#pragma once

#include "pom/maths/exception/exception.hpp"

#include <string>

namespace pom {
namespace maths {

class precondition_violation : public exception {
public:
	precondition_violation(const std::string& what)
		: what_{what}
	{}

	const char* what() const noexcept {
		return what_.c_str();
	}

private:
	std::string what_;
};

}}
