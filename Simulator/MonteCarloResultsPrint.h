#ifndef MONTECARLORESULTSPRINT_H
#define MONTECARLORESULTSPRINT_H

#include "BettingStrategies.h"

inline void monteCarloResults()
{
    std::cout << "Timid strategy with a win rate of " << (static_cast<double>(g_timidWins)*100.0)/g_timidTotalRounds << '\n' ;
    std::cout << "Bold strategy with a win rate of " << (static_cast<double>(g_boldWins)*100.0)/g_boldTotalRounds << '\n' ;
    std::cout << "Martingale strategy with a win rate of " << (static_cast<double>(g_martingaleWins)*100.0)/g_martingaleTotalRounds << '\n' ;
    std::cout << "Random strategy with a win rate of " << (static_cast<double>(g_randomWins)*100.0)/g_randomTotalRounds << '\n' ;
}

#endif
