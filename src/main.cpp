#include <iostream>
#include "core/Segment/Segment.h"
#define PRECISION 0.001


int main() {
    Point a(-6.67,3.5), b(4.09,4.62), c(11.467539,5.3879223), d(-2.1667461, 3.96874017);
    Segment X(a,b), Y(c,d);
    Segment Intersection_XY = *Segment::intersection(X,Y);
    if(Intersection_XY.point1() == d && Intersection_XY.point2() == b) {
        std::cout << "TEST #1: SUCCESS\n";
    }
    else std::cout << "TEST #1: FAIL\n";
    Point E(-5.03,7.72), F(-2.39,1.34);
    Segment Z(E,F);
    Intersection_XY = *Segment::intersection(X,Z);
    if(Intersection_XY.point1() == Intersection_XY.point2() && (Point(Intersection_XY.point1().x - (-3.42362), Intersection_XY.point1().y - 3.83791 )).norm() < PRECISION) {
        std::cout << "TEST #2: SUCCESS\n";
    }
    else std::cout << "TEST #2: FAIL\n";
    Point x_A(1,3), x_B(1,7), x_C(1.00001,4.5), x_D(1,9);
    Segment first = Segment(x_A, x_B), second = Segment(x_C, x_D);
    Intersection_XY = *Segment::intersection(first, second);
    if(Intersection_XY.point1() == x_C && Intersection_XY.point2() == x_B) {
        std::cout << "TEST #3: SUCCESS\n";
    }
    else std::cout << "TEST #3: FAIL\n";


    return 0;
}