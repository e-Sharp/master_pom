#pragma once

#include "matrix_col_row.hpp"
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

	explicit constexpr dynamic_matrix(col_row cr)
		: size_{cr.col, cr.row}
		, elements(element_count(*this))
	{}

	explicit constexpr dynamic_matrix(row_col rc)
		: dynamic_matrix({rc.col, rc.row})
	{}

	explicit constexpr dynamic_matrix(std::size_t square)
		: dynamic_matrix({col{square}, row{square}})
	{}

	constexpr const Ty* data() const noexcept {
		return elements.data();
	}

	constexpr Ty* data() noexcept {
		return elements.data();
	}

	constexpr col_row size() const noexcept {
		return size_;
	}

private:
	col_row size_ = {col{0}, row{0}};
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
col col_count(const dynamic_matrix<Ty>& m) {
	return m.size().col;
}

template<typename Ty> constexpr
row row_count(const dynamic_matrix<Ty>& m) {
	return m.size().row;
}

template<typename Ty> constexpr
std::size_t element_count(const dynamic_matrix<Ty>& m) {
	auto cc = static_cast<std::size_t>(col_count(m));
	auto rc = static_cast<std::size_t>(row_count(m));
	return cc * rc;
}

// Element access.

template<typename Ty> constexpr
const Ty& at(const dynamic_matrix<Ty>& m, std::tuple<col, row> cr) {
	auto i = get<row>(cr) * col_count(m) + get<col>(cr);
	return *(m.data() + i);
}

template<typename Ty> constexpr
Ty& at(dynamic_matrix<Ty>& m, std::tuple<col, row> cr) {
	auto i = get<row>(cr) * get<col>(m.size()) + get<col>(cr);
	return *(m.data() + i);
}

template<typename Ty> constexpr
const Ty& at(const dynamic_matrix<Ty>& m, std::tuple<row, col> rc) {
	return at(m, {get<col>(rc), get<row>(rc)});
}

template<typename Ty> constexpr
Ty& at(dynamic_matrix<Ty>& m, std::tuple<row, col> rc) {
	return at(m, {get<col>(rc), get<row>(rc)});
}

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
	return ranges::make_subrange(m.data(), m.data() + element_count(m));
}

template<typename Ty> constexpr
auto row_major(dynamic_matrix<Ty>& m) noexcept {
	return ranges::make_subrange(m.data(), m.data() + element_count(m));
}

// Vector access (through 'vector_view's).

template<typename Ty> constexpr
auto at(const dynamic_matrix<Ty>& m, col c) {
	auto cr = row_major(m)
		| ranges::views::drop_exactly(c)
		| ranges::views::stride(col_count(m))
		| ranges::views::take_exactly(row_count(m));
	return vector_view(std::move(cr), row_count(m));
}

template<typename Ty> constexpr
auto at(dynamic_matrix<Ty>& m, col c) {
	auto cr = row_major(m)
		| ranges::views::drop_exactly(c)
		| ranges::views::stride(col_count(m))
		| ranges::views::take_exactly(row_count(m));
	return vector_view(std::move(cr), row_count(m));
}

template<typename Ty> constexpr
auto at(const dynamic_matrix<Ty>& m, row r) {
	auto rv = row_major(m)
		| ranges::views::drop_exactly(r * col_count(m))
		| ranges::views::take_exactly(std::size_t{col_count(m)}); 
	return vector_view(std::move(rv), col_count(m));
}

template<typename Ty> constexpr
auto at(dynamic_matrix<Ty>& m, row r) {
	auto rv = row_major(m)
		| ranges::views::drop_exactly(r * col_count(m))
		| ranges::views::take_exactly(static_cast<std::size_t>(col_count(m))); 
	return vector_view(std::move(rv), col_count(m));
}

// Vector ranges (through 'vector_view's).
// There might be more adequate combinations of adaptors.

template<typename Ty> constexpr
auto cols(const dynamic_matrix<Ty>& m) {
	auto cc = m.col_count();
	return ranges::views::transform(
		ranges::views::ints(decltype(cc){0}, cc),
		[&m](col c) { return at(m, c); });
}

template<typename Ty> constexpr
auto cols(dynamic_matrix<Ty>& m) {
	auto cc = m.col_count();
	return ranges::views::transform(
		ranges::views::ints(decltype(cc){0}, cc),
		[&m](col c) { return at(m, c); });
}

template<typename Ty>
auto rows(const dynamic_matrix<Ty>& m) {
	auto rc = m.row_count();
	return ranges::views::transform(
		ranges::views::ints(decltype(rc){0}, rc),
		[&m](row r) { return at(m, r); });
}

template<typename Ty>
auto rows(dynamic_matrix<Ty>& m) {
	auto rc = m.row_count();
	return ranges::views::transform(
		ranges::views::ints(decltype(rc){0}, rc),
		[&m](row r) { return at(m, r); });
}

}}
