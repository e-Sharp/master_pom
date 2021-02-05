#pragma once

#include <string>

namespace pom {
namespace maths {

class exception {
public:
	virtual const char* what() const noexcept = 0;
};

class invariant_violation : public exception {
public:
	invariant_violation(const std::string& what)
		: what_{what}
	{}

	const char* what() const noexcept {
		return what_.c_str();
	}

private:
	std::string what_;
};

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

} // namespace maths
} // namespace pom
