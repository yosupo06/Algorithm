#include "gtest/gtest.h"
#include "algotest/datastructure/wavelet_test.h"

using namespace algotest;

#include "base.h"
#include "datastructure/wavelet.h"


struct WaveletTester : public WaveletTesterBase {
    Wavelet wt;
    void setup(V<int> a) final {
        wt = Wavelet(a);
    }
    int rank(int l, int r, int x) final {
        return wt.rank(l, r, x);
    }
    int select(int l, int r, int k) final {
        return wt.select(l, r, k);
    }
};

using WaveletTypes = ::testing::Types<WaveletTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MyWavelet, WaveletTest, WaveletTypes);
