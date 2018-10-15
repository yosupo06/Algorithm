#include "gtest/gtest.h"
#include "algotest/math/matrix_mod_test.h"

using namespace algotest;

#include "base.h"
#include "math/modint.h"
#include "math/matrix.h"

using Mint = ModInt<MatrixModTesterBase::kMod>;

struct MatrixModTester : public MatrixModTesterBase {
    int rank(VV<ll> _mat) final {
        VV<Mint> mat;
        for (auto v: _mat) {
            mat.push_back({});
            for (auto d: v) mat.back().push_back(d);
        }
        return calc_rank(mat);
    }
    V<ll> linear_equation(VV<ll> _mat, V<ll> _vec) final {
        VV<Mint> mat;
        for (auto v: _mat) {
            mat.push_back({});
            for (auto d: v) mat.back().push_back(d);
        }
        V<Mint> vec;
        for (auto d: _vec) vec.push_back(d);
        auto res = solve_linear(mat, vec);
        V<ll> _res;
        for (auto d: res) _res.push_back(d.v);
        return _res;
    }
};

using MatrixModTypes = ::testing::Types<MatrixModTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MyMatrixMod, MatrixModTest, MatrixModTypes);
