#pragma once

#include "pom/maths/exception/invariant_violation.hpp"
#include "pom/maths/object/vector.hpp"

#include <array>

namespace pom {
namespace maths {
namespace default_preset {

template<typename Ty, std::size_t Size>
struct static_vector_traits {
	using element = Ty;

	static constexpr auto size = Size;
};

template<typename Tr>
class static_vector_ {
public:
	constexpr
	static_vector_() noexcept = default;

	constexpr
	static_vector_(std::size_t size) {
		if(size != Tr::size) throw invariant_violation{
			"Static vectors have constant size."};
	}

	constexpr
	static_vector_(
		const std::array<typename Tr::element, Tr::size>& elements_) noexcept
		: elements{elements_}
	{}

	std::array<typename Tr::element, Tr::size> elements = {};
};

template<typename Ty, std::size_t Size>
using static_vector = vector<static_vector_<static_vector_traits<Ty, Size>>>;


// Size.

template<typename Tr> constexpr
std::size_t size(const static_vector_<Tr>& v) noexcept {
	return v.elements.size();
}

// Iterators.

template<typename Tr> constexpr
auto begin(const static_vector_<Tr>& v) {
	return std::begin(v.elements);
}

template<typename Tr> constexpr
auto end(const static_vector_<Tr>& v) {
	return std::end(v.elements);
}

template<typename Tr> constexpr
auto begin(static_vector_<Tr>& v) {
	return std::begin(v.elements);
}

template<typename Tr> constexpr
auto end(static_vector_<Tr>& v) {
	return std::end(v.elements);
}

// Element access.

template<typename Tr> constexpr
const auto& at(const static_vector_<Tr>& v, std::size_t i) {
	return v.elements[i];
}

template<typename Tr> constexpr
auto& at(static_vector_<Tr>& v, std::size_t i) {
	return v.elements[i];
}

}}}
