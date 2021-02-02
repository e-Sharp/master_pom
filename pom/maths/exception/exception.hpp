#pragma once

namespace pom {
namespace maths {

class exception {
public:
	virtual const char* what() const noexcept = 0;
};

} // namespace maths
} // namespace pom
