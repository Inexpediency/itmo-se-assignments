project(infectionSimulator)

set(HEADER_FILES
        InfectionSimulator.h
        )

set(SOURCE_FILES
        InfectionSimulator.cpp
        )

add_library(infectionSimulator_lib ${SOURCE_FILES} ${HEADER_FILES})
