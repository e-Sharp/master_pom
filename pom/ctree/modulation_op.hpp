#pragma once

#include "pom/ctree/ctree.hpp"

#include <memory>

template<typename F>
class modulation_op : public ctree {
public:
    modulation_op(F f, const std::shared_ptr<ctree>& subtree)
        : f{std::move(f)}
        , subtree{subtree}
    {}

    eval eval_at(point p) const override {
        auto e = subtree->eval_at(p);
        e.height = f(e.height);
        return e;
    }

private:
    F f;
    std::shared_ptr<ctree> subtree;
};
