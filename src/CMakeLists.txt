

set(SOURCES
    main.cpp
    RiscV.cpp
    Log.cpp
    Instruction.cpp
)
add_executable(RiscVSim ${SOURCES})

include_directories(../include)