project(slae)

set(HEADER_FILES
        GaussSolver.h
        Matrix.h
        )

add_library(slae_lib INTERFACE ${HEADER_FILES})
