set(TARGET core)

set(Sources
    Point/Point.cpp
    Figure/Figure.cpp
    Segment/Segment.cpp
    Triangle/Triangle.cpp
    Alghoritms/Alghoritms.cpp
)

add_library(${TARGET} SHARED ${Sources})