#ifndef CASESINFO_H
#define CASESINFO_H

#include "StructRelated.h"
#include <atomic>

//Casino edge

/*inline GamblerInfo TimidStrategyPlayer { 5 , 0.49 , 1 , 150 } ;
inline GamblerInfo BoldStrategyPlayer { 5 , 0.49 , 1 , 150 } ;
inline GamblerInfo MartinGaleStrategyPlayer { 5 , 0.49 , 1 , 150 } ;
inline GamblerInfo ForgetfulStrategyPlayer { 5 , 0.49 , 1 , 150 } ;*/

//Equal edge

/*inline GamblerInfo TimidStrategyPlayer { 5 , 0.5 , 1 , 150 } ;
inline GamblerInfo BoldStrategyPlayer { 5 , 0.5 , 1 , 150 } ;
inline GamblerInfo MartinGaleStrategyPlayer { 5 , 0.5 , 1 , 150 } ;
inline GamblerInfo ForgetfulStrategyPlayer { 5 , 0.5 , 1 , 150 } ;*/

//Player edge

inline GamblerInfo TimidStrategyPlayer { 5 , 0.6 , 1 , 150 } ;
inline GamblerInfo BoldStrategyPlayer { 5 , 0.6 , 1 , 150 } ;
inline GamblerInfo MartinGaleStrategyPlayer { 5 , 0.6 , 1 , 150 } ;
inline GamblerInfo ForgetfulStrategyPlayer { 5 , 0.6 , 1 , 150 } ;

inline thread_local SimulationStatististics  data { } ;

std::atomic<double> g_timidStartingCapital { TimidStrategyPlayer.getBalance() } ;
std::atomic<double> g_boldStartingCapital { BoldStrategyPlayer.getBalance() } ;
std::atomic<double> g_martingaleStartingCapital { MartinGaleStrategyPlayer.getBalance() } ;
std::atomic<double> g_randomStartingCapital { ForgetfulStrategyPlayer.getBalance() } ;

#endif
