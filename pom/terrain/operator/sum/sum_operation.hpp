#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename A, typename B>
struct sum_operation {
	A a;
	B b;
};

template<typename A, typename B>
sum_operation(A&&, B&&) -> sum_operation<A, B>;

template<typename DeclContext, typename A, typename B> constexpr
float recipe(
	DeclContext,
	color_, 
	const sum_operation<A, B>& so,
	vec2f coords)
{
	// Couldn't find a good definition for it.
	throw meta::not_implemented();
}

template<typename DeclContext, typename A, typename B> constexpr
float recipe(
	DeclContext,
	gradient, 
	const sum_operation<A, B>& so,
	vec2f coords)
{
	auto [ga] = decl::make<gradient>(so.a, coords);
	auto [gb] = decl::make<gradient>(so.b, coords);
	return ga + gb;
}

template<typename DeclContext, typename A, typename B> constexpr
float recipe(
	DeclContext,
	height_, 
	const sum_operation<A, B>& so,
	vec2f coords)
{
	auto [ha] = decl::make<height_>(so.a, coords);
	auto [hb] = decl::make<height_>(so.b, coords);
	return ha + hb;
}

template<typename DeclContext, typename A, typename B> constexpr
float recipe(
	DeclContext,
	weight_, 
	const sum_operation<A, B>& so,
	vec2f coords)
{
	auto [wa] = decl::make<weight_>(so.a, coords);
	auto [wb] = decl::make<weight_>(so.b, coords);
	return wa + wb - wa * wb;
}

}
