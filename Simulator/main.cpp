#include "StructRelated.h"
#include "GamblerInfoClass.h"
#include "Enum.h"
#include "SimulatorEngine.h"

int main()
{
    GamblerInfo TimidStrategyPlayer { 50 , 0.5   , 1 , 150 } ;
    GamblerInfo BoldStrategyPlayer { 50 , 0.5 , 1 , 150 } ;
    GamblerInfo MartinGaleStrategyPlayer { 50 , 0.5 , 1 , 150 } ;
    GamblerInfo ForgetfulStrategyPlayer { 50 , 0.5 , 1 , 150 } ;

    SimulationStatististics data { } ;

    std::cout << CoinFlipSimulation( TimidStrategyPlayer , BettingMethod::timid , data ) ;
    freeStruct( data ) ;
    std::cout << CoinFlipSimulation( BoldStrategyPlayer , BettingMethod::bold , data ) ;
    freeStruct( data ) ;
    std::cout << CoinFlipSimulation( MartinGaleStrategyPlayer , BettingMethod::martingale , data ) ;
    freeStruct( data ) ;
    std::cout << CoinFlipSimulation( ForgetfulStrategyPlayer , BettingMethod::random , data ) ;

    return 0;

}