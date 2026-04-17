cmake_minimum_required(VERSION 3.20)

project(GarndpasPensionDemolisherStrategies LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GarndpasPensionDemolisherStrategies main.cpp
    RandomGen.h
)

include(GNUInstallDirs)
install(TARGETS GarndpasPensionDemolisherStrategies
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
