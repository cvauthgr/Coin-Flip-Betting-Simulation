#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#include <random>

namespace random
{

inline std::mt19937_64 generate() //Inline leaks to global
{
    thread_local std::random_device rd ; //thread_local so each thread get a different seed

    return std::mt19937_64 ( rd() ) ;
}

inline thread_local std::mt19937_64  mt { generate() } ; //Can be called from any file ( stand-alone instance ) , thread local for the same reason
//otherwise all threas use the same random value at each respective simualation , mt19937_64 to avoid repetitiond in random number generations

template < typename T > //TODO : Return the common type of <T,U> , for now only float, double up front
T getReal(T min , T max)
{
    return std::uniform_real_distribution<T>{ min , max }(mt) ;
}

//Does not check the case (int , float) , use std::optional  (???)

}

#endif
