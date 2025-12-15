#pragma once
#include <vector>


class Field
{
private:
    int width = -1;
    int height = -1;
    int points = -1;
    std::vector<std::vector<int>> field;
    int counter_moves = 0;
public:
    Field() = default;
    ~Field() = default;

    void setWidth(int width);
    int getWidth() const;
    void setHeight(int height);
    int getHeight() const;
    void setPoints(int points);
    int getPoints() const;
    void initField(int width, int height, int points);
    int getCellStatus(int x, int y) const;
    void setCellStatus(int x, int y, int newStatus);
    void print();
    int getCounterPoints() const;
};
