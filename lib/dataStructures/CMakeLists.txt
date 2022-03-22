project(dataStructures)

set(HEADER_FILES
        Container.h
        RingList.h
        )

set(SOURCE_FILES
        RingList.cpp
        )

add_library(dataStructures_lib ${SOURCE_FILES} ${HEADER_FILES})
