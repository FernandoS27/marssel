// Copyright 2018 Dynarmic Project / 2018 Marssel Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <list>
#include <optional>
#include <string>

#pragma once

#include <iosfwd>
#include <string>

#include "IR/types.h"

namespace Marssel::IR {

/**
 * The Opcodes of our intermediate representation.
 * Type signatures for each opcode can be found in opcodes.inc
 */
enum class Opcode {
#define OPCODE(name, type, ...) name,
#include "opcodes.inc"
#undef OPCODE
    NUM_OPCODE
};

constexpr size_t OpcodeCount = static_cast<size_t>(Opcode::NUM_OPCODE);

enum class Type {
 Void = 1 << 0;
 U1 = 1 << 1;
 U16 = 1 << 2;
 U32 = 1 << 3;
 F16 = 1 << 4;
 F32 = 1 << 5;
 F64 = 1 << 6;
 V4F = 1 << 7;
 V4I = 1 << 8;
 Symbol = 1 << 9;
 Ptr = 1 << 10;
 Opaque = 1 << 11;
 U8 = 1 << 12;
}

constexpr Type operator|(Type a, Type b) {
    return static_cast<Type>(static_cast<size_t>(a) | static_cast<size_t>(b));
}

constexpr Type operator&(Type a, Type b) {
    return static_cast<Type>(static_cast<size_t>(a) & static_cast<size_t>(b));
}

/// Get return type of an opcode
Type GetTypeOf(Opcode op);

/// Get the number of arguments an opcode accepts
size_t GetNumArgsOf(Opcode op);

/// Get the required type of an argument of an opcode
Type GetArgTypeOf(Opcode op, size_t arg_index);

/// Get the name of an opcode.
std::string GetNameOf(Opcode op);

/// Get the name of a type.
std::string GetNameOf(Type type);

/// @returns true if t1 and t2 are compatible types
bool AreTypesCompatible(Type t1, Type t2);

std::ostream& operator<<(std::ostream& o, Opcode opcode);
std::ostream& operator<<(std::ostream& o, Type type);

} // namespace Dynarmic::IR
