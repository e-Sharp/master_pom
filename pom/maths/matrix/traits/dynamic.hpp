#pragma once

#include "pom/maths/annotation/dimension.hpp"
#include "pom/maths/matrix/traits/matrix.hpp"

#include <stdexcept>
#include <vector>

namespace pom {

template<typename Ty>
concept dynamic_matrix_traits =
	matrix_traits<Ty> &&
	Ty::is_dynamic;

template<typename Ty>
struct default_dynamic_matrix_traits {
	static constexpr auto is_dynamic = true;

	using element = Ty;

	struct storage {
		dimension<0, std::size_t> width = {0};
		dimension<1, std::size_t> height = {0};
		std::vector<element> elements = {};
	};

	static const auto& at(
		const storage& s, dimension<0, std::size_t> i, dimension<1, std::size_t> j)
	{
		if(i >= s.width || j >= s.height) {
			throw std::out_of_range{"Matrix."};
		}
		return s.elements[index_at(s, i, j)];
	}

	static auto& at(
		storage& s, dimension<0, std::size_t> i, dimension<1, std::size_t> j)
	{
		if(i >= s.width || j >= s.height) {
			throw std::out_of_range{"Matrix."};
		}
		return s.elements[index_at(s, i, j)];
	}

	static auto size(const storage& s, dimension<0>) {
		return s.width;
	}

	static auto size(const storage& s, dimension<1>) {
		return s.height;
	}

	static auto resize(
		storage& s, dimension<0, std::size_t> d0, dimension<1, std::size_t> d1)
	{
		s.elements.clear();
		s.elements.resize(d0 * d1);
		s.width = d0;
		s.height = d1;
	}

private:
	static auto index_at(
		const storage& s, dimension<0, std::size_t> i, dimension<1, std::size_t> j)
	{
		// Column major for now.
		return j * s.width + i;
	}
};

} // namespace pom
