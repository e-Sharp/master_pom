#pragma once

namespace decl {
namespace detail {

struct undefined_tag {};

constexpr auto undefined = undefined_tag();

}}
