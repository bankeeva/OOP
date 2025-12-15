#include "Field.h"
#include <iostream>
#include <random>
#include <algorithm>


void Field::setWidth(int w)
{
    if (w > 0)
        width = w;
    else
    {
        std::cerr << "Ошибка: ширина должна быть больше 0!\n";
        exit(0);
    }
}

int Field::getWidth() const
{
    return width;
}

void Field::setHeight(int h)
{
    if (h > 0)
        height = h;
    else
    {
        std::cerr << "Ошибка: высота должна быть больше 0!\n";
        exit(0);
    }
}

int Field::getHeight() const
{
    return height;
}

void Field::setPoints(int p)
{
    if (p >= 0 && p <= width * height)
        points = p;
    else
    {
        std::cerr << "Ошибка: кол-во монет должно быть не меньше 0 и меньше значения (высота * ширина)!\n";
        exit(0);
    }
}

int Field::getPoints() const
{
    return points;
}

void Field::initField(int w, int h, int p)
{
    setWidth(w);
    setHeight(h);
    setPoints(p);
    
    field.resize(height, std::vector<int>(width, 0));

    std::vector<int> temp_field(width * height, 0);
    for (int i = 0; i < p; i++) temp_field[i] = 1;

    std::shuffle(temp_field.begin(), temp_field.end(), std::mt19937{std::random_device{}()});

    int k = 0;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            field[i][j] = temp_field[k++];
}

int Field::getCellStatus(const int x, const int y) const
{
    return field[y][x];
}

void Field::setCellStatus(const int x, const int y, const int newStatus)
{
    field[y][x] = newStatus;
}

void Field::print()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << getCellStatus(j, i) << " ";
        }
        std::cout << std::endl;
    }
}

int Field::getCounterPoints() const
{
    int counter = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (getCellStatus(j, i) == 1) counter++;
        }
    }
    return counter;
}
