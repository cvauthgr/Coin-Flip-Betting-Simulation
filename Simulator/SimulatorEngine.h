#ifndef SIMULATORENGINE_H
#define SIMULATORENGINE_H

#include "StructRelated.h"
#include "GamblerInfoClass.h"
#include "Enum.h"
#include "BettingStrategies.h"

inline SimulationStatististics& CoinFlipSimulation( GamblerInfo& Player , BettingMethod method , SimulationStatististics& stats) // Implement struct as return type
{
    switch( method ) // Should break those as free functions
    {

    case BettingMethod::timid : return timidStrategy( Player , stats ) ;

    case BettingMethod::bold : return  boldStrategy( Player , stats ) ;

    case BettingMethod::martingale : return martingaleStrategy( Player , stats ) ;

    case BettingMethod::random : return randomBetsStrategy( Player , stats ) ;

    default : return stats = { -1 , -1 , -1 , -1 , -1 , -1 } ;
    }
}

#endif
