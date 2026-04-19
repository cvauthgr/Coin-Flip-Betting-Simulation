#ifndef BETTINGSTRATEGIES_H
#define BETTINGSTRATEGIES_H

#include "StructRelated.h"
#include "GamblerInfoClass.h"
#include "RandomGen.h" 
#include "FileHandler.h"
#include "Plotting.h"
#include "ProgramMode.h"

#include <atomic>
#include <vector>

std::atomic<std::uint64_t> g_timidWins { 0 } ;
std::atomic<std::uint64_t> g_boldWins { 0 } ;
std::atomic<std::uint64_t>g_martingaleWins { 0 } ;
std::atomic<std::uint64_t> g_randomWins { 0 } ;

std::atomic<std::uint64_t> g_timidTotalRounds { 0 } ;
std::atomic<std::uint64_t> g_boldTotalRounds { 0 } ;
std::atomic<std::uint64_t> g_martingaleTotalRounds { 0 } ;
std::atomic<std::uint64_t> g_randomTotalRounds { 0 } ;

inline SimulationStatististics& timidStrategy( GamblerInfo& Player , SimulationStatististics& stats )
{
    copyof playerData { Player } ;

    while ( playerData.balance < playerData.goal && playerData.balance > 0 )
    {
        if( random::getReal( 0.0 , 1.0 ) <= playerData.probability )
        {
            playerData.balance += playerData.bet ;
            stats.winningRounds += 1 ;
        }
        else
        {
            playerData.balance -= playerData.bet ;
            #ifdef MONOTHREADING
            stats.losingRounds += 1 ;
            #endif
        }
        stats.roundsPlayed += 1 ;
        #ifdef MONOTHREADING
        playerData.balanceValues.push_back(playerData.balance);
        #endif
    }
    #ifdef MONOTHREADING
    stats.balanceAfter = playerData.balance ;
    Player.mutBalance( playerData.balance ) ;

    stats.winPrecentage = ( 100.0 * stats.winningRounds ) / stats.roundsPlayed ; 

    writeToFile( playerData.balanceValues , "timidstats.txt") ;

    plot( "timidstats.txt" , "Timid" ) ;
    #endif

    #ifdef MULTITHREADING
    g_timidTotalRounds += stats.roundsPlayed ;
    g_timidWins += stats.winningRounds ;
    #endif

    return stats ;
}
inline SimulationStatististics& boldStrategy( GamblerInfo& Player , SimulationStatististics& stats)
{
    copyof playerData { Player } ;

    while ( playerData.balance < playerData.goal && playerData.balance > 0 )
    {
        if( playerData.balance <= playerData.goal / 2 )
        {
            playerData.bet = playerData.balance ;
        }
        else if( playerData.balance > playerData.goal / 2 )
        {
            playerData.bet = playerData.goal - playerData.balance ;
        }

        if( random::getReal( 0.0 , 1.0 ) <= playerData.probability )
        {
            playerData.balance += playerData.bet ;
            stats.winningRounds += 1 ;
        }
        else
        {
            playerData.balance -= playerData.bet ;
            #ifdef MONOTHREADING
            stats.losingRounds += 1 ;
            #endif
        }
        stats.roundsPlayed += 1 ;
        #ifdef MONOTHREADING
        playerData.balanceValues.push_back(playerData.balance) ;
        #endif
    }
    #ifdef MONOTHREADING
    stats.balanceAfter = playerData.balance ;
    Player.mutBalance( playerData.balance ) ;

    stats.winPrecentage = ( 100.0 * stats.winningRounds ) / stats.roundsPlayed ;

    writeToFile( playerData.balanceValues , "boldstats.txt") ;

    plot( "boldstats.txt" , "Bold" ) ;
    #endif

    #ifdef MULTITHREADING
    g_boldTotalRounds += stats.roundsPlayed ;
    g_boldWins += stats.winningRounds ;
    #endif

    return  stats;
}
inline SimulationStatististics& martingaleStrategy( GamblerInfo& Player , SimulationStatististics& stats)
{
    copyof playerData { Player } ;

    while ( playerData.balance < playerData.goal && playerData.balance > 0 )
    {
        if( random::getReal( 0.0 , 1.0 ) <= playerData.probability )
        {
            playerData.balance += playerData.bet ;
            stats.winningRounds += 1 ;
            playerData.bet = Player.getBet() ;
        }
        else if( playerData.bet*2 <= playerData.balance )
        {
            playerData.balance -= playerData.bet ;
            //stats.losingRounds += 1 ;
            playerData.bet *= 2 ;
        }
        else
        {
            playerData.bet = playerData.balance ;
            playerData.balance -= playerData.bet ;
            #ifdef MONOTHREADING
            stats.losingRounds += 1 ;
            #endif
        }
        stats.roundsPlayed += 1 ;
        #ifdef MONOTHREADING
        playerData.balanceValues.push_back(playerData.balance) ;
        #endif
    }
    #ifdef MONOTHREADING
    stats.balanceAfter = playerData.balance ;
    Player.mutBalance( playerData.balance ) ;

    stats.winPrecentage = ( 100.0 * stats.winningRounds ) / stats.roundsPlayed ; 

    writeToFile( playerData.balanceValues , "martingalestats.txt" ) ;

    plot( "martingalestats.txt" , "Martingale" ) ;
    #endif

    #ifdef MULTITHREADING
    g_martingaleTotalRounds += stats.roundsPlayed ;
    g_martingaleWins += stats.winningRounds ;
    #endif

    return stats ;
}
inline SimulationStatististics& randomBetsStrategy( GamblerInfo& Player , SimulationStatististics& stats)
{
    copyof playerData { Player } ;

    while ( playerData.balance < playerData.goal && playerData.balance > 0 )
    {

        while( playerData.balance + playerData.bet > playerData.goal )
            playerData.bet = random::getReal( 0.0 , playerData.balance ) ;

        if( random::getReal( 0.0 , 1.0 ) <= playerData.probability )
        {
            playerData.balance += playerData.bet ;
            stats.winningRounds += 1 ;
        }
        else
        {
            playerData.balance -= playerData.bet ;
            #ifdef MONOTHREADING
            stats.losingRounds += 1 ;
            #endif
        }
        stats.roundsPlayed += 1 ;

        #ifdef MONOTHREADING
        playerData.balanceValues.push_back(playerData.balance) ;
        #endif
    }

    #ifdef MONOTHREADING
    stats.balanceAfter = playerData.balance ;
    Player.mutBalance( playerData.balance ) ;

    stats.winPrecentage = ( 100.0 * stats.winningRounds ) / stats.roundsPlayed ; 

    writeToFile( playerData.balanceValues , "randombetting.txt" ) ;

    plot( "randombetting.txt" , "RandomBets" ) ; 
    #endif

    #ifdef MULTITHREADING
    g_randomTotalRounds += stats.roundsPlayed ;
    g_randomWins += stats.winningRounds ;
    #endif

    return stats ;
}

#endif
