#include <cassert>
#include <iostream>
#include <cstdlib>
#include <fstream>

#include "RandomGen.h" // DO NOT USE ANYWHERE ( ONLY USE -> Random.h )

enum class BettingMethod
{
    timid,
    bold,
    martingale,
    random
};
struct SimulationStatististics // 64 bits cpu reads in 8 bytes packets at a time ( important for padding )
{
    double balanceAfter { 0.0 } ;
    int roundsPlayed { 0 } ;
    int winningRounds { 0 } ;
    int losingRounds { 0 } ;
    int paddingAvoider { 0 } ;
    double winPrecentage { 0.0 } ;
};// Struct members need reseting
void freeStruct(SimulationStatististics& stats)
{
    stats.balanceAfter = 0.0  ;
    stats.losingRounds = 0 ;
    stats.roundsPlayed = 0;
    stats.winningRounds = 0 ;
    stats.paddingAvoider = 0 ; // avoiding unwanted memory holding
    stats.winPrecentage = 0.0 ;
}
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

    SimulationStatististics data { } ;

    //DO NOT CALL IN A LOOP FOR ANY REASON
    std::cout << CoinFlipSimulation( TimidStrategyPlayer , BettingMethod::timid , data ) ;
    freeStruct( data ) ;
    std::cout << CoinFlipSimulation( BoldStrategyPlayer , BettingMethod::bold , data ) ;
    freeStruct( data ) ;
    std::cout << CoinFlipSimulation( MartinGaleStrategyPlayer , BettingMethod::martingale , data ) ;
    freeStruct( data ) ;
    std::cout << CoinFlipSimulation( ForgetfulStrategyPlayer , BettingMethod::random , data ) ;


    return 0;

}
