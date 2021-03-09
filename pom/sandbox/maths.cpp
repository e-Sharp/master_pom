#include <array>
#include <bitset>
#include <cmath>
#include <iostream>
#include <type_traits>

template<std::size_t D, typename Map, typename Reduce>
struct hypercube {
    static_assert(D > 0 && D <= 8);
    Map map;
    Reduce reduce;
};

template<std::size_t D, typename M, typename R>
auto hypercube_(M m, R r) {
        return hypercube<D, M, R>(m, r);
}

template<std::size_t D, typename M, typename R, std::size_t I>
auto compute(const hypercube<D, M, R>& h, std::bitset<D> bs, std::integral_constant<std::size_t, I> = {}) {
    auto a = compute(h, bs, std::integral_constant<std::size_t, I - 1>());
    bs.set(I - 1);
    auto b = compute(h, bs, std::integral_constant<std::size_t, I - 1>());
    return h.reduce(a, b, I - 1);
}

template<std::size_t D, typename M, typename R>
auto compute(const hypercube<D, M, R>& h, std::bitset<D> bs, std::integral_constant<std::size_t, 0> = {}) {
    return h.map(bs);
}

template<std::size_t D, typename M, typename R>
auto compute(const hypercube<D, M, R>& h) {
    return compute(h, std::bitset<D>(), std::integral_constant<std::size_t, D>());
}

void throwing_main() {
    auto arr = std::array<float, 4>{1, 2, 3, 4};
    auto is = std::array<float, 2>{0.5, 0.1};
    auto h = hypercube_<2>( 
        [&](std::bitset<2> b) {
            return arr[b.to_ulong()];
        },
        [&](float a, float b, std::size_t i) {
            std::cout << i << ": " << a << " " << b << std::endl;
            return std::lerp(a, b, is[i]);
        });
    std::cout << compute(h) << std::endl;
}

int main() {
    try {
        throwing_main();
    } catch(const std::exception& e) {
        std::cerr << "std::exception: " << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Unhandled exception." << std::endl;
        return -1;
    }
    return 0;
}

