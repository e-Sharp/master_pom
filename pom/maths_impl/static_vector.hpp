#pragma once

#include "pom/maths/exceptions.hpp"

#include <algorithm>
#include <initializer_list>

namespace pom {
namespace maths_impl {

template<typename Ty, std::size_t Size>
struct static_vector_traits {
	using element = Ty;

	static constexpr auto size = Size;
};

template<typename Traits>
class static_vector {
public:
	using element_type = typename Traits::element;

	constexpr static_vector() noexcept = default;

	constexpr static_vector(std::size_t size) {
		if(size != Traits::size) throw maths::invariant_violation{
			"Static vectors have constant size."};
	}

	constexpr static_vector(std::initializer_list<element_type> l) {
		if(l.size() != Traits::size) throw maths::precondition_violation{""};
		std::move(std::begin(l), std::end(l), std::begin(elements));
	}

	std::array<element_type, Traits::size> elements = {};
};

// Capacity.

template<typename Tr> constexpr
std::size_t size(const static_vector<Tr>& v) noexcept {
	return v.elements.size();
}

// Iterators.

template<typename Tr> constexpr
auto begin(const static_vector<Tr>& v) {
	return std::begin(v.elements);
}

template<typename Tr> constexpr
auto end(const static_vector<Tr>& v) {
	return std::end(v.elements);
}

template<typename Tr> constexpr
auto begin(static_vector<Tr>& v) {
	return std::begin(v.elements);
}

template<typename Tr> constexpr
auto end(static_vector<Tr>& v) {
	return std::end(v.elements);
}

// Element access.

template<typename Tr> constexpr
const auto& at(const static_vector<Tr>& v, std::size_t i) {
	return v.elements[i];
}

template<typename Tr> constexpr
auto& at(static_vector<Tr>& v, std::size_t i) {
	return v.elements[i];
}

// User-friendly type with default traits.
template<typename Ty, std::size_t Size>
struct static_vector_ : static_vector<static_vector_traits<Ty, Size>> {
	using static_vector<static_vector_traits<Ty, Size>>::static_vector;
};

}}
