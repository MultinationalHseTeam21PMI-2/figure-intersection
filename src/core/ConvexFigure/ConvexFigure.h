#pragma once

#include <stdexcept>
#include "../Algorithms/Algorithms.h"
#include "../Figure/Figure.h"

class ConvexFigure : public Figure {
private:
    using super = Figure;
protected:

    void ConstructConvexFigure(std::vector<Point> &points) {
        getConvexHull(points, true);

        std::vector<Segment> segments;
        size_t points_size = points.size();
        for (size_t i = 0; i < points_size; i++)
        {
            segments.push_back(Segment(points[i], points[(i+1) % points_size]));
        }

        ConstructFigure(segments);
    }

public:   
    ConvexFigure(std::initializer_list<Point> points_list) {   
        std::vector<Point> points;
        for(auto i: points_list)
        {
            points.push_back(i);
        }
        ConstructConvexFigure(points);
        
    }
    
    ConvexFigure(std::vector<Point> &points) {
        ConstructConvexFigure(points);

    } 
};
