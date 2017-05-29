
#include <iostream>

#include "gtest\gtest.h"

#include "Emblem/Expression.h"
using namespace Emblem;

#include <functional>

const double gDoubleTol = 1e-16;

TEST(BinaryOperatorTest, Addition)
{
    const Expression<double>::Symbol x("x"), y("y");
    const Expression<double>::ValueMap values = { {x, 5.0}, {y, 6.0} };
    const Expression<double> expression = x + y;

    const double exprResult = expression.evaluate(values);
    const double actualResult = values.at(x) + values.at(y);
    ASSERT_NEAR(exprResult, actualResult, gDoubleTol);
}

TEST(BinaryOperatorTest, Subtraction)
{
    const Expression<double>::Symbol x("x"), y("y");
    const Expression<double>::ValueMap values = { { x, 5.0 },{ y, 6.0 } };
    const Expression<double> expression = x - y;

    const double exprResult = expression.evaluate(values);
    const double actualResult = values.at(x) - values.at(y);
    ASSERT_NEAR(exprResult, actualResult, gDoubleTol);
}

TEST(BinaryOperatorTest, Multiplication)
{
    const Expression<double>::Symbol x("x"), y("y");
    const Expression<double>::ValueMap values = { { x, 5.0 },{ y, 6.0 } };
    const Expression<double> expression = x * y;

    const double exprResult = expression.evaluate(values);
    const double actualResult = values.at(x) * values.at(y);
    ASSERT_NEAR(exprResult, actualResult, gDoubleTol);
}

TEST(BinaryOperatorTest, Division)
{
    const Expression<double>::Symbol x("x"), y("y");
    const Expression<double>::ValueMap values = { { x, 5.0 },{ y, 6.0 } };
    const Expression<double> expression = x / y;

    const double exprResult = expression.evaluate(values);
    const double actualResult = values.at(x) / values.at(y);
    ASSERT_NEAR(exprResult, actualResult, gDoubleTol);
}

TEST(UnaryOperatorTest, Sin)
{
    const Expression<double>::Symbol x("x");
    const Expression<double>::ValueMap values = { { x, 5.0 } };
    const Expression<double> expression = sin(x);

    const double exprResult = expression.evaluate(values);
    const double actualResult = sin(values.at(x));
    ASSERT_NEAR(exprResult, actualResult, gDoubleTol);
}

TEST(UnaryOperatorTest, Cos)
{
    const Expression<double>::Symbol x("x");
    const Expression<double>::ValueMap values = { { x, 5.0 } };
    const Expression<double> expression = cos(x);

    const double exprResult = expression.evaluate(values);
    const double actualResult = cos(values.at(x));
    ASSERT_NEAR(exprResult, actualResult, gDoubleTol);
}

TEST(UnaryOperatorTest, Tan)
{
    const Expression<double>::Symbol x("x");
    const Expression<double>::ValueMap values = { { x, 5.0 } };
    const Expression<double> expression = tan(x);

    const double exprResult = expression.evaluate(values);
    const double actualResult = tan(values.at(x));
    ASSERT_NEAR(exprResult, actualResult, gDoubleTol);
}

TEST(UnaryOperatorTest, Abs)
{
    const Expression<double>::Symbol x("x");
    const Expression<double>::ValueMap values = { { x, -5.0 } };
    const Expression<double> expression = abs(x);

    const double exprResult = expression.evaluate(values);
    const double actualResult = abs(values.at(x));
    ASSERT_NEAR(exprResult, actualResult, gDoubleTol);
}

TEST(UnaryOperatorTest, Log)
{
    const Expression<double>::Symbol x("x");
    const Expression<double>::ValueMap values = { { x, 5.0 } };
    const Expression<double> expression = log(x);

    const double exprResult = expression.evaluate(values);
    const double actualResult = log(values.at(x));
    ASSERT_NEAR(exprResult, actualResult, gDoubleTol);
}

TEST(UnaryOperatorTest, Log10)
{
    const Expression<double>::Symbol x("x");
    const Expression<double>::ValueMap values = { { x, 5.0 } };
    const Expression<double> expression = log10(x);

    const double exprResult = expression.evaluate(values);
    const double actualResult = log10(values.at(x));
    ASSERT_NEAR(exprResult, actualResult, gDoubleTol);
}

TEST(UnaryOperatorTest, Exp)
{
    const Expression<double>::Symbol x("x");
    const Expression<double>::ValueMap values = { { x, 5.0 } };
    const Expression<double> expression = exp(x);

    const double exprResult = expression.evaluate(values);
    const double actualResult = exp(values.at(x));
    ASSERT_NEAR(exprResult, actualResult, gDoubleTol);
}

TEST(UnaryOperatorTest, Sqrt)
{
    const Expression<double>::Symbol x("x");
    const Expression<double>::ValueMap values = { { x, 5.0 } };
    const Expression<double> expression = sqrt(x);

    const double exprResult = expression.evaluate(values);
    const double actualResult = sqrt(values.at(x));
    ASSERT_NEAR(exprResult, actualResult, gDoubleTol);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    std::cin.get();
    return ret;
}