set(TARGET core)

set(Sources
    Figure/Figure.cpp
    Segment/Segment.cpp
    Triangle/Triangle.cpp
)

add_library(${TARGET} SHARED ${Sources})