#ifndef FACTORY_POINT_H
#define FACTORY_POINT_H

#include "object.h"

class Point : public Shape {
private:
    std::string x, y;
public:
    Point() : x("0"), y("0") {}
    Point(const std::string& x_, const std::string& y_) : x(x_), y(y_) {}

    void draw() override {
        std::cout << "point at (" << x << ", " << y << ")" << std::endl;
    }
};

#endif //FACTORY_POINT_H