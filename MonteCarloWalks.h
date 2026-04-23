#ifndef MONTECARLOWALKS_H
#define MONTECARLOWALKS_H

#include <cstdint>
#include <thread>

#include "BettingStrategies.h"
#include "CasesInfo.h"
#include "MonteCarloResultsPrint.h"

inline void monteCarloSimulation( std::uint64_t numberOfSimulations )
{
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

    std::jthread Timid1( callTimid , numberOfSimulations / 4 ) ;
    std::jthread Timid2( callTimid , numberOfSimulations / 4 ) ;
    std::jthread Timid3( callTimid , numberOfSimulations / 4 ) ;
    std::jthread Timid4( callTimid , numberOfSimulations / 4 ) ;
    std::jthread Bold1( callBold , numberOfSimulations / 4 ) ;
    std::jthread Bold2( callBold , numberOfSimulations / 4 ) ;
    std::jthread Bold3( callBold , numberOfSimulations / 4 ) ;
    std::jthread Bold4( callBold , numberOfSimulations / 4 ) ;
    std::jthread Martingale1( callMartingale , numberOfSimulations / 4 ) ;
    std::jthread Martingale2( callMartingale , numberOfSimulations / 4 ) ;
    std::jthread Martingale3( callMartingale , numberOfSimulations / 4 ) ;
    std::jthread Martingale4( callMartingale , numberOfSimulations / 4 ) ;
    std::jthread Random1( callRandom , numberOfSimulations / 4 ) ;
    std::jthread Random2( callRandom , numberOfSimulations / 4 ) ;
    std::jthread Random3( callRandom , numberOfSimulations / 4 ) ;
    std::jthread Random4( callRandom , numberOfSimulations / 4 ) ;

}

#endif
