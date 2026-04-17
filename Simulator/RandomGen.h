#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#include <random>

namespace random
{

inline std::mt19937 generate() //Inline leaks to global
{
    std::random_device rd ;

    return std::mt19937( rd() ) ;
}

inline std::mt19937 mt { generate() } ; //Can be called from any file ( stand-alone instance )

template < typename T > //TODO : Return the common type of <T,U> , for now only float, double up front
T getReal(T min , T max)
{
    return std::uniform_real_distribution<T>{ min , max }(mt) ;
}

//Does not check the case (int , float) , use common_type or std::optional  (???)

}

#endif
