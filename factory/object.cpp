#include "object.h"
#include "point.h"
#include "rect.h"
#include "circle.h"
#include "line.h"
#include <iostream>
#include <string>
#include <memory>


enum Shapes
{
    POINT,
    RECTANGLE,
    CIRCLE,
    LINE
};


std::unique_ptr<Shape> ShapeFactory::createShape(const std::vector<std::string>& type) {
    const std::string ShapeNames[] = {
        "point",
        "rect",
        "circle",
        "line"
    };

    Shapes s = {};
    for (int i = 0; i < 4; ++i)
        if (type[0] == ShapeNames[i]) s = static_cast<Shapes>(i);

    switch (s)
    {
        case POINT:
            return std::make_unique<Point>(type[1], type[2]);
        case RECTANGLE:
            return std::make_unique<Rect>(type[1], type[2], type[3], type[4]);
        case CIRCLE:
            return std::make_unique<Circle>(type[1], type[2], type[3]);
        case LINE:
            return std::make_unique<Line>(type[1], type[2], type[3], type[4]);
    }

    return nullptr;
}
