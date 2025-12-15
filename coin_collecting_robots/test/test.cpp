#include <gtest/gtest.h>
#include "../Field.h"
#include "../GreedyStrategy.h"
#include "../BounceStrategy.h"
#include "../LadderStrategy.h"
#include "../RandomVHStrategy.h"
#include "../RandomDStrategy.h"



// field

// проверяем что поле корректно инициализируется
TEST(FieldTest, InitFieldCorrectSize)
{
    Field f;
    f.initField(5, 4, 3);

    EXPECT_EQ(f.getWidth(), 5);
    EXPECT_EQ(f.getHeight(), 4);
    EXPECT_EQ(f.getPoints(), 3);
}

// setCellStatus изменяет состояние клетки
TEST(FieldTest, SetCellStatusChangesValue)
{
    Field f;
    f.initField(3, 3, 0);

    f.setCellStatus(1, 1, 1);
    EXPECT_EQ(f.getCellStatus(1, 1), 1);
}

// что подсчёт монет работает корректно
TEST(FieldTest, CountPointsWorks)
{
    Field f;
    f.initField(3, 3, 0);

    f.setCellStatus(0, 0, 1);
    f.setCellStatus(1, 1, 1);
    f.setCellStatus(2, 2, 1);

    EXPECT_EQ(f.getCounterPoints(), 3);
}

// стратегии

// корректная установка стартовой позиции
TEST(StrategyTest, SetStartCorrect)
{
    GreedyStrategy s;
    s.setStart(2, 3);

    EXPECT_EQ(s.getStartX(), 2);
    EXPECT_EQ(s.getStartY(), 3);
    EXPECT_EQ(s.getCurX(), 2);
    EXPECT_EQ(s.getCurY(), 3);
}

// функция reset()
TEST(StrategyTest, ResetWorks)
{
    RandomVHStrategy s;
    Field f;
    f.initField(5, 5, 0);

    s.setStart(1, 1);

    s.nextMove(f);
    s.nextMove(f);

    s.reset();

    EXPECT_EQ(s.getCurX(), 1);
    EXPECT_EQ(s.getCurY(), 1);
    EXPECT_EQ(s.getSteps(), 0);
    EXPECT_EQ(s.getCount(), 0);
}

// движение

// GreedyStrategy должна собирать монеты, если они рядом
TEST(GreedyStrategyTest, GreedyCollectsCoin)
{
    Field f;
    f.initField(3, 3, 0);

    f.setCellStatus(1, 1, 1);

    GreedyStrategy s;
    s.setStart(0, 0);

    for (int i = 0; i < 5; i++)
        s.nextMove(f);

    EXPECT_GE(s.getCount(), 1);
}

// BounceStrategy должна ходить внутри поля и не выходить за границы
TEST(BounceStrategyTest, BounceMovesInsideField)
{
    Field f;
    f.initField(4, 2, 0);

    BounceStrategy s;
    s.setStart(0, 0);

    for (int i = 0; i < 10; i++)
        s.nextMove(f);

    EXPECT_GE(s.getCurX(), 0);
    EXPECT_LT(s.getCurX(), f.getWidth());
    EXPECT_GE(s.getCurY(), 0);
    EXPECT_LT(s.getCurY(), f.getHeight());
}

// LadderStrategy должна чередовать: вправо → вниз → вправо → вниз
TEST(LadderStrategyTest, LadderAlternatesMoves)
{
    Field f;
    f.initField(5, 5, 0);

    LadderStrategy s;
    s.setStart(0, 0);

    s.nextMove(f);
    int x1 = s.getCurX();
    int y1 = s.getCurY();

    s.nextMove(f);
    int x2 = s.getCurX();
    int y2 = s.getCurY();

    EXPECT_EQ(x1, 1);
    EXPECT_EQ(y1, 0);
    EXPECT_EQ(x2, 1);
    EXPECT_EQ(y2, 1);
}

// RandomVHStrategy должна оставаться в границах поля
TEST(RandomVHStrategyTest, RandomVHStaysInsideField)
{
    Field f;
    f.initField(3, 3, 0);

    RandomVHStrategy s;
    s.setStart(1, 1);

    for (int i = 0; i < 20; i++)
        s.nextMove(f);

    EXPECT_GE(s.getCurX(), 0);
    EXPECT_LE(s.getCurX(), 2);
    EXPECT_GE(s.getCurY(), 0);
    EXPECT_LE(s.getCurY(), 2);
}

// RandomDStrategy должна оставаться в границах
TEST(RandomDStrategyTest, RandomDDiagonalOrStay)
{
    Field f;
    f.initField(3, 3, 0);

    RandomDStrategy s;
    s.setStart(1, 1);

    for (int i = 0; i < 20; i++)
        s.nextMove(f);

    EXPECT_GE(s.getCurX(), 0);
    EXPECT_LE(s.getCurX(), 2);
    EXPECT_GE(s.getCurY(), 0);
    EXPECT_LE(s.getCurY(), 2);
}
