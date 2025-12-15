#pragma once
#include "Strategy.h"
#include <vector>
#include <random>


class LadderStrategy final : public Strategy
{
    bool move_right_next = true; // true — вправо, false — вниз
public:
    LadderStrategy() {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    void setStart(const int x, const int y) override {
        cur_x = x;
        cur_y = y;
        move_right_next = true;
        start_x = x;
        start_y = y;
    }

    void nextMove(Field& field) override {
        if (move_right_next) {
            if (cur_x + 1 < field.getWidth()) {
                cur_x++;
            }
        } else {
            if (cur_y + 1 < field.getHeight()) {
                cur_y++;
            }
        }

        move_right_next = !move_right_next;
        steps++;
        if (field.getCellStatus(cur_x, cur_y) == 1) {
            countPoints++;
            field.setCellStatus(cur_x, cur_y, 0);
        }
    }

    std::string name() const override {
        return "LadderStrategy";
    }
};
