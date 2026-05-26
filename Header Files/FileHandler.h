#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <iostream>
#include <vector>

inline bool isFileOpen( const std::ofstream& fileName )
{
    if(fileName)
        return true ;
    else
        return false ;
}
inline void errorOpeningTheFile(const std::string& fileName)
{
    std::cout << "File name :" << fileName << " , failure to open " << std::endl ;
}
inline void writeToFile( const std::vector<double>& balanceValues , const std::string& fileName ) //std::ofstream can't be const( we write to it)
{
    std::ofstream objectFileName ;

    objectFileName.open(fileName) ; //Open the provided object file with the chose name

    if(isFileOpen(objectFileName))
    {
        for( int index = 0 ; index < std::ssize( balanceValues ) ; ++ index )
        {
            objectFileName << balanceValues[ index ] << '\n' ;
        }

        objectFileName.close() ;

    }
    else
        errorOpeningTheFile(fileName) ;
}

#endif
