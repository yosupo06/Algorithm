#include "gtest/gtest.h"
#include "algotest/math/matrix_mod_test.h"

using namespace algotest;

#include "base.h"
#include "math/modint.h"
#include "datastructure/bitvector.h"
#include "math/matrix.h"

using Mint = ModInt<MatrixModTesterBase::kMod>;

struct MatrixModTester : public MatrixModTesterBase {
    int rank(VV<ll> _mat) final {
        Mat<Mint> mat;
        for (auto v: _mat) {
            mat.push_back({});
            for (auto d: v) mat.back().push_back(d);
        }
        return calc_rank(mat);
    }
    long long det(VV<ll> _mat) final {
        Mat<Mint> mat;
        for (auto v: _mat) {
            mat.push_back({});
            for (auto d: v) mat.back().push_back(d);
        }
        return calc_det(mat).v;
    }
    V<ll> linear_equation(VV<ll> _mat, V<ll> _vec) final {
        Mat<Mint> mat;
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
    VV<ll> inverse(VV<ll> _mat) final {
        Mat<Mint> mat;
        for (auto v: _mat) {
            mat.push_back({});
            for (auto d: v) mat.back().push_back(d);
        }
        auto out = ::inverse(mat);
        VV<ll> _out;
        for (auto v: out) {
            _out.push_back({});
            for (auto d: v) _out.back().push_back(d.v);
        }
        return _out;
    }
};

using MatrixModTypes = ::testing::Types<MatrixModTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MyMatrixMod, MatrixModTest, MatrixModTypes);
