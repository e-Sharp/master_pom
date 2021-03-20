#pragma once

#include "decl/context/context_of.hpp"
#include "decl/storage/storage.hpp"
#include "decl/type/type.hpp"

namespace decl {
namespace detail {

template<typename S, typename Target, typename... Args>
auto make_and_store(storage<S>& s, type<Target> t, Args&&... as) {
	get(s, t) = recipe(
		context_of(s, t),
		Target(),
		std::forward<Args>(as)...);
}

template<typename S, typename... Targets, typename... Args>
auto make_and_store(storage<S>& s, type_list<Targets...>, Args&&... as) {
	(
		make_and_store(s, type<Targets>(), std::forward<Args>(as)...)
	, ...);
}

}}
