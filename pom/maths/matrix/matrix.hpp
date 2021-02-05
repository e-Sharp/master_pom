#pragma once

#include "pom/maths/matrix/traits/dynamic.hpp"
#include "pom/maths/matrix/traits/static.hpp"
#include "pom/maths/preset/default/all.hpp"

namespace pom {

template<matrix_traits Traits>
class matrix {
public:
	using storage = typename Traits::storage;
	using traits = Traits;

	matrix() noexcept = default;

	template<dynamic_matrix_traits = Traits>
	matrix(dimension<0, std::size_t> size_0, dimension<1, std::size_t> size_1) {
		traits::resize(storage_, size_0, size_1);
	}

	storage storage_ = {};
};

template<typename Ty>
using dynamic_matrix = matrix<default_dynamic_matrix_traits<Ty>>;

template<typename Ty, col C, row R>
using static_matrix = matrix<default_static_matrix_traits<Ty, C, R>>;

template<matrix_traits Tr>
const auto& at(
	const matrix<Tr>& m,
	dimension<0, std::size_t> i, dimension<1, std::size_t> j)
{
	return Tr::at(m.storage_, i, j);
}

template<matrix_traits Tr>
auto& at(
	matrix<Tr>& m, dimension<0, std::size_t> i, dimension<1, std::size_t> j)
{
	return Tr::at(m.storage_, i, j);
}

template<dynamic_matrix_traits Tr>
auto size(const matrix<Tr>& m, dimension<0>) {
	return Tr::size(m.storage_, dimension<0>{});
}

template<dynamic_matrix_traits Tr>
auto size(const matrix<Tr>& m, dimension<1>) {
	return Tr::size(m.storage_, dimension<1>{});
}

template<dynamic_matrix_traits Tr>
auto size(const matrix<Tr>& m) {
	return maths::default_preset::static_vector<std::size_t, 2>{{
		size(m, dimension<0>{}), size(m, dimension<1>{})}};
}

} // namespace pom
