#ifndef MONTECARLOWALKS_H
#define MONTECARLOWALKS_H

#include <cstdint>
#include <thread>

#include "BettingStrategies.h"
#include "CasesInfo.h"
#include "MonteCarloResultsPrint.h"

inline void monteCarloSimulation( std::uint64_t numberOfSimulations )
{
    unsigned int numberOfThreads = std::thread::hardware_concurrency() ; // Get the number of threads in the specific machine

    auto callTimid = []( std::uint64_t numberOfSimulations )
    {
        for( std::uint64_t index = 0 ; index < numberOfSimulations ; ++ index)
        {
            timidStrategy(TimidStrategyPlayer , data ) ;
            freeStruct( data ) ;
        }
    };
    auto callBold = []( std::uint64_t numberOfSimulations )
    {
        for( std::uint64_t index = 0 ; index < numberOfSimulations ; ++ index)
        {
            boldStrategy(BoldStrategyPlayer , data ) ;
            freeStruct( data ) ;
        }
    };
    auto callMartingale = []( std::uint64_t numberOfSimulations )
    {
        for( std::uint64_t index = 0 ; index < numberOfSimulations ; ++ index)
        {
            martingaleStrategy( MartinGaleStrategyPlayer , data ) ;
            freeStruct( data ) ;
        }
    };
    auto callRandom = []( std::uint64_t numberOfSimulations )
    {
        for( std::uint64_t index = 0 ; index < numberOfSimulations ; ++ index)
        {
            randomBetsStrategy(ForgetfulStrategyPlayer , data ) ;
            freeStruct( data ) ;
        }
    };

    unsigned int numberOfIterationsPerThread = numberOfSimulations / numberOfThreads ;

    std::vector<std::jthread> workerThreads { } ;
    workerThreads.reserve(numberOfThreads) ;

    //Push the needed number of threads in the vector , analogous to the thread counter ; ( All modern machines have an even amount of threads > 4 )

    for( unsigned int index = 0 ; index < numberOfThreads / 4 ; ++ index )
    {
        workerThreads.emplace_back(callTimid , numberOfIterationsPerThread ) ;
        workerThreads.emplace_back(callBold , numberOfIterationsPerThread) ;
        workerThreads.emplace_back(callMartingale , numberOfIterationsPerThread) ;
        workerThreads.emplace_back(callRandom , numberOfIterationsPerThread) ;
    }


}

#endif
