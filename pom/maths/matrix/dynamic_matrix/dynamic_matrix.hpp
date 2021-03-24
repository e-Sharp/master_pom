#pragma once

#include "pom/maths/matrix/col_row_indexes.hpp"
#include "pom/maths/vector/all.hpp"

#include <range/v3/view/chunk.hpp>
#include <range/v3/view/drop_exactly.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/stride.hpp>
#include <range/v3/view/take_exactly.hpp>
#include <range/v3/view/transform.hpp>
#include <vector>

namespace pom::maths {

template<typename Ty>
class dynamic_matrix {
public:
	// Member types.

	using size_type = std::size_t;

	// Constructors.

	constexpr dynamic_matrix() noexcept = default;

	constexpr
	dynamic_matrix(maths::col_i<std::size_t> c, maths::row_i<std::size_t> r)
		: dynamic_matrix(
			static_cast<std::size_t>(c), static_cast<std::size_t>(r))
	{}

	explicit constexpr dynamic_matrix(std::size_t square)
		: dynamic_matrix(square, square)
	{}

	// Size.

	constexpr std::size_t col_count() const noexcept {
		return col_count_;
	}

	constexpr std::size_t row_count() const noexcept {
		return row_count_;
	}

	// Element access.

	constexpr const Ty* data() const noexcept {
		return elements.data();
	}

	constexpr Ty* data() noexcept {
		return elements.data();
	}

private:
	constexpr dynamic_matrix(std::size_t c, std::size_t r)
    	: col_count_{c}
		, row_count_{r}
		, elements(element_count(*this))
	{} 

	std::size_t col_count_ = 0;
	std::size_t row_count_ = 0;
	std::vector<Ty> elements = {};
};

// Ordering.

template<typename Ty> constexpr
bool is_col_major(const dynamic_matrix<Ty>& m) {
	return false;
}

template<typename Ty> constexpr
bool is_row_major(const dynamic_matrix<Ty>& m) {
	return true;
}

// Size.

template<typename Ty> constexpr
std::size_t col_count(const dynamic_matrix<Ty>& m) noexcept {
	return m.col_count();
}

template<typename Ty> constexpr
std::size_t row_count(const dynamic_matrix<Ty>& m) noexcept {
	return m.row_count();
}

template<typename Ty> constexpr
std::size_t element_count(const dynamic_matrix<Ty>& m) noexcept {
	return col_count(m) * row_count(m);
}

template<typename Ty> constexpr
maths::static_vector<std::size_t, 2> size_cr(const dynamic_matrix<Ty>& m) noexcept {
	return {col_count(m), row_count(m)};
}

// Element access.

template<typename Ty> constexpr
const Ty& at_cr(const dynamic_matrix<Ty>& m, std::size_t c, std::size_t r) {
	auto i = r * col_count(m) + c;
	return *(m.data() + i);
}

template<typename Ty> constexpr
Ty& at_cr(dynamic_matrix<Ty>& m, std::size_t c, std::size_t r) {
	auto i = r * col_count(m) + c;
	return *(m.data() + i);
}

// Element ranges.

template<typename Ty> constexpr
auto col_major(const dynamic_matrix<Ty>&) {
	throw std::logic_error{"Not implemented."};
}

template<typename Ty> constexpr
auto col_major(dynamic_matrix<Ty>&) {
	throw std::logic_error{"Not implemented."};
}

template<typename Ty> constexpr
auto row_major(const dynamic_matrix<Ty>& m) noexcept {
	auto d = m.data();
	return ranges::make_subrange(d, d + element_count(m));
}

template<typename Ty> constexpr
auto row_major(dynamic_matrix<Ty>& m) noexcept {
	auto d = m.data();
	return ranges::make_subrange(d, d + element_count(m));
}

// Vector access (through 'vector_view's).

template<typename Ty> constexpr
auto col(const dynamic_matrix<Ty>& m, std::size_t i) {
	auto c = row_major(m)
	| ranges::views::drop_exactly(i)
	| ranges::views::stride(col_count(m))
	| ranges::views::take_exactly(row_count(m));
	return vector_view(std::move(c), row_count(m));
}

template<typename Ty> constexpr
auto col(dynamic_matrix<Ty>& m, std::size_t i) {
	auto c = row_major(m)
	| ranges::views::drop_exactly(i)
	| ranges::views::stride(col_count(m))
	| ranges::views::take_exactly(row_count(m));
	return vector_view(std::move(c), row_count(m));
}

template<typename Ty> constexpr
auto row(const dynamic_matrix<Ty>& m, std::size_t i) {
	auto r = row_major(m)
	| ranges::views::drop_exactly(i * col_count(m))
	| ranges::views::take_exactly(col_count(m)); 
	return vector_view(std::move(r), col_count(m));
}

template<typename Ty> constexpr
auto row(dynamic_matrix<Ty>& m, std::size_t i) {
	auto r = row_major(m)
	| ranges::views::drop_exactly(i * col_count(m))
	| ranges::views::take_exactly(col_count(m)); 
	return vector_view(std::move(r), col_count(m));
}

// Vector ranges (through 'vector_view's).

template<typename Ty> constexpr
auto cols(const dynamic_matrix<Ty>& m) {
	auto cc = col_count(m);
	return ranges::views::transform(
		ranges::views::ints(decltype(cc){0}, cc),
		[&m](auto i) { return col(m, i); });
}

template<typename Ty> constexpr
auto cols(dynamic_matrix<Ty>& m) {
	auto cc = col_count(m);
	return ranges::views::transform(
		ranges::views::ints(decltype(cc){0}, cc),
		[&m](auto i) { return col(m, i); });
}

template<typename Ty>
auto rows(const dynamic_matrix<Ty>& m) {
	auto cc = col_count(m);
	return ranges::views::transform(
		row_major(m) | ranges::views::chunk(cc),
		[cc](auto&& row) { return vector_view(std::move(row), cc); });
}

template<typename Ty>
auto rows(dynamic_matrix<Ty>& m) {
	auto cc = col_count(m);
	return ranges::views::transform(
		row_major(m) | ranges::views::chunk(cc),
		[cc](auto&& row) { return vector_view(std::move(row), cc); });
}

}
