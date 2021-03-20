#pragma once

#include "decl/type_list/type_list.hpp"

namespace decl {
namespace detail {

template<typename... Targets, typename... Args> consteval
auto bound_storage_traits_of(type_list<Targets...>, Args&&... as) {
	struct traits {
		struct storage_traits {
			using targets = decltype(target_sequence(type_list<Targets...>()));
			using recipes = decltype(recipes_return_types(targets(), std::forward<Args>(as)...));
		};
		using bound_targets = type_list<Targets...>;
	};
	return traits();
}

}}
