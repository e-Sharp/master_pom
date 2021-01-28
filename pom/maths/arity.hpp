#pragma once

#include <type_traits>

namespace pom {
namespace detail {

template<typename Ty>
struct arity : arity<decltype(&Ty::operator())> {};

template<typename Ty>
struct arity<Ty&> : arity<decltype(&Ty::operator())> {};

template <typename R, typename... Ps>
struct arity<R(*)(Ps...)> : std::integral_constant<unsigned, sizeof...(Ps)> {};

template<typename R, typename C, typename... Ps>
struct arity<R(C::*)(Ps...)> : std::integral_constant<std::size_t, sizeof...(Ps)> {};

template<typename R, typename C, typename... Ps>
struct arity<R(C::*)(Ps...) const> : std::integral_constant<std::size_t, sizeof...(Ps)> {};

template<typename R, typename C, typename... Ps>
struct arity<R(C::* const)(Ps...)> : std::integral_constant<std::size_t, sizeof...(Ps)> {};

template<typename R, typename C, typename... Ps>
struct arity<R(C::* const)(Ps...) const> : std::integral_constant<std::size_t, sizeof...(Ps)> {};

template<typename R, typename C, typename... Ps>
struct arity<R(C::* const&)(Ps...)> : std::integral_constant<std::size_t, sizeof...(Ps)> {};

template<typename R, typename C, typename... Ps>
struct arity<R(C::* const&)(Ps...) const> : std::integral_constant<std::size_t, sizeof...(Ps)> {};

} // namespace detail
} // namespace pom

namespace pom {

template<typename Ty>
constexpr auto arity = detail::arity<Ty>::value;

} // namespace pom
