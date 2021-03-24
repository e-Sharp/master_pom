#pragma once

#include <pom/meta/exception/all.hpp>

#include <array>
#include <initializer_list>

namespace pom::maths {

template<typename Ty, std::size_t N>
class static_vector {
public:
	constexpr static_vector() noexcept = default;

	explicit constexpr static_vector(std::size_t) {}

	constexpr static_vector(std::initializer_list<Ty> l) {
		if(l.size() != N) throw meta::precondition_violation();
		std::move(std::begin(l), std::end(l), std::begin(elements));
	}

	std::array<Ty, N> elements = {};
};

// Capacity.

template<typename Ty, std::size_t N> constexpr
std::size_t size(const static_vector<Ty, N>& v) noexcept {
	return size(v.elements);
}

// Element access.

template<typename Ty, std::size_t N> constexpr
const Ty& at(const static_vector<Ty, N>& v, std::size_t i) {
	return v.elements[i];
}

template<typename Ty, std::size_t N> constexpr
Ty& at(static_vector<Ty, N>& v, std::size_t i) {
	return v.elements[i];
}

// Iterators.

template<typename Ty, std::size_t N> constexpr
auto begin(const static_vector<Ty, N>& v) {
	return begin(v.elements);
}

template<typename Ty, std::size_t N> constexpr
auto end(const static_vector<Ty, N>& v) {
	return end(v.elements);
}

template<typename Ty, std::size_t N> constexpr
auto begin(static_vector<Ty, N>& v) {
	return begin(v.elements);
}

template<typename Ty, std::size_t N> constexpr
auto end(static_vector<Ty, N>& v) {
	return end(v.elements);
}

}
