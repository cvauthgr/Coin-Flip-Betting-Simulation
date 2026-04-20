#include "StructRelated.h"
#include "Enum.h"
#include "SimulatorEngine.h"
#include "CasesInfo.h"
#include "MonteCarloWalks.h"
#include "ProgramMode.h"

int main()
{
    #ifdef MONOTHREADING
    std::cout << CoinFlipSimulation( TimidStrategyPlayer , BettingMethod::timid , data ) ;
    freeStruct( data ) ;
    std::cout << CoinFlipSimulation( BoldStrategyPlayer , BettingMethod::bold , data ) ;
    freeStruct( data  );
    std::cout << CoinFlipSimulation( MartinGaleStrategyPlayer , BettingMethod::martingale , data ) ;
    freeStruct( data ) ;
    std::cout << CoinFlipSimulation( ForgetfulStrategyPlayer , BettingMethod::random , data ) ;
    #endif

    #ifdef MULTITHREADING
    monteCarloSimulation(1000000);
    monteCarloResults() ;
    #endif
    return 0;

}
