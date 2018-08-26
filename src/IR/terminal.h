// Copyright 2018 Dynarmic Project / 2018 Marssel Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <boost/variant.hpp>

#include "common/types.h"
#include "IR/cond.h"
#include "IR/location_descriptor.h"

namespace Marssel::IR {
namespace Term {

struct Invalid {};

/**
 * This terminal instruction jumps to the basic block described by `next`.
 */
struct LinkBlock {
    explicit LinkBlock(const LocationDescriptor& next_) : next(next_) {}
    LocationDescriptor next; ///< Location descriptor for next block.
};

struct ReturnToCallee {};

struct Call {
  explicit LinkBlock(const LocationDescriptor& next_) : next(next_) {}
  LocationDescriptor next; ///< Location descriptor for next block.
};

struct If;
/// A Terminal is the terminal instruction in a MicroBlock.
using Terminal = boost::variant<
        Invalid,
        LinkBlock,
        ReturnToCallee,
        Call,
        boost::recursive_wrapper<If>
>;

/**
 * This terminal instruction conditionally executes one terminal or another depending
 * on the run-time state of the ARM flags.
 */
struct If {
    If(Cond if_, Terminal then_, Terminal else_) : if_(if_), then_(then_), else_(else_) {}
    Cond if_;
    Terminal then_;
    Terminal else_;
};

} // namespace Term

using Term::Terminal;

} // namespace Marssel::IR
