#pragma once

#include "decl/tag/undefined.hpp"
#include "decl/type/type.hpp"
#include "decl/type/what.hpp"
#include "decl/type_list/type_list.hpp"

namespace decl {
namespace detail {

template<typename Target, typename... Args> consteval
auto recipe_return_type(type<Target>, type_list<Args...>) {
	using r = decltype(recipe(undefined, Target(), what(type<Args>())...));
	return type<r>();
}

template<typename... Targets, typename... Args> consteval
auto recipes_return_types(type_list<Targets...>, type_list<Args...> as) {
	return type_list<decltype(what(recipe_return_type(type<Targets>(), as)))...>();
}

}}
