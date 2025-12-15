#include <gtest/gtest.h>
#include "BitmapPlusPlus.hpp"
#include <sstream>
#include "img.h"


bool is_pixel_equal(const bmp::Pixel& a, const bmp::Pixel& b) {
    return a.r == b.r && a.g == b.g && a.b == b.b;
}


// параллельно оси Х
TEST(DrawLine, Horizontal)
{
    bmp::Bitmap image(10, 10);
    bmp::Pixel color(255, 0, 0);

    Img::draw_line(&image, 1, 2, 8, 2, &color);

    for (int x = 1; x <= 8; x++)
    {
        EXPECT_TRUE(is_pixel_equal(image.get(x, 2), color)) << "Pixel at (" << x << ", 2) должен быть красным";
    }
}

// параллельно оси У
TEST(DrawLine, Vertical)
{
    bmp::Bitmap image(10, 10);
    bmp::Pixel color(255, 0, 0);

    Img::draw_line(&image, 2, 1, 2, 8, &color);

    for (int y = 1; y <= 8; y++)
    {
        EXPECT_TRUE(is_pixel_equal(image.get(2, y), color)) << "Pixel at (" << y << ", 2) должен быть красным";
    }
}

// 45 гр
TEST(DrawLine, 45Degrees)
{
    bmp::Bitmap image(10, 10);
    bmp::Pixel color(255, 0, 0);

    Img::draw_line(&image, 2, 2, 6, 6, &color);

    for (int i = 2; i <= 6; i++)
    {
        EXPECT_TRUE(is_pixel_equal(image.get(i, i), color)) << "Pixel at (" << i << ", " << i << ") должен быть красным";
    }
}

// маленький угол
TEST(DrawLine, SmallAngle)
{
    bmp::Bitmap image(20, 10);
    bmp::Pixel color(255, 0, 0);

    Img::draw_line(&image, 0, 0, 15, 5, &color);

    EXPECT_TRUE(is_pixel_equal(image.get(0, 0), color));
    EXPECT_TRUE(is_pixel_equal(image.get(5, 2), color));
    EXPECT_TRUE(is_pixel_equal(image.get(10, 3), color));
    EXPECT_TRUE(is_pixel_equal(image.get(15, 5), color));
}

// линия пересекает границы изображения
TEST(DrawLine, OutsideBorders)
{
    bmp::Bitmap image(10, 10);
    bmp::Pixel color(255, 0, 0);

    Img::draw_line(&image, -5, -5, 15, 15, &color);

    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(is_pixel_equal(image.get(i, i), color)) << "Pixel at (" << i << ", " << i << ") должен быть красным";
    }
}

// вне изображения
TEST(DrawLine, InsideBorders)
{
    bmp::Bitmap image(10, 10);
    bmp::Pixel color(255, 0, 0);

    Img::draw_line(&image, -10, -10, -1, -1, &color);

    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
            EXPECT_TRUE(!is_pixel_equal(image.get(x, y), color)) << "Pixel at (" << x << ", " << y << ") изменен";
    }
}

// парсиннг ввода
TEST(InputParsing, ParsesValidInputCorrectly)
{
    std::stringstream ss;
    ss << "input.bmp\n1 1\n5 5\n255 0 0\noutput.bmp\n";

    std::string in_bmp, out_bmp;
    int start[2], end[2], r, g, b;

    ss >> in_bmp;
    ss >> start[0] >> start[1];
    ss >> end[0] >> end[1];
    ss >> r >> g >> b;
    ss >> out_bmp;

    EXPECT_EQ(in_bmp, "input.bmp");
    EXPECT_EQ(out_bmp, "output.bmp");
    EXPECT_EQ(start[0], 1);
    EXPECT_EQ(start[1], 1);
    EXPECT_EQ(end[0], 5);
    EXPECT_EQ(end[1], 5);
    EXPECT_EQ(r, 255);
    EXPECT_EQ(g, 0);
    EXPECT_EQ(b, 0);
}

// некорректный ввод
TEST(InputParsingTest, ThrowsOnInvalidInput) {
    std::stringstream ss;
    ss << "input.bmp\n1 1\nA B\n255 0 0\noutput.bmp\n";

    std::string in_bmp, out_bmp;
    int start[2], end[2], r, g, b;

    ss >> in_bmp;
    ss >> start[0] >> start[1];

    bool failed = false;
    try {
        ss >> end[0] >> end[1];

        if (ss.fail()) {
            throw std::ios_base::failure("Invalid input");
        }
    } catch (const std::ios_base::failure&) {
        failed = true;
    }

    EXPECT_TRUE(failed) << "Ожидалась ошибка при чтении некорректных координат (A B), но она не произошла";
}
