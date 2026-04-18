#ifndef CASESINFO_H
#define CASESINFO_H

#include "StructRelated.h"

inline GamblerInfo TimidStrategyPlayer { 50 , 0.5   , 1 , 150 } ;
inline GamblerInfo BoldStrategyPlayer { 50 , 0.5 , 1 , 150 } ;
inline GamblerInfo MartinGaleStrategyPlayer { 50 , 0.5 , 1 , 150 } ;
inline GamblerInfo ForgetfulStrategyPlayer { 50 , 0.5 , 1 , 150 } ;

inline thread_local SimulationStatististics  data { } ;


#endif
