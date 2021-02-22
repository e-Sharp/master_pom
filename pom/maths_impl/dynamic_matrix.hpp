#pragma once

#include "vector_view.hpp"

#include <range/v3/view/all.hpp>
#include <range/v3/view/drop_exactly.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/stride.hpp>
#include <range/v3/view/take_exactly.hpp>
#include <range/v3/view/transform.hpp>
#include <tuple>
#include <vector>

namespace pom {
namespace maths_impl {

template<typename Ty>
class dynamic_matrix {
public:
	constexpr dynamic_matrix() noexcept = default;

	explicit constexpr dynamic_matrix(std::size_t rows, std::size_t cols)
		: col_count_{cols}
		, row_count_{rows}
		, elements(col_count() * row_count())
	{}

	// Dimensions.

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
	std::size_t col_count_ = 0;
	std::size_t row_count_ = 0;
	std::vector<Ty> elements = {};
};

////////////////////////////////////////////////////////////////////////////////
// Ranges.

// Element ranges.

template<typename Ty> constexpr
auto col_major(const dynamic_matrix<Ty>& m) noexcept {
	throw std::logic_error{"Not implemented."};
}

template<typename Ty> constexpr
auto col_major(dynamic_matrix<Ty>& m) noexcept {
	throw std::logic_error{"Not implemented."};
}

template<typename Ty> constexpr
auto row_major(const dynamic_matrix<Ty>& m) noexcept {
	auto d = m.data();
	return ranges::make_subrange(d, d + m.col_count() * m.row_count());
}

template<typename Ty> constexpr
auto row_major(dynamic_matrix<Ty>& m) noexcept {
	auto d = m.data();
	return ranges::make_subrange(d, d + m.col_count() * m.row_count());
}

// Vector ranges.
// There might be more adequate combinations of adaptors.

template<typename Ty> constexpr
auto col(const dynamic_matrix<Ty>& m, std::size_t i) {
	auto c = row_major(m)
		| ranges::views::drop_exactly(i)
		| ranges::views::stride(m.col_count())
		| ranges::views::take_exactly(m.row_count());
	return vector_view(std::move(c), m.row_count());
}

template<typename Ty> constexpr
auto col(dynamic_matrix<Ty>& m, std::size_t i) {
	auto c = row_major(m)
		| ranges::views::drop_exactly(i)
		| ranges::views::stride(m.col_count())
		| ranges::views::take_exactly(m.row_count());
	return vector_view(std::move(c), m.row_count());
}

template<typename Ty> constexpr
auto cols(const dynamic_matrix<Ty>& m) {
	return ranges::views::transform(
		ranges::views::ints(std::size_t{0}, m.col_count()),
		[&m](std::size_t c) { return col(m, c); }
	);
}

template<typename Ty> constexpr
auto cols(dynamic_matrix<Ty>& m) {
	return ranges::views::transform(
		ranges::views::ints(std::size_t{0}, m.col_count()),
		[&m](std::size_t c) { return col(m, c); }
	);
}

template<typename Ty>
auto row(const dynamic_matrix<Ty>& m, std::size_t i) {
	auto r = row_major(m)
		| ranges::views::drop_exactly(i * m.col_count())
		| ranges::views::take_exactly(m.col_count()); 
	return vector_view(std::move(r), m.col_count());
}

template<typename Ty>
auto row(dynamic_matrix<Ty>& m, std::size_t i) {
	auto r = row_major(m)
		| ranges::views::drop_exactly(i * m.col_count())
		| ranges::views::take_exactly(m.col_count()); 
	return vector_view(std::move(r), m.col_count());
}

template<typename Ty>
auto rows(const dynamic_matrix<Ty>& m) {
	return ranges::views::transform(
		ranges::views::ints(std::size_t{0}, m.row_count()),
		[&m](std::size_t r) { return row(m, r); }
	);
}

template<typename Ty>
auto rows(dynamic_matrix<Ty>& m) {
	return ranges::views::transform(
		ranges::views::ints(std::size_t{0}, m.row_count()),
		[&m](std::size_t r) { return row(m, r); }
	);
}

}}
