#ifndef GAMBLERINFOCLASS_H
#define GAMBLERINFOCLASS_H

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

#endif
