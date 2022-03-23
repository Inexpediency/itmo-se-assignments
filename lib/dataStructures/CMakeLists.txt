project(dataStructures)

set(HEADER_FILES
        Container.h
        List.h
        )

add_library(dataStructures_lib INTERFACE ${HEADER_FILES})
