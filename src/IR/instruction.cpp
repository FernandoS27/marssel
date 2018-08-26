#include <algorithm>

#include "common/assert.h"
#include "IR/instruction.h"

namespace Marssel::IR {

bool Inst::AreAllArgsImmediates() const {
    return std::all_of(args.begin(), args.begin() + NumArgs(), [](const auto& value){ return value.IsImmediate(); });
}

Type Inst::GetType() const {
    if (op == Opcode::Identity)
        return args[0].GetType();
    return GetTypeOf(op);
}

Value Inst::GetArg(size_t index) const {
    ASSERT(index < GetNumArgsOf(op));
    ASSERT(!args[index].IsEmpty());

    return args[index];
}

void Inst::SetArg(size_t index, Value value) {
    ASSERT(index < GetNumArgsOf(op));
    ASSERT(AreTypesCompatible(value.GetType(), GetArgTypeOf(op, index)));

    if (!args[index].IsImmediate()) {
        UndoUse(args[index]);
    }
    if (!value.IsImmediate()) {
        Use(value);
    }

    args[index] = value;
}

void Inst::Invalidate() {
    ClearArgs();
    op = Opcode::Void;
}

void Inst::ClearArgs() {
    for (auto& value : args) {
        if (!value.IsImmediate()) {
            UndoUse(value);
        }
        value = {};
    }
}

void Inst::ReplaceUsesWith(Value replacement) {
    Invalidate();

    op = Opcode::Identity;

    if (!replacement.IsImmediate()) {
        value.GetInst()->use_count++;
    }

    args[0] = replacement;
}

} // namespace Marssel::IR
