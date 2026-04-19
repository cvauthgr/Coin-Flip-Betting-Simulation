#ifndef PLOTTING_H
#define PLOTTING_H

#include <string>

inline void plot(const std::string& fileName ,const std::string& plotTitle) // C-Style string concatenation (exceptional & this->C)
{
    std::string gnuplotCommand = "gnuplot -persistent -e \""
                                 "set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb 'black' behind;"
                                 " set border lc rgb 'white'; "
                                 "set xtics tc rgb 'white'; "
                                 "set ytics tc rgb 'white'; "
                                 "set key tc rgb 'white'; "
                                 "plot '"+fileName+"' with lines lc rgb 'red' title '"+plotTitle+"'\"";

    system(gnuplotCommand.c_str());
}

#endif
