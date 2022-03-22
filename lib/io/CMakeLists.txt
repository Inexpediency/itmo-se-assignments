project(io)

set(HEADER_FILES
        ioutils.h
        )

set(SOURCE_FILES
        ioutils.cpp
        )

add_library(io_lib ${SOURCE_FILES} ${HEADER_FILES})
