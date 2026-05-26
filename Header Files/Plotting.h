#ifndef PLOTTING_H
#define PLOTTING_H

#include <vector>
#include <windows.h>
#include <string>

inline void plot(const std::string& fileName ,const std::string& plotTitle) // C-Style string concatenation
{

    STARTUPINFOA si {} ;
    PROCESS_INFORMATION pi {} ;

    si.cb = sizeof(si) ;

    std::string gnuplotCommand = "gnuplot -persistent -e \""
                                 "set terminal wxt size 800,600 enhanced; "
                                 "set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb 'black' behind; "
                                 "set border lc rgb 'white'; "
                                 "set xtics tc rgb 'white'; "
                                 "set ytics tc rgb 'white'; "
                                 "set key tc rgb 'white'; "
                                 "set lmargin 10; "
                                 "set rmargin 5; "
                                 "set tmargin 5; "
                                 "set bmargin 5; "
                                 "plot '"+fileName+"' with lines lc rgb 'red' title '"+plotTitle+"'\"";

    std::vector<char> mutableCommand( gnuplotCommand.begin(), gnuplotCommand.end() ) ;
    mutableCommand.push_back( '\0' ) ;

    BOOL success = CreateProcessA(
        NULL,                    // Application name ( NULL = infer from command line )
        mutableCommand.data(),           // Command line
        NULL,                    // Process security attributes
        NULL,                    // Thread security attributes
        FALSE,                   // Inherit handles
        0,                       // Creation flags
        NULL,                    // Environment ( NULL = inherit parent's )
        NULL,                    // Working directory ( NULL = inherit parent's )
        &si,                     // Startup info
        &pi                      // Process information ( output )
        ) ;

    if( success )
    {
        CloseHandle( pi.hProcess ) ;
        CloseHandle( pi.hThread ) ;
    }

}

#endif
