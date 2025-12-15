#pragma once
#include "Strategy.h"
#include <vector>
#include <random>


class BounceStrategy final : public Strategy
{
    bool move_right_next = true; // true — вправо, false — вниз
public:
    BounceStrategy() {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    void setStart(const int x, const int y) override {
        cur_x = x;
        cur_y = y;
        start_x = x;
        start_y = y;
        move_right_next = true;
    }

    void nextMove(Field& field) override {
        if (move_right_next) {
            if (cur_x + 1 < field.getWidth()) {
                cur_x++;
            } else {
                move_right_next = false;
                if (cur_y + 1 < field.getHeight()) {
                    cur_y++;
                }
            }
        } else {
            if (cur_x - 1 >= 0) {
                cur_x--;
            } else {
                move_right_next = true;
                if (cur_y + 1 < field.getHeight()) {
                    cur_y++;
                }
            }
        }

        steps++;

        if (field.getCellStatus(cur_x, cur_y) == 1) {
            countPoints++;
            field.setCellStatus(cur_x, cur_y, 0);
        }
    }

    std::string name() const override {
        return "BounceStrategy";
    }
};
