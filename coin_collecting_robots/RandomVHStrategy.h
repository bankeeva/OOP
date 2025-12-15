#pragma once
#include "Strategy.h"
#include <random>

class RandomVHStrategy final : public Strategy
{
public:
    RandomVHStrategy() {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    void setStart(const int x, const int y) override {
        cur_x = x;
        cur_y = y;
        start_x = x;
        start_y = y;
    }

    void nextMove(Field& field) override {
        Position moves[5];
        int count = 0;

        if (cur_x > 0)
            moves[count++] = {cur_x - 1, cur_y};
        if (cur_x < field.getWidth() - 1)
            moves[count++] = {cur_x + 1, cur_y};
        if (cur_y > 0)
            moves[count++] = {cur_x, cur_y - 1};
        if (cur_y < field.getHeight() - 1)
            moves[count++] = {cur_x, cur_y + 1};

        moves[count++] = {cur_x, cur_y};

        const int index = std::rand() % count;
        cur_x = moves[index].x;
        cur_y = moves[index].y;

        steps++;

        if (field.getCellStatus(cur_x, cur_y) == 1) {
            countPoints++;
            field.setCellStatus(cur_x, cur_y, 0);
        }
    }

    std::string name() const override {
        return "RandomVHStrategy";
    }
};