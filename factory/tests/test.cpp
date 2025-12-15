#include <gtest/gtest.h>
#include <sstream>
#include "../object.h"
#include "../point.h"
#include "../rect.h"
#include "../circle.h"
#include "../line.h"

TEST(ShapeFactoryTest, CreatePoint) {
    std::vector<std::string> args = {"point", "10", "20"};
    auto shape = ShapeFactory::createShape(args);
    ASSERT_NE(shape, nullptr);

    std::string out = captureOutput(std::move(shape));
    EXPECT_EQ(out, "point at (10, 20)\n");
}
