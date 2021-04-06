#pragma once

#include "multiplication.hpp"

#include "pom/terrain/import/all.hpp"

#include <tuple>

namespace pom::terrain {

template<typename Lhs, typename Rhs>
struct product {
	Lhs lhs;
	Rhs rhs;
};

template<typename Lhs, typename Rhs>
product(Lhs&&, Rhs&&) -> product<Lhs, Rhs>;

template<typename Lhs, typename... Rhss> constexpr
auto product_of(Lhs&& l, Rhss&&... rs) {
	return product(
		std::forward<Lhs>(l),
		product_of(std::forward<Rhss>(rs)...));
}

template<typename Lhs, typename Rhs> constexpr
auto product_of(Lhs&& l, Rhs&& r) {
	return product(std::forward<Lhs>(l), std::forward<Rhs>(r));
}

template<typename... Functions> constexpr
auto operator|(std::tuple<Functions...>&& t, multiplication) {
	return std::apply(
		[](auto&&... as) { 
			return product_of(std::forward<decltype(as)>(as)...); },
		std::move(t));
}

template<typename DeclContext, typename... P> constexpr
float recipe(DeclContext, height_, const product<P...>& p, vec2f coords) {
	auto [ha] = decl::make<height_>(p.lhs, coords);
	auto [hb] = decl::make<height_>(p.rhs, coords);
	return ha * hb;
}

}
