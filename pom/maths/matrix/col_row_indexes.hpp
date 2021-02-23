#pragma once

#include <concepts>

namespace pom {
namespace maths {

template<std::integral Ty>
struct col_i {
	operator const Ty&() const noexcept {
		return value;
	}

	operator Ty&() noexcept {
		return value;
	}
	
	Ty value;
};

template<std::integral Ty>
struct row_i {
	operator const Ty&() const noexcept {
		return value;
	}

	operator Ty&() noexcept {
		return value;
	}

	Ty value;
};

template<typename Ty>
col_i(Ty) -> col_i<Ty>;

template<typename Ty>
row_i(Ty) -> row_i<Ty>;

}}
