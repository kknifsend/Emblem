
#include "gtest\gtest.h"

#include "Emblem/Expression.h"
using namespace Emblem;

TEST(TestStub, Stub)
{
    EXPECT_EQ(5, 5);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}