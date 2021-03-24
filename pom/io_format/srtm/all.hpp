#pragma once

#include "pom/io/endianness/reverse.hpp"
#include "pom/io_std/all.hpp"
#include "pom/maths/all.hpp"

#include <istream>

namespace pom {
namespace io_format {
namespace srtm {

auto read_srtm3(std::istream& is) {
	auto m = maths::matrix<float>(1201);
	for(auto& e : row_major(m)) {
		e = static_cast<float>(io::reversed(io_std::get<short>(is)));
	}
	return m;
}

}}}
