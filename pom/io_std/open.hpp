#pragma once

#include <fstream>
#include <stdexcept>
#include <string>

namespace pom {
namespace io_std {

std::fstream open_file(const char* filename, std::ios::openmode mode) {
	auto f = std::fstream{filename, mode};
	if(!f.is_open()) throw std::runtime_error{
		std::string{"Failed to open file "} + filename + "."};
	return f;
}

std::fstream open_file(const std::string& s, std::ios::openmode mode) {
	return open_file(s.c_str(), mode);
}

}}
