#pragma once

#include <cstdlib>

namespace pom {
namespace maths {

template<typename Base>
struct vector : Base {
	using Base::Base;
};

//// Size.
//
//template<typename B> constexpr
//auto size(const vector<B>& v) {
//	return size(static_cast<const B&>(v));
//}
//
//// Iterators.
//
//template<typename B> constexpr
//auto begin(const vector<B>& v) {
//	return begin(static_cast<const B&>(v));
//}
//
//template<typename B> constexpr
//auto end(const vector<B>& v) {
//	return end(static_cast<const B&>(v));
//}
//
//template<typename B> constexpr
//auto begin(vector<B>& v) {
//	return begin(static_cast<B&>(v));
//}
//
//template<typename B> constexpr
//auto end(vector<B>& v) {
//	return end(static_cast<B&>(v));
//}
//
//// Element access.
//
//template<typename B> constexpr
//const auto& at(const vector<B>& v, std::size_t i) {
//	return at(static_cast<const B&>(v), i);
//}
//
//template<typename B> constexpr
//auto& at(vector<B>& v, std::size_t i) {
//	return at(static_cast<B&>(v), i);
//}

}}
