#pragma once

#include "pom/maths/exceptions.hpp"

namespace pom {
namespace maths_impl {

// Implementation of 'pom::maths::interval'.
// Invariant: 'lower() <= upper()'.
template<typename Ty>
class interval_ {
public:
	constexpr interval_() noexcept = default;

	constexpr interval_(const Ty& lower, const Ty& upper)
		: lower_{lower}
		, upper_{upper}
	{
		throw_if_invalid();
	}

	constexpr const Ty& lower() const noexcept {
		return lower_;
	}

	constexpr const Ty& upper() const noexcept {
		return upper_;
	}

private:
	constexpr void throw_if_invalid() const {
		if(lower() > upper()) throw maths::invariant_violation{
			"Interval: lower bound is greater than upper bound."};
	}

	Ty lower_ = {};
	Ty upper_ = {};
};

template<typename Ty> constexpr
decltype(auto) lower(const interval_<Ty>& i) noexcept {
	return i.lower();
}

template<typename Ty> constexpr
decltype(auto) upper(const interval_<Ty>& i) noexcept {
	return i.upper();
}

// Deduction guides.

template<typename Ty>
interval_(Ty, Ty) -> interval_<Ty>;

}}
