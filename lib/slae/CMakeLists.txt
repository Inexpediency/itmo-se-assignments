project(slae)

set(HEADER_FILES
        GaussSolver.h
        Matrix.h
        )

set(SOURCE_FILES
        GaussSolver.cpp
        Matrix.cpp
        )

add_library(slae_lib ${SOURCE_FILES} ${HEADER_FILES})
