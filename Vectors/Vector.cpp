#include "Vector.hpp"
#include <cmath>
#include <stdexcept>


Vector::Vector(): _x(0.0), _y(0.0){}

Vector::Vector(const double x, const double y): _x(x), _y(y) {}

Vector::Vector(const Vector& that): _x(that._x), _y(that._y){}

Vector& Vector::operator=(const Vector& that) {
    _x = that._x;
    _y = that._y;

    return *this;
}

Vector Vector::makePolar(const double rad, const double alpha) {
    const double x = rad * cos(alpha);
    const double y = rad * sin(alpha);

    return Vector(x, y);
}

double Vector::x() const {
    return _x;
}

double Vector::y() const {
    return _y;
}

void Vector::x(const double newX) {
    _x = newX;
}

void Vector::y(const double newY) {
    _y = newY;
}

Vector Vector::operator+(const Vector& that) const {
    const double newX = _x + that.x();
    const double newY = _y + that.y();

    return Vector(newX, newY);
}

Vector Vector::operator-(const Vector& that) const {
    const double newX = _x - that.x();
    const double newY = _y - that.y();

    return Vector(newX, newY);
}

double Vector::operator*(const Vector& that) const {
    const double scalPr = _x * that.x() + _y * that.y();

    return scalPr;
}

Vector Vector::operator*(const double& that) const {
    const double newX = _x * that;
    const double newY = _y * that;

    return Vector(newX, newY);
}

Vector Vector::operator/(const double& that) const {
    if (that == 0.0)
        throw std::runtime_error("Сannot be divided by zero.");

    const double newX = _x / that;
    const double newY = _y / that;

    return Vector(newX, newY);
}

Vector& Vector::operator+=(const Vector& that) {
    this->_x += that.x();
    this->_y += that.y();

    return *this;
}

Vector& Vector::operator-=(const Vector& that) {
    this->_x -= that.x();
    this->_y -= that.y();

    return *this;
}

Vector& Vector::operator*=(const double& that) {
    this->_x *= that;
    this->_y *= that;

    return *this;
}

Vector& Vector::operator/=(const double& that) {
    if (that == 0.0)
        throw std::runtime_error("Сannot be divided by zero.");

    this->_x /= that;
    this->_y /= that;

    return *this;
}

Vector Vector::operator-() const {
    return Vector(-_x, -_y);
}

bool Vector::operator==(const Vector& that) const {

    return _x == that.x() && _y == that.y();
}

bool Vector::operator!=(const Vector& that) const {

    return _x != that.x() || _y != that.y();
}

Vector& Vector::rotate(const double angle) {
    const double x = this->_x * cos(angle) - this->_y * sin(angle);
    const double y = this->_x * sin(angle) + this->_y * cos(angle);

    this->_x = x;
    this->_y = y;

    return *this;
}

Vector& Vector::rotate(int quad) {
    quad = (quad % 360 + 360) % 360;

    const double x = this->_x;
    const double y = this->_y;

    switch (quad) {
    case 90:
        this->_x = -y;
        this->_y = x;
        break;
    case 180:
        this->_x = -x;
        this->_y = -y;
        break;
    case 270:
        this->_x = y;
        this->_y = -x;
        break;
    default:
        break;
    }

    return *this;
}

double Vector::module2() const {

    return _x * _x + _y * _y;
}

double Vector::length() const {
    return sqrt(module2());
}

double Vector::angle() const {
    const double a = atan2(_y, _x);

    return a;
}

double Vector::angle(const Vector& that) const {
    const double lens = this->length() * that.length();

    if (lens == 0.0)
        throw std::runtime_error("Сannot be divided by zero.");

    const double cs = *this * that / lens;

    return acos(cs);
}


double Vector::projection(const Vector& base) const {
    if (base.module2() == 0.0)
        throw std::runtime_error("Сannot be divided by zero.");

    const double proj = *this * base / base.module2();

    return proj;
}

Vector& Vector::normalize() {
    const double l = this->length();
    if (l > 0)
    {
        this->_x /= l;
        this->_y /= l;
    }

    return *this;
}

Vector& Vector::transformTo(const Vector& e1, const Vector& e2) {
    const double det = e1.x() * e2.y() - e1.y() * e2.x();

    if (det == 0.0)
        throw std::runtime_error("Сannot be divided by zero.");


    const double inv11 = e2.y() / det,
                    inv12 = -e2.x() / det,
                    inv21 = -e1.y() / det,
                    inv22  = e1.x() / det;

    const double x = this->_x;
    const double y = this->_y;

    this->_x = x * inv11 - y * inv12;
    this->_y = x * inv21 - y * inv22;

    return *this;
}

Vector& Vector::transformFrom(const Vector& e1, const Vector& e2) {
    const double x = this->_x;
    const double y = this->_y;

    this->_x = x * e1.x() + y * e2.x();
    this->_y = x * e1.y() + y * e2.y();

    return *this;
}




Vector operator*(const double& lhs, const Vector& rhs) {
    return Vector(rhs.x() * lhs, rhs.y() * lhs);
}

Vector rotate(const Vector& v, double angle) {
    const double x = v.x() * cos(angle) - v.y() * sin(angle);
    const double y = v.x() * sin(angle) + v.y() * cos(angle);

    return Vector(x, y);
}

Vector rotate(const Vector& v, int quad) {
    quad = (quad % 360 + 360) % 360;

    double x = 0;
    double y = 0;

    if (quad == 90)
    {
        x = -v.y();
        y = v.x();
    }
    else if (quad == 180)
    {
        x = -v.x();
        y = -v.y();
    }
    else if (quad == 270)
    {
        x = v.y();
        y = -v.x();
    }

    return Vector(x, y);
}

double module2(const Vector& v) {
    const double m = v.x() * v.x() + v.y() * v.y();

    return m;
}

double length(const Vector& v) {
    const double l = sqrt(v.x() * v.x() + v.y() * v.y());

    return l;
}

double angle(const Vector& v) {
    const double a = atan2(v.y(), v.x());

    return a;
}

double angle(const Vector& v1, const Vector& v2) {
    const double lens = v1.length() * v2.length();

    if (lens == 0.0)
        throw std::runtime_error("Сannot be divided by zero.");

    const double cs = v1 * v2 / lens;

    return acos(cs);
}

double projection(const Vector& v, const Vector& base) {
    if (base.module2() == 0.0)
        throw std::runtime_error("Сannot be divided by zero.");

    const double proj = v * base / base.module2();

    return proj;
}

Vector normalize(const Vector& v) {
    double x = v.x();
    double y = v.y();
    const double l = v.length();

    if (l > 0)
    {
        x = x / l;
        y = y / l;
    }
    return Vector(x, y);
}

Vector transformTo(const Vector& v, const Vector& e1, const Vector& e2) {
    const double det = e1.x() * e2.y() - e1.y() * e2.x();

    if (det == 0.0)
        throw std::runtime_error("Сannot be divided by zero.");

    const double inv11 = e2.y() / det,
                    inv12 = -e2.x() / det,
                    inv21 = -e1.y() / det,
                    inv22  = e1.x() / det;

    const double x = v.x() * inv11 - v.y() * inv12;
    const double y = v.x() * inv21 - v.y() * inv22;

    return Vector(x, y);
}

Vector transformFrom(const Vector& v, const Vector& e1, const Vector& e2) {
    const double x = v.x() * e1.x() + v.y() * e2.x();
    const double y = v.x() * e1.y() + v.y() * e2.y();

    return Vector(x, y);
}
