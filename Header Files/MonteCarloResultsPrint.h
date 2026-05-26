#ifndef MONTECARLORESULTSPRINT_H
#define MONTECARLORESULTSPRINT_H

#include "BettingStrategies.h"
#include "CasesInfo.h"

inline void monteCarloResults()
{
    std::cout << "Timid strategy with a win rate of " << (static_cast<double>(g_timidWins)*100.0)/g_timidTotalRounds << "% with an expected return value of E[X] = " << g_timidTotalEarnings/static_cast<double>(g_timidTotalRounds) << "$ and an expected total net loss E[L] = " << 100.0 - ( ( 100 * g_timidTotalEarnings/static_cast<double>(g_timidTotalRounds) ) /  g_timidStartingCapital ) << "%" << '\n' ;
    std::cout << "Bold strategy with a win rate of " << (static_cast<double>(g_boldWins)*100.0)/g_boldTotalRounds << "% with an expected return value of E[X] = " << g_boldTotalEarnings/static_cast<double>(g_boldTotalRounds) << "$ and an expected total net loss E[L] = " << 100.0 - ( ( 100 * g_boldTotalEarnings/static_cast<double>(g_boldTotalRounds) ) /  g_boldStartingCapital ) << "%" <<'\n' ;
    std::cout << "Martingale strategy with a win rate of " << (static_cast<double>(g_martingaleWins)*100.0)/g_martingaleTotalRounds << "% with an expected return value of E[X] = " << g_martingaleTotalEarnings/static_cast<double>(g_martingaleTotalRounds) << "$ and an expected total net loss E[L] = " << 100.0 - ( ( 100 * g_martingaleTotalEarnings/static_cast<double>(g_martingaleTotalRounds) ) /  g_martingaleStartingCapital ) << "%" << '\n' ;
    std::cout << "Random strategy with a win rate of " << (static_cast<double>(g_randomWins)*100.0)/g_randomTotalRounds <<  "% with an expected return value of E[X] = " << g_randomTotalEarnings/static_cast<double>(g_randomTotalRounds) << "$ and an expected total net loss E[L] = "<< 100.0 - ( ( 100 * g_randomTotalEarnings/static_cast<double>(g_randomTotalRounds) ) /  g_randomStartingCapital ) << "%" << '\n' ;
}

#endif
