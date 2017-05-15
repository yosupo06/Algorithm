#include "gtest/gtest.h"

#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <random>
#include <array>

using namespace std;

#include "base.h"

#include "graph/scc.h"
#include "graph/twosat.h"
#include "string/suffixarray.h"
#include "random.h"

#include "gcd_test.h"
#include "sa_test.h"
#include "twosat_test.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
