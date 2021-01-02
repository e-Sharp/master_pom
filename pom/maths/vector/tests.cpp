#include "pom/maths/function/interpolation.hpp"
#include "pom/maths/vector/all.hpp"

#include <catch2/catch.hpp>

using namespace pom;

TEST_CASE("Equality of vectors.", "[vector]") {
    SECTION("Reflexivity.") {
        auto v = vector<traits::vector<int, 3>>{1, 2, 3};
        REQUIRE(v == v);
    }
    SECTION("Not equal.") {
        auto l = vector<traits::vector<int, 3>>{1, 2, 3};
        auto r = vector<traits::vector<int, 3>>{1, 2, 4};
        REQUIRE_FALSE(l == r);
    }
}

TEST_CASE("Linear interpolation of vectors.", "[vector]") {
    constexpr auto lhs = vector<traits::vector<float, 3>>{1.f, 3.f, 5.f};
    constexpr auto rhs = vector<traits::vector<float, 3>>{2.f, 4.f, 6.f};
    constexpr auto r = lerp(lhs, rhs, 0.5f);
    constexpr auto ex = vector<traits::vector<float, 3>>{1.5f, 3.5f, 5.5f};
    REQUIRE(r == ex);
}

TEST_CASE("Dot product of vectors.", "[vector]") {
    auto lhs = vector<traits::vector<int, 3>>{1, 2, 3};
    auto rhs = vector<traits::vector<int, 3>>{4, 5, 6};
    REQUIRE(dot(lhs, rhs) == 32);
}

TEST_CASE("Floored vector.", "[vector]") {
    auto v = vector<traits::vector<float, 3>>{-0.9f, 2.3f, 3.9f};
    auto ex = vector<traits::vector<float, 3>>{-1.f, 2.f, 3.f};
    REQUIRE(floored(v) == ex);
}
