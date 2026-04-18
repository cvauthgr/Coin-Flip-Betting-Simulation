#ifndef MONTECARLOWALKS_H
#define MONTECARLOWALKS_H

#include <cstdint>
#include <thread>

#include "BettingStrategies.h"
#include "CasesInfo.h"
#include "MonteCarloResultsPrint.h"

/*Initialize the threads with their respective functions
 std::ref is needed because std::jthread tries to bind the arguments provided
to rvalues which is impossible for types like the ones i have created ( ex. SimulationStatistics )
std::ref unpacks as an rvalue the argument and then when it is of use to the function
it turns it back to the non-const lvalue it needs (as far as i understand) */

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

    std::jthread Timid( callTimid , numberOfSimulations) ;
    std::jthread Bold( callBold , numberOfSimulations) ;
    std::jthread Martingale( callMartingale , numberOfSimulations) ;
    std::jthread Random( callRandom , numberOfSimulations ) ;

}

#endif
