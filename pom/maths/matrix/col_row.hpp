#pragma once

#include <concepts>

namespace pom {
namespace maths {

// MSVC requires the cast operators to be explicit
// or fails to resolve overload ambiguity.

template<std::integral Ty>
struct col {
	constexpr col() noexcept = default;
	
	explicit constexpr col(Ty val) noexcept
		: value{val}
	{}

	col& operator=(Ty val) noexcept {
		value = val;
		return *this;
	}

	operator Ty&() noexcept {
		return value;
	}

	operator Ty() const noexcept {
		return value;
	}

	Ty value;
};

template<std::integral Ty>
struct row {
	constexpr row() noexcept = default;
	
	explicit constexpr row(Ty val) noexcept
		: value{val}
	{}

	row& operator=(Ty val) noexcept {
		value = val;
		return *this;
	}

	operator Ty&() noexcept {
		return value;
	}

	operator Ty() const noexcept {
		return value;
	}

	Ty value;
};

template<typename Ty>
col(Ty) -> col<Ty>;

template<typename Ty>
row(Ty) -> row<Ty>;

// Increment / decrement.

template<typename Ty> constexpr
col<Ty>& operator++(col<Ty>& c) noexcept {
	++c.value;
	return c;
}

template<typename Ty> constexpr
row<Ty>& operator++(row<Ty>& r) noexcept {
	++r.value;
	return r;
}

template<typename Ty> constexpr
col<Ty>& operator--(col<Ty>& c) noexcept {
	--c.value;
	return c;
}

template<typename Ty> constexpr
row<Ty>& operator--(row<Ty>& r) noexcept {
	--r.value;
	return r;
}

template<typename Ty> constexpr
col<Ty>& operator++(col<Ty>& c, int) noexcept {
	return col<Ty>{c.value++};
}

template<typename Ty> constexpr
row<Ty>& operator++(row<Ty>& r, int) noexcept {
	return row<Ty>{r.value++};
}

template<typename Ty> constexpr
col<Ty>& operator--(col<Ty>& c, int) noexcept {
	return col<Ty>{c.value--};
}

template<typename Ty> constexpr
row<Ty>& operator--(row<Ty>& r, int) noexcept {
	return row<Ty>{r.value--};
}

// Arithmetic operators.

//template<typename Ty> constexpr
//col<Ty> operator-(col<Ty> l, col<Ty> r) noexcept {
//	return col<Ty>{l.value - r.value};
//}
//
//template<typename Ty> constexpr
//row<Ty> operator-(row<Ty> l, row<Ty> r) noexcept {
//	return row<Ty>{l.value - r.value};
//}

}}
