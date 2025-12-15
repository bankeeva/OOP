#include "Vector.hpp"
#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>

// Тест конструктора по умолчанию
TEST(VectorTest, DefaultConstructor) {
    const Vector v;
    EXPECT_DOUBLE_EQ(v.x(), 0.0);
    EXPECT_DOUBLE_EQ(v.y(), 0.0);
}

// Тест конструктора с параметрами
TEST(VectorTest, ParameterizedConstructor) {
    const Vector v(3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.x(), 3.0);
    EXPECT_DOUBLE_EQ(v.y(), 4.0);
}

// Тест конструктора копирования
TEST(VectorTest, CopyConstructor) {
    const Vector v1(1.0, 2.0);
    Vector v2(v1);
    EXPECT_DOUBLE_EQ(v2.x(), 1.0);
    EXPECT_DOUBLE_EQ(v2.y(), 2.0);
}

// Тест оператора присваивания
TEST(VectorTest, AssignmentOperator) {
    const Vector v1(5.0, 6.0);
    Vector v2;
    v2 = v1;
    EXPECT_DOUBLE_EQ(v2.x(), 5.0);
    EXPECT_DOUBLE_EQ(v2.y(), 6.0);
}

// Тест makePolar
TEST(VectorTest, MakePolar) {
    const double r = 1.0;
    const double angle = M_PI / 4; // 45 градусов
    const Vector v = Vector::makePolar(r, angle);
    EXPECT_NEAR(v.x(), std::cos(angle), 1e-9);
    EXPECT_NEAR(v.y(), std::sin(angle), 1e-9);
}

// Операторы +, -, *, / (Vector)
TEST(VectorTest, AdditionOperator) {
    Vector v1(1, 2);
    Vector v2(3, 4);
    Vector v3 = v1 + v2;
    EXPECT_DOUBLE_EQ(v3.x(), 4);
    EXPECT_DOUBLE_EQ(v3.y(), 6);
}

TEST(VectorTest, SubtractionOperator) {
    Vector v1(5, 7);
    Vector v2(2, 3);
    Vector v3 = v1 - v2;
    EXPECT_DOUBLE_EQ(v3.x(), 3);
    EXPECT_DOUBLE_EQ(v3.y(), 4);
}

TEST(VectorTest, DotProduct) {
    Vector v1(1, 2);
    Vector v2(3, 4);
    double dot = v1 * v2;
    EXPECT_DOUBLE_EQ(dot, 1*3 + 2*4);
}

// Умножение на число
TEST(VectorTest, ScalarMultiplication) {
    Vector v(2, 3);
    Vector res = v * 2;
    EXPECT_DOUBLE_EQ(res.x(), 4);
    EXPECT_DOUBLE_EQ(res.y(), 6);

    res = 2 * v; // оператор с числом слева
    EXPECT_DOUBLE_EQ(res.x(), 4);
    EXPECT_DOUBLE_EQ(res.y(), 6);
}

// Деление на число и проверка исключения
TEST(VectorTest, ScalarDivision) {
    Vector v(4, 6);
    Vector res = v / 2;
    EXPECT_DOUBLE_EQ(res.x(), 2);
    EXPECT_DOUBLE_EQ(res.y(), 3);

    EXPECT_THROW(v / 0, std::runtime_error);
}

// Операторы +=, -=, *=, /= и проверка исключения
TEST(VectorTest, PlusEquals) {
    Vector v1(1, 1);
    Vector v2(2, 3);
    v1 += v2;
    EXPECT_DOUBLE_EQ(v1.x(), 3);
    EXPECT_DOUBLE_EQ(v1.y(), 4);
}

TEST(VectorTest, MinusEquals) {
    Vector v1(5, 5);
    Vector v2(2, 3);
    v1 -= v2;
    EXPECT_DOUBLE_EQ(v1.x(), 3);
    EXPECT_DOUBLE_EQ(v1.y(), 2);
}

TEST(VectorTest, MultiplyEquals) {
    Vector v(3, 4);
    v *= 2;
    EXPECT_DOUBLE_EQ(v.x(), 6);
    EXPECT_DOUBLE_EQ(v.y(), 8);
}

TEST(VectorTest, DivideEquals) {
    Vector v(8, 6);
    v /= 2;
    EXPECT_DOUBLE_EQ(v.x(), 4);
    EXPECT_DOUBLE_EQ(v.y(), 3);

    EXPECT_THROW(v /= 0, std::runtime_error);
}

// Унарный минус
TEST(VectorTest, UnaryMinus) {
    Vector v(3, -4);
    Vector neg = -v;
    EXPECT_DOUBLE_EQ(neg.x(), -3);
    EXPECT_DOUBLE_EQ(neg.y(), 4);
}

// Операторы сравнения == и !=
TEST(VectorTest, EqualityOperators) {
    Vector v1(1, 2);
    Vector v2(1, 2);
    Vector v3(2, 3);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
    EXPECT_TRUE(v1 != v3);
    EXPECT_FALSE(v1 != v2);
}

// Поворот (радианы)
TEST(VectorTest, RotateByAngle) {
    Vector v(1, 0);
    v.rotate(M_PI / 2); // повернуть на 90 градусов
    EXPECT_NEAR(v.x(), 0, 1e-9);
    EXPECT_NEAR(v.y(), 1, 1e-9);
}

// Поворот (кратные 90 градусов)
TEST(VectorTest, RotateByDegrees) {
    Vector v(1, 0);
    v.rotate(90);
    EXPECT_DOUBLE_EQ(v.x(), 0);
    EXPECT_DOUBLE_EQ(v.y(), 1);

    v.rotate(90); // теперь 180
    EXPECT_DOUBLE_EQ(v.x(), -1);
    EXPECT_DOUBLE_EQ(v.y(), 0);

    v.rotate(90); // теперь 270
    EXPECT_DOUBLE_EQ(v.x(), 0);
    EXPECT_DOUBLE_EQ(v.y(), -1);

    v.rotate(90); // теперь 0 (360)
    EXPECT_DOUBLE_EQ(v.x(), 1);
    EXPECT_DOUBLE_EQ(v.y(), 0);
}

// Length и module2
TEST(VectorTest, LengthAndModule2) {
    Vector v(3, 4);
    EXPECT_DOUBLE_EQ(v.module2(), 25);
    EXPECT_DOUBLE_EQ(v.length(), 5);
}

// Угол (радианы)
TEST(VectorTest, Angle) {
    Vector v(0, 1);
    EXPECT_DOUBLE_EQ(v.angle(), M_PI / 2);

    Vector v2(1, 0);
    EXPECT_DOUBLE_EQ(v2.angle(), 0);

    Vector v3(-1, 0);
    EXPECT_DOUBLE_EQ(v3.angle(), M_PI);
}

// Угол между векторами и проверка исключения (нуль-вектор)
TEST(VectorTest, AngleBetweenVectors) {
    Vector v1(1, 0);
    Vector v2(0, 1);
    EXPECT_DOUBLE_EQ(v1.angle(v2), M_PI / 2);

    Vector zero(0, 0);
    EXPECT_THROW(v1.angle(zero), std::runtime_error);
}

// Проекция и проверка исключения (нуль-вектор)
TEST(VectorTest, Projection) {
    Vector v(3, 4);
    Vector base(1, 0);
    double proj = v.projection(base);
    EXPECT_DOUBLE_EQ(proj, 3);

    Vector zero(0, 0);
    EXPECT_THROW(v.projection(zero), std::runtime_error);
}

// Нормализация (нормальный и нулевой вектор)
TEST(VectorTest, Normalize) {
    Vector v(3, 4);
    v.normalize();
    EXPECT_NEAR(v.length(), 1.0, 1e-9);

    Vector zero(0, 0);
    zero.normalize(); // не должно бросать
    EXPECT_DOUBLE_EQ(zero.x(), 0);
    EXPECT_DOUBLE_EQ(zero.y(), 0);
}

// TransformTo и TransformFrom и исключения
TEST(VectorTest, TransformToAndFrom) {
    Vector v(1, 0);
    Vector e1(0, 1);
    Vector e2(-1, 0);

    Vector transformed = v.transformTo(e1, e2);
    EXPECT_NEAR(transformed.x(), 0, 1e-9);
    EXPECT_NEAR(transformed.y(), -1, 1e-9);

    Vector original = transformed.transformFrom(e1, e2);
    EXPECT_NEAR(original.x(), 1, 1e-9);
    EXPECT_NEAR(original.y(), 0, 1e-9);

    Vector e3(1, 0);
    Vector e4(2, 0); // линейно зависимые векторы, det = 0
    EXPECT_THROW(v.transformTo(e3, e4), std::runtime_error);
}

// Тест свободных функций

TEST(VectorTest, FreeFunctionRotateAngle) {
    Vector v(1, 0);
    Vector rotated = rotate(v, M_PI / 2);
    EXPECT_NEAR(rotated.x(), 0, 1e-9);
    EXPECT_NEAR(rotated.y(), 1, 1e-9);
}

TEST(VectorTest, FreeFunctionRotateDegrees) {
    Vector v(1, 0);
    Vector rotated = rotate(v, 90);
    EXPECT_DOUBLE_EQ(rotated.x(), 0);
    EXPECT_DOUBLE_EQ(rotated.y(), 1);
}

TEST(VectorTest, FreeFunctionModule2LengthAngle) {
    Vector v(3, 4);
    EXPECT_DOUBLE_EQ(module2(v), 25);
    EXPECT_DOUBLE_EQ(length(v), 5);
    EXPECT_DOUBLE_EQ(angle(v), atan2(4,3));
}

TEST(VectorTest, FreeFunctionAngleBetweenVectors) {
    Vector v1(1, 0);
    Vector v2(0, 1);
    EXPECT_DOUBLE_EQ(angle(v1, v2), M_PI / 2);

    Vector zero(0, 0);
    EXPECT_THROW(angle(v1, zero), std::runtime_error);
}

TEST(VectorTest, FreeFunctionProjection) {
    Vector v(3, 4);
    Vector base(1, 0);
    EXPECT_DOUBLE_EQ(projection(v, base), 3);

    Vector zero(0, 0);
    EXPECT_THROW(projection(v, zero), std::runtime_error);
}

TEST(VectorTest, FreeFunctionNormalize) {
    Vector v(3, 4);
    Vector norm = normalize(v);
    EXPECT_NEAR(norm.length(), 1, 1e-9);

    Vector zero(0, 0);
    norm = normalize(zero);
    EXPECT_DOUBLE_EQ(norm.x(), 0);
    EXPECT_DOUBLE_EQ(norm.y(), 0);
}

TEST(VectorTest, FreeFunctionTransformToFrom) {
    Vector v(1, 0);
    Vector e1(0, 1);
    Vector e2(-1, 0);

    Vector transformed = transformTo(v, e1, e2);
    EXPECT_NEAR(transformed.x(), 0, 1e-9);
    EXPECT_NEAR(transformed.y(), -1, 1e-9);

    Vector original = transformFrom(transformed, e1, e2);
    EXPECT_NEAR(original.x(), 1, 1e-9);
    EXPECT_NEAR(original.y(), 0, 1e-9);

    Vector e3(1, 0);
    Vector e4(2, 0); // det == 0
    EXPECT_THROW(transformTo(v, e3, e4), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
