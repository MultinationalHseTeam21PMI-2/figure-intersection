set(TARGET core)

set(Sources
    Point/Point.cpp
    Figure/Figure.cpp
    Segment/Segment.cpp
    Triangle/Triangle.cpp
    ConvexFigure/ConvexFigure.cpp
    Algorithms/Algorithms.cpp
)

add_library(${TARGET} SHARED ${Sources})