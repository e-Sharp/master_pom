#pragma once

#include "bound_storage.hpp"

#include "decl/type/what.hpp"
#include "decl/type_list/at.hpp"
#include "decl/type_list/size.hpp"

#include <tuple>

namespace std {

template<std::size_t I, typename S>
struct tuple_element<I, decl::detail::bound_storage<S>> {
	using type = decltype(decl::detail::what(at(S::storage_traits::recipes(), index(S::storage_traits::targets(), at<I>(S::bound_targets())))));
};

template<typename S>
struct tuple_size<decl::detail::bound_storage<S>>
	: std::integral_constant<std::size_t, size(S::bound_targets())> {};

}
