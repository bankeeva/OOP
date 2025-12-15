#ifndef FACTORY_LINE_H
#define FACTORY_LINE_H

class Line : public Shape {
private:
    std::string x1, y1, x2, y2;
public:
    Line () : x1("0"), y1("0"), x2("0"), y2("0") {}
    Line(const std::string& x1_, const std::string& y1_, const std::string& x2_, const std::string& y2_)
    : x1(x1_), y1(y1_), x2(x2_), y2(y2_) {}

    void draw() override {
        std::cout << "line at (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")" << std::endl;
    }
};

#endif //FACTORY_LINE_H