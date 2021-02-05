#pragma once

#include "pom/maths/object/interval.hpp"
#include "pom/maths/exceptions.hpp"

namespace pom {
namespace maths {
namespace default_preset {

template<typename Ty>
struct interval_traits {
	using element = Ty;
};

template<typename Tr>
class interval_ {
public:
	using element_type = typename Tr::element;

	constexpr interval_() noexcept = default;

	constexpr
	interval_(const element_type& lower, const element_type& upper)
		: lower_{lower}
		, upper_{upper}
	{
		throw_if_invalid();
	}

	constexpr
	const element_type& lower() const noexcept {
		return lower_;
	}

	constexpr
	const element_type& upper() const noexcept {
		return upper_;
	}

private:
	constexpr void throw_if_invalid() const {
		if(lower() > upper()) throw invariant_violation{
			"Interval: lower bound is greater than upper bound."};
	}

	element_type lower_ = {};
	element_type upper_ = {};
};

template<typename Tr> constexpr
decltype(auto) lower(const interval_<Tr>& i) noexcept {
	return i.lower();
}

template<typename Tr> constexpr
decltype(auto) upper(const interval_<Tr>& i) noexcept {
	return i.upper();
}

template<typename Ty>
using interval = maths::interval<interval_<interval_traits<Ty>>>;

}}}
