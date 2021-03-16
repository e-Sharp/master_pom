//#pragma once
//
//#include "list.hpp"
//#include "union.hpp"
//
//#include "pom/meta/type/type/all.hpp"
//
//namespace pom {
//namespace meta {
//
//template<typename Ty, typename... Args> consteval
//type_list<Ty> set_of(type<Ty> t, Args... as) {
//	return union_(t, set_of(as...));
//}
//
//consteval
//type_list<> set_of() { return {}; }
//
//}}
