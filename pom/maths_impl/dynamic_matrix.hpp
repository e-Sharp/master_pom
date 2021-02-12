#pragma once

#include "pom/maths_impl/static_vector.hpp"

#include <vector>

namespace pom {
namespace maths_impl {

template<typename Ty>
struct dynamic_matrix_traits {
	using index = static_vector_<std::size_t, 2>;
	using element = Ty;
};

template<typename Traits>
struct dynamic_matrix {
	using index_type = typename Traits::index;
	using element_type = typename Traits::element;

	constexpr dynamic_matrix() noexcept = default;

	constexpr
	dynamic_matrix(const index_type& size)
		: size{size}
		, elements(at(size, 0) * at(size, 1))
	{}

	index_type size = {};
	std::vector<element_type> elements = {};
};

template<typename Tr>
decltype(auto) at(
	const dynamic_matrix<Tr>& m, typename Tr::index ij)
{
	return m.elements[index_at(m, ij)];
}

template<typename Tr>
decltype(auto) at(dynamic_matrix<Tr>& m, typename Tr::index ij) {
	return m.elements[index_at(m, ij)];
}

template<typename Tr>
std::size_t index_at(
	const dynamic_matrix<Tr>& m, typename Tr::index ij)
{
	return at(size(m), 0) * at(ij, 1) + at(ij, 0);
}

template<typename Tr>
typename Tr::index size(const dynamic_matrix<Tr>& m) noexcept {
	return m.size;
}

// Pre-defined type using default traits.

template<typename Ty>
struct dynamic_matrix_ : dynamic_matrix<dynamic_matrix_traits<Ty>> {
	using dynamic_matrix<dynamic_matrix_traits<Ty>>::dynamic_matrix;
};

}}
