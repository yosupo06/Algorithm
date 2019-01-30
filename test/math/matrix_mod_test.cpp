#include "gtest/gtest.h"
#include "algotest/math/matrix_mod_test.h"

using namespace algotest;

#include "base.h"
#include "bitop.h"
#include "util/random.h"
#include "math/modint.h"
#include "datastructure/bitvector.h"
#include "math/matrix.h"
#include "math/poly.h"

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

struct BMDetTester : public MatrixModTesterBase {
    int rank(VV<ll>) final { return 0; }
    ll det(VV<ll> mat) final {
        struct E { int to; Mint f; };
        int n = int(mat.size());
        VV<E> edges(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                edges[i].push_back(E{j, Mint(mat[i][j])});
            }
        }
        return sparse_det(edges).v;
    }
    V<ll> linear_equation(VV<ll>, V<ll>) final { return {}; }
    VV<ll> inverse(VV<ll>) final { return {}; }
};


INSTANTIATE_TYPED_TEST_CASE_P(MatrixMod, MatrixModRankTest, ::testing::Types<MatrixModTester>);
using MatrixDetTypes = ::testing::Types<MatrixModTester, BMDetTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MatrixMod, MatrixModDetTest, MatrixDetTypes);
INSTANTIATE_TYPED_TEST_CASE_P(MatrixMod, MatrixModLinearEquationTest, ::testing::Types<MatrixModTester>);
INSTANTIATE_TYPED_TEST_CASE_P(MatrixMod, MatrixModInverseTest, ::testing::Types<MatrixModTester>);
