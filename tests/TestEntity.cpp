#include <gtest/gtest.h>
#include "entity/Entity.h"


TEST(SquareRootTest, PositiveNos) {
    ASSERT_EQ(6,    std::sqrt(36.0));
    ASSERT_EQ(18.0, std::sqrt(324.0));
    ASSERT_EQ(25.4, std::sqrt(645.16));
    ASSERT_EQ(0,    std::sqrt(0.0));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
