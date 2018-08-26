// Copyright 2018 Dynarmic Project / 2018 Marssel Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <array>

#include "common/intrusive_list.h"
#include "IR/types.h"
#include "IR/opcodes.h"
#include "IR/value.h"

namespace Marssel::IR {

/**
 * A representation of a microinstruction. A single ARM/Thumb instruction may be
 * converted into zero or more microinstructions.
 */
class Inst final : public Common::IntrusiveListNode<Inst> {
public:
    explicit Inst(Opcode op) : op(op) {}

    /// Determines if all arguments of this instruction are immediates.
    bool AreAllArgsImmediates() const;

    size_t UseCount() const { return use_count; }
    bool HasUses() const { return use_count > 0; }

    /// Get the microop this microinstruction represents.
    Opcode GetOpcode() const { return op; }
    /// Get the type this instruction returns.
    Type GetType() const;
    /// Get the number of arguments this instruction has.
    size_t NumArgs() const { return GetNumArgsOf(op); }

    Value GetArg(size_t index) const;
    void SetArg(size_t index, Value value);

    void Invalidate();
    void ClearArgs();

    void ReplaceUsesWith(Value replacement);

private:

    Opcode op;
    size_t use_count = 0;
    std::array<Value, 4> args;

};

} // namespace Dynarmic::IR
