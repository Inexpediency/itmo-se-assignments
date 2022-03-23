project(io)

set(HEADER_FILES
        ioutils.h
        )

add_library(io_lib INTERFACE ${HEADER_FILES})
