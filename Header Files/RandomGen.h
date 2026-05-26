#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#include <random>

namespace random
{

inline std::mt19937_64 generate() 
{
    thread_local std::random_device rd ; //thread_local so each thread get a different seed

    thread_local std::seed_seq seed_collection { rd() , rd() , rd() , rd() , rd() , rd() , rd() } ;

    return std::mt19937_64 ( seed_collection ) ;
}

inline thread_local std::mt19937_64  mt { generate() } ; //Can be called from any file ( stand-alone instance ) , thread local for the same reason
//otherwise all threads use the same random value at each respective simualation , mt19937_64 to avoid repetitiond in random number generations

template < typename T > 
T getReal(T min , T max)
{
    return std::uniform_real_distribution<T>{ min , max }(mt) ;
}


}

#endif
