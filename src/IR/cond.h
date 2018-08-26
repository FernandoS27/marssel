// Copyright 2018 Dynarmic Project / 2018 Marssel Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "common/types.h"

namespace Marssel {
namespace IR {

enum class Cond {
    EQ, NE, CS, CC, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, AL, NV,
    HS = CS, LO = CC,
};

inline Cond invert(Cond c) {
	return static_cast<Cond>(static_cast<size_t>(c) ^ 1);
}

} // namespace IR
} // namespace Marssel
