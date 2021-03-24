#pragma once

#include <pom/meta/exception/all.hpp>

namespace pom::maths {

// Invariant: 'lower() <= upper()'.
template<typename Ty>
class interval {
public:
	constexpr interval() noexcept = default;

	constexpr interval(Ty lower, Ty upper)
		: lower_{lower}
		, upper_{upper}
	{
		throw_if_invalid();
	}

	constexpr Ty lower() const noexcept {
		return lower_;
	}

	constexpr Ty upper() const noexcept {
		return upper_;
	}

private:
	constexpr void throw_if_invalid() const {
		if(lower() > upper()) throw meta::invariant_violation();
	}

	Ty lower_ = {};
	Ty upper_ = {};
};

// Deduction guides.

template<typename Ty>
interval(Ty, Ty) -> interval<Ty>;

// Factories.

template<typename Ty> constexpr
interval<Ty> interval_0_1() noexcept {
	return interval(Ty{0}, Ty{1});
}

template<typename Ty> constexpr
interval<Ty> interval_0_n(Ty n) {
	return interval(Ty{0}, n);
}

}
