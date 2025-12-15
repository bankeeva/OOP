#ifndef OBJECT_OBJECT_H
#define OBJECT_OBJECT_H
#pragma once


#include <iostream>
#include <memory>

class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

class ShapeFactory {
public:
    static std::unique_ptr<Shape> createShape(const std::vector<std::string>& type);
};

#endif //OBJECT_OBJECT_H
