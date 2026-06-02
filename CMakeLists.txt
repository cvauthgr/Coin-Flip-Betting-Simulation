cmake_minimum_required(VERSION 3.20)

project(SimulatorStrategies LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SimulatorStrategies main.cpp
    RandomGen.h
    FileHandler.h
    Plotting.h
    GamblerInfoClass.h
    StructRelated.h
    Enum.h
    BettingStrategies.h
    SimulatorEngine.h

    MonteCarloWalks.h
    CasesInfo.h
    MonteCarloResultsPrint.h
    ProgramMode.h


)

target_compile_options(SimulatorStrategies PRIVATE -O3)

include(GNUInstallDirs)
install(TARGETS SimulatorStrategies
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
