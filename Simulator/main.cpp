#include <cassert>
#include <iostream>
#include <cstdlib>
#include <fstream>

#include "RandomGen.h" // DO NOT USE ANYWHERE ( ONLY USE -> Random.h )
#include "PrimeGen.h"

//#define DEBUG
#define TODO

enum class BettingMethod
{
    timid,
    bold,
    martingale,
    random,
    primes,
};
struct SimulationStatististics // 64 bits cpu reads in 8 bytes packets at a time ( important for padding )
{
    double balanceAfter { 0.0 } ;
    int roundsPlayed { 0 } ;
    int winningRounds { 0 } ;
    int losingRounds { 0 } ;
    int paddingAvoider { 0 } ;
    double winPrecentage { 0.0 } ;
};
std::ostream& operator<<( std::ostream& output ,const SimulationStatististics& data)
{
    output << "After " << data.roundsPlayed << " rounds , your balance is " << data.balanceAfter << '\n' <<"You won " << data.winningRounds << " rounds and lost " << data.losingRounds << '\n' <<"With a win percentage of " << data.winPrecentage << "%\n";

    return output ;
}
class GamblerInfo
{

private :

    double m_balance { 0.0 } ; //constexpr static in case of static assertion for better catching ( if i implement exceptions )
    double m_probability { 0.0 } ;
    double m_betPerRound { 0.0 } ;
    double m_goal { 0.0 } ;

public :

    GamblerInfo( double balance  , double probability , double betPerRound ,double goal ) // Class constructor initialization
        : m_balance { balance } ,
        m_probability { probability } ,
        m_betPerRound{ betPerRound },
        m_goal { goal }
    {

    }

    ~GamblerInfo() = default ; // Class Destructor ( No need to be called - only for potential scalability )

    //May need a copy constructor (???)

    //Class getters

    double getBalance() const { return m_balance ; }
    double getProbability() const { return m_probability ; }
    double getBet() const { return m_betPerRound ; }
    double getGoal() const { return m_goal ; }

    //Class Mutators

    void mutBalance( double Balance ) { m_balance = Balance ; } //Maybe passing by reference is better (???)
    void mutPropability( double Probability ) { m_probability = Probability ; }
    void mutBet( double Bet ) { m_betPerRound = Bet ; }
    void mutGoal( double Goal ) { m_goal = Goal ; }

};
SimulationStatististics& CoinFlipSimulation( GamblerInfo& Player , BettingMethod method , SimulationStatististics& stats) // Implement struct as return type
{
    double PlayerBet = Player.getBet() ;
    double PlayerBalance = Player.getBalance() ;
    double PlayerGoal = Player.getGoal() ;
    double PlayerProbability = Player.getProbability() ;

    switch( method )
    {

    case BettingMethod::timid :
    {
    std::ofstream timidstats ;
    timidstats.open("timidstats.txt") ;

    if(!timidstats) // Throw an exception or something ( assert this possibly )
    {
        std::cerr << "Failure in provision of requested file" << '\n' ;
        abort() ;
    }

    while ( PlayerBalance < PlayerGoal && PlayerBalance > 0 )
    {
        if( random::getReal( 0.0 , 1.0 ) <= PlayerProbability )
        {
            PlayerBalance += PlayerBet ;
            stats.winningRounds += 1 ;
        }
        else
        {
            PlayerBalance -= PlayerBet ;
            stats.losingRounds += 1 ;
        }
        stats.roundsPlayed += 1 ;

        timidstats << PlayerBalance << '\n' ;
    }

    stats.balanceAfter = PlayerBalance ;
    Player.mutBalance( PlayerBalance ) ;

    #ifdef DEBUG
    assert( stats.roundsPlayed != 0 ) ;
    #endif

    stats.winPrecentage = ( 100.0 * stats.winningRounds ) / stats.roundsPlayed ; //Integer division bug

    timidstats.close() ;

    system("gnuplot -persistent -e \""
           "set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb 'black' behind;"
           " set border lc rgb 'white'; "
           "set xtics tc rgb 'white'; "
           "set ytics tc rgb 'white'; "
           "set key tc rgb 'white'; "
           "plot 'timidstats.txt' with lines lc rgb 'red' title 'Timid'\"");

    return stats ;
    }

    case BettingMethod::bold :
    {
        std::ofstream boldstats ;
        boldstats.open( "boldstats.txt" ) ;

        if( !boldstats )
        {
            std::cerr << "Failure in provision of requested file" << '\n' ;
            abort() ;
        }

        while ( PlayerBalance < PlayerGoal && PlayerBalance > 0 )
        {
            if( PlayerBalance <= PlayerGoal / 2 )
            {
                PlayerBet = PlayerBalance ;
            }
            else if( PlayerBalance > PlayerGoal / 2 )
            {
                PlayerBet = PlayerGoal - PlayerBalance ;
            }

            if( random::getReal( 0.0 , 1.0 ) <= PlayerProbability )
            {
                PlayerBalance += PlayerBet ;
                stats.winningRounds += 1 ;
            }
            else
            {
                PlayerBalance -= PlayerBet ;
                stats.losingRounds += 1 ;
            }
            stats.roundsPlayed += 1 ;

            boldstats << PlayerBalance << '\n' ;
        }
        stats.balanceAfter = PlayerBalance ;
        Player.mutBalance( PlayerBalance ) ;

    #ifdef DEBUG
        assert( stats.roundsPlayed != 0 ) ;
    #endif

        stats.winPrecentage = ( 100.0 * stats.winningRounds ) / stats.roundsPlayed ; //Integer division bug

        boldstats.close();

        system("gnuplot -persistent -e \""
               "set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb 'black' behind;"
               " set border lc rgb 'white'; "
               "set xtics tc rgb 'white'; "
               "set ytics tc rgb 'white'; "
               "set key tc rgb 'white'; "
               "plot 'boldstats.txt' with lines lc rgb 'red' title 'Bold'\"");


        return  stats;
    }
    case BettingMethod::martingale :
    {
        std::ofstream martingalestats ;
        martingalestats.open("martingalestats.txt") ;

        if(!martingalestats) // Throw an exception or something ( assert this possibly )
        {
            std::cerr << "Failure in provision of requested file" << '\n' ;
            abort() ;
        }

        while ( PlayerBalance < PlayerGoal && PlayerBalance > 0 )
        {
            if( random::getReal( 0.0 , 1.0 ) <= PlayerProbability )
            {
                PlayerBalance += PlayerBet ;
                stats.winningRounds += 1 ;
                PlayerBet = Player.getBet() ;
            }
            else if( PlayerBet*2 <= PlayerBalance )
            {
                PlayerBalance -= PlayerBet ;
                stats.losingRounds += 1 ;
                PlayerBet *= 2 ;
            }
            else
            {
                PlayerBet = PlayerBalance ;
                PlayerBalance -= PlayerBet ;
                stats.losingRounds += 1 ;
            }
            stats.roundsPlayed += 1 ;

            martingalestats << PlayerBalance << '\n' ;
        }

        stats.balanceAfter = PlayerBalance ;
        Player.mutBalance( PlayerBalance ) ;

        #ifdef DEBUG
        assert( stats.roundsPlayed != 0 ) ;
        #endif

        stats.winPrecentage = ( 100.0 * stats.winningRounds ) / stats.roundsPlayed ; //Integer division bug

        martingalestats.close() ;

        system("gnuplot -persistent -e \""
               "set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb 'black' behind;"
               " set border lc rgb 'white'; "
               "set xtics tc rgb 'white'; "
               "set ytics tc rgb 'white'; "
               "set key tc rgb 'white'; "
               "plot 'martingalestats.txt' with lines lc rgb 'red' title 'Martingale'\""); // Should make it a free function

        return stats ;
    }
    case BettingMethod::random :
    {

        std::ofstream randombetting ;
        randombetting.open("randombetting.txt") ;

        if( !randombetting )
        {
            std::cerr << "Failure in provision of requested file" << '\n' ;
            abort() ;
        }

        while ( PlayerBalance < PlayerGoal && PlayerBalance > 0 )
        {

            while( PlayerBalance + PlayerBet > PlayerGoal )
                PlayerBet = random::getReal( 0.0 , PlayerBalance ) ; //Both need to be doubles ( random.h still needs refactoring)

                if( random::getReal( 0.0 , 1.0 ) <= PlayerProbability )
                {
                    PlayerBalance += PlayerBet ;
                    stats.winningRounds += 1 ;
                }
                else
                {
                    PlayerBalance -= PlayerBet ;
                    stats.losingRounds += 1 ;
                }
                stats.roundsPlayed += 1 ;

            randombetting << PlayerBalance << '\n' ;
        }

        stats.balanceAfter = PlayerBalance ;
        Player.mutBalance( PlayerBalance ) ;

        #ifdef DEBUG
        assert( stats.roundsPlayed != 0 ) ;
        #endif

        stats.winPrecentage = ( 100.0 * stats.winningRounds ) / stats.roundsPlayed ; //Integer division bug

        randombetting.close() ;

        system("gnuplot -persistent -e \""
               "set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb 'black' behind;"
               " set border lc rgb 'white'; "
               "set xtics tc rgb 'white'; "
               "set ytics tc rgb 'white'; "
               "set key tc rgb 'white'; "
               "plot 'randombetting.txt' with lines lc rgb 'red' title 'Random Bets'\""); // Should make it a free function

        return stats ;

    }
    case BettingMethod::primes :
    {

    }
    default :
        stats.balanceAfter = -1 ;
        stats.losingRounds = -1 ;
        stats.roundsPlayed = -1 ;
        stats.winPrecentage = -1 ;

    return stats ;

    }
}
int main()
{
    GamblerInfo TimidStrategyPlayer { 50 , 0.5   , 1 , 150 } ;
    GamblerInfo BoldStrategyPlayer { 50 , 0.5 , 1 , 150 } ;
    GamblerInfo MartinGaleStrategyPlayer { 50 , 0.5 , 1 , 150 } ;
    GamblerInfo ForgetfulStrategyPlayer { 50 , 0.5 , 1 , 150 } ;
    GamblerInfo MathematicalStrategyPlayer { 50 , 0.5 , 1 , 150 } ;

    SimulationStatististics data { } ;

    #ifdef DEBUG

    std::cout << TimidStrategyPlayer.getBalance() << '\n' ;
    TimidStrategyPlayer.mutBalance( 75 ) ;
    std::cout << TimidStrategyPlayer.getBalance() << '\n' ;
    std::cout << TimidStrategyPlayer.getProbability()<< '\n' ;
    TimidStrategyPlayer.mutPropability( 0.2 ) ;
    std::cout << TimidStrategyPlayer.getProbability()<< '\n' ;
    std::cout << TimidStrategyPlayer.getBet() << '\n' ;
    TimidStrategyPlayer.mutBet( 2 ) ;
    std::cout << TimidStrategyPlayer.getBet() << '\n' ;
    std::cout << TimidStrategyPlayer.getGoal() << '\n' ;
    TimidStrategyPlayer.mutGoal( 225 ) ;
    std::cout << TimidStrategyPlayer.getGoal() << '\n' ;

    #endif

    //std::cout << CoinFlipSimulation( TimidStrategyPlayer , BettingMethod::timid , data ) ;
    //std::cout << CoinFlipSimulation( BoldStrategyPlayer , BettingMethod::bold , data ) ;
    //std::cout << CoinFlipSimulation( MartinGaleStrategyPlayer , BettingMethod::martingale , data ) ;
    //std::cout << CoinFlipSimulation( ForgetfulStrategyPlayer , BettingMethod::random , data ) ;

    prime::getPrimes(1000) ;

    return 0;

}