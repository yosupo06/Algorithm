#include "gtest/gtest.h"

#include "gcd_test.h"
#include "sa_test.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
