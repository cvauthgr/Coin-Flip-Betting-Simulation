#ifndef STRUCTRELATED_H
#define STRUCTRELATED_H

#include <vector>
#include <iostream>

#include "GamblerInfoClass.h"

struct SimulationStatististics // 64 bits cpu reads in 8 bytes packets at a time ( important for padding )
{
    double balanceAfter { 0.0 } ;
    int roundsPlayed { 0 } ;
    int winningRounds { 0 } ;
    int losingRounds { 0 } ;
    int paddingAvoider { 0 } ;
    double winPrecentage { 0.0 } ;
};// Struct members need reseting
struct copyof
{
    double bet { 0.0 } ;
    double balance { 0.0 } ;
    double goal { 0.0 } ;
    double probability { 0.0 } ;
    std::vector<double> balanceValues { } ;

    copyof( const GamblerInfo& Player )
        : bet { Player.getBet() } ,
          balance { Player.getBalance()} ,
          goal { Player.getGoal() } ,
          probability { Player.getProbability() }
    {

    }
};
inline void freeStruct(SimulationStatististics& stats)
{
    stats.balanceAfter = 0.0  ;
    stats.losingRounds = 0 ;
    stats.roundsPlayed = 0;
    stats.winningRounds = 0 ;
    stats.paddingAvoider = 0 ; // avoiding unwanted memory holding
    stats.winPrecentage = 0.0 ;
}
inline std::ostream& operator<<( std::ostream& output ,const SimulationStatististics& data)
{
    output << "After " << data.roundsPlayed << " rounds , your balance is " << data.balanceAfter << '\n' <<"You won " << data.winningRounds << " rounds and lost " << data.losingRounds << '\n' <<"With a win percentage of " << data.winPrecentage << "%\n";

    return output ;
}

#endif
