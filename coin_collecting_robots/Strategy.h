#pragma once
#include <string>
#include "Field.h"


struct Position {
    int x;
    int y;
};

class Strategy
{
protected:
    int cur_x, cur_y;
    int countPoints = 0;
    int start_x = 0;
    int start_y = 0;
    int steps = 0;
public:
    virtual ~Strategy() = default;
    virtual void setStart(int x, int y) = 0;
    virtual void nextMove(Field& field) = 0;
    virtual std::string name() const = 0;

    int getCount() const {return countPoints;}
    int getSteps() const { return steps; }
    int getStartX() const { return start_x; }
    int getStartY() const { return start_y; }
    int getCurX() const { return cur_x; }
    int getCurY() const { return cur_y; }
    void reset() {
        cur_x = start_x;
        cur_y = start_y;
        steps = 0;
        countPoints = 0;
    }
};
