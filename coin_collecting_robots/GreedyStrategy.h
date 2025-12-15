#pragma once
#include "Strategy.h"
#include <vector>
#include <random>


class GreedyStrategy final : public Strategy
{
public:
    GreedyStrategy() {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    void setStart(const int x, const int y) override {
        cur_x = x;
        cur_y = y;
        start_x = x;
        start_y = y;
    }

    void nextMove(Field& field) override {
        Position coinMove[8];
        Position moves[8];
        int countCoin = 0;
        int count = 0;

        for (int _x = -1; _x < 2; _x++)
        {
            for (int _y = -1; _y < 2; _y++)
            {
                if (cur_x + _x >= 0 && cur_x + _x < field.getWidth() && cur_y + _y >= 0 && cur_y + _y < field.getHeight())
                {
                    if (field.getCellStatus(cur_x + _x, cur_y + _y) == 1)
                        coinMove[countCoin++] = {cur_x + _x, cur_y + _y};
                    else
                        moves[count++] = {cur_x + _x, cur_y + _y};
                }
            }
        }

        Position nextPos{};
        if (countCoin != 0) {
            const int index = std::rand() % countCoin;
            nextPos = coinMove[index];
        } else {
            const int index = std::rand() % count;
            nextPos = moves[index];
        }

        cur_x = nextPos.x;
        cur_y = nextPos.y;

        steps++;

        if (field.getCellStatus(cur_x, cur_y) == 1)
        {
            countPoints++;
            field.setCellStatus(cur_x, cur_y, 0);
        }
    }

    std::string name() const override {
        return "GreedyStrategy";
    }
};
