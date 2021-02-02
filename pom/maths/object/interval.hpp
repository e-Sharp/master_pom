#pragma once

#include "pom/maths/exception/invariant_violation.hpp"

namespace pom {

template<typename Traits>
struct interval {
	using element = typename Traits::element;
	using traits = Traits;

	interval() noexcept = default;

	interval(const element& l, const element& u)
		: lower_{l}
		, upper_{u}
	{
		throw_if_invalid();
	}

	const element& lower() const noexcept {
		return lower_;
	}

	const element& upper() const noexcept {
		return upper_;
	}

private:
	void throw_if_invalid() {
		if(lower_ > upper_) throw maths::invariant_violation{
			"Not a valid interval."};
	}

	element lower_ = {};
	element upper_ = {};
};

} // namespace pom
