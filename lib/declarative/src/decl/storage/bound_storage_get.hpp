#pragma once

#include "bound_storage.hpp"
#include "bound_storage_bindings.hpp"

namespace decl {
namespace detail {

template<std::size_t I, typename S> constexpr
auto& get(bound_storage<S>& s) {
	return get<std::tuple_element_t<I, bound_storage<S>>>(s.storage.data);
}

template<std::size_t I, typename S> constexpr
auto&& get(bound_storage<S>&& s) {
	return get<std::tuple_element_t<I, bound_storage<S>>>(s.storage.data);
}

}}
