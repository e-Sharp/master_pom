#pragma once

#include "pom/ctree/point.hpp"

#include <array>
#include <memory>

struct eval {
    float height = {};
    float weight = {};
};

class ctree {
public:
    virtual ~ctree() noexcept {};

    virtual eval eval_at(point) const = 0;
};

using shared_ctree = std::shared_ptr<ctree>;
