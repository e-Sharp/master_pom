#pragma once

#include <type_traits>

namespace pom {
namespace meta {
namespace detail {

template<typename Ty>
struct arity
    : arity<decltype(&Ty::operator())> {};

// Specializations for function objects - and lambdas.

template<typename R, typename C, typename... Ps>
struct arity<R(C::*)(Ps...) const>
    : std::integral_constant<std::size_t, sizeof...(Ps)>
{};

}}}

namespace pom {
namespace meta {

template<typename Ty>
constexpr std::size_t arity = detail::arity<Ty>::value;

}}
