#pragma once

#include "pom/io/exception/all.hpp"

#include <concepts>

namespace pom {
namespace io {
namespace wavefront {

template<typename Stream>
concept input_stream = requires(Stream s) {
	{ empty(s) } -> std::convertible_to<bool>;
	{ get(s) };
};

}}}
