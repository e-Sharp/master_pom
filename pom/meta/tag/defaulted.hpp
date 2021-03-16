#pragma once

namespace pom {
namespace meta {

struct defaulted_tag {};

constexpr auto defaulted = defaulted_tag();

}}
