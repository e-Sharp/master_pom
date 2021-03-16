#pragma once

#include "type.hpp"

#include <tuple>

namespace pom {
namespace meta {

template<typename... Tuple, typename Ty> constexpr
decltype(auto) get(const std::tuple<Tuple...>& tu, type<Ty>) {
	return std::get<Ty>(tu);
}

template<typename... Tuple, typename Ty> constexpr
decltype(auto) get(std::tuple<Tuple...>& tu, type<Ty>) {
	return std::get<Ty>(tu);
}

}}
