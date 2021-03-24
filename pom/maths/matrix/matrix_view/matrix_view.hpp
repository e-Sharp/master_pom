#pragma once

#include "pom/maths/matrix/col_row_indexes.hpp"

#include <iostream>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/transform.hpp>

namespace pom {
namespace maths {

// TODO: Handling of ordering (only row major for now).
template<typename Range>
class matrix_view {
public:
	using col_index = maths::col_i<std::size_t>;
	using row_index = maths::row_i<std::size_t>;

	constexpr matrix_view(Range&& r, col_index ci, row_index ri)
        : col_count_{static_cast<std::size_t>(ci)}
		, row_count_{static_cast<std::size_t>(ri)}
		, range_{std::move(r)}
	{}

	// Size.

	constexpr std::size_t col_count() const noexcept {
		return col_count_;
	}

	constexpr std::size_t row_count() const noexcept {
		return row_count_;
	}

	// Element access.

	constexpr const Range& range() const noexcept {
		return range_;
	}

private:
	std::size_t col_count_ = 0;
	std::size_t row_count_ = 0;
	Range range_;
};

// Deduction guides.

template<typename R>
matrix_view(R&&, maths::col_i<std::size_t>, maths::row_i<std::size_t>) -> matrix_view<R>;

// TODO: Ordering.

// Size.

template<typename R> constexpr
std::size_t col_count(const matrix_view<R>& mv) noexcept {
	return mv.col_count();
}

template<typename R> constexpr
std::size_t row_count(const matrix_view<R>& mv) noexcept {
	return mv.row_count();
}

// Element access.



// Vector access.

template<typename R> constexpr
auto row(const matrix_view<R>& m, std::size_t i) {
	auto cc = col_count(m);
	auto r = row_major(m)
	| ranges::views::drop_exactly(i * cc)
	| ranges::views::take_exactly(cc);
	return vector_view(std::move(r), cc);
}

// Element ranges.

template<typename R> constexpr
R row_major(const matrix_view<R>& mv) noexcept {
	return mv.range();
}

// Vector ranges.

template<typename R> constexpr
auto rows(const matrix_view<R>& mv) noexcept {
	auto cc = col_count(mv);
	return ranges::views::transform(
		row_major(mv) | ranges::views::chunk(cc),
		[cc](auto&& row) { return vector_view(std::move(row), cc); }
	);
}

}}
