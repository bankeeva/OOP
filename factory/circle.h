#ifndef FACTORY_CIRCLE_H
#define FACTORY_CIRCLE_H

class Circle : public Shape {
private:
    std::string x, y, r;
public:
    Circle() : x("0"), y("0"), r("0") {}
    Circle(const std::string& x_, const std::string& y_, const std::string& r_)
    : x(x_), y(y_), r(r_) {}

    void draw() override {
        std::cout << "circle at (" << x << ", " << y << "), rad = " << r << std::endl;
    }
};

#endif //FACTORY_CIRCLE_H