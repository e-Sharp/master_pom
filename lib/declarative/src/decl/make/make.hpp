#pragma once

#include "make_and_store.hpp"

#include "decl/storage/bound_storage.hpp"
#include "decl/storage/bound_storage_traits_of.hpp"
#include "decl/type_list/type_list.hpp"
#include "decl/target/recipe_return_type.hpp"
#include "decl/target/target_sequence.hpp"

#include <iostream>

namespace decl {

template<typename... Targets, typename... Args> constexpr
auto make(Args&&... as) {
	struct traits {
		struct storage_traits {
			using targets = decltype(detail::target_sequence(type_list<Targets...>()));
			using recipes = decltype(detail::recipes_return_types(targets(), type_list<Args&&...>()));
		};
		using bound_targets = type_list<Targets...>;
	};
	auto s = bound_storage<traits>();
	make_and_store(s.storage, traits::storage_traits::targets(), std::forward<Args>(as)...);
	return s;
}

}
