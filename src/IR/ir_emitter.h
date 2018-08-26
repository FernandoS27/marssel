
// Copyright 2018 Dynarmic Project / 2018 Marssel Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "common/types.h"
#include "frontend/ir/basic_block.h"
#include "frontend/ir/location_descriptor.h"
#include "frontend/ir/terminal.h"
#include "IR/value.h"

// Marssel AOT Microinstruction Intermediate Representation
//
// This intermediate representation is an SSA IR. It is designed primarily for analysis,
// though it can be lowered into a reduced form for interpretation. Each IR node (Value)
// is a microinstruction of an idealised GPU. The choice of microinstructions is made
// not based on any existing microarchitecture but on ease of implementation.

namespace Marssel::IR {

enum class Opcode;

/**
 * Convenience class to construct a basic block of the intermediate representation.
 * `block` is the resulting block.
 * The user of this class updates `current_location` as appropriate.
 */
class IREmitter {
public:
    explicit IREmitter(Block& block) : block(block), insertion_point(block.end()) {}

    Block& block;

    U1 Imm1(bool value);
    U8 Imm8(u8 value);
    U16 Imm16(u16 value);
    U32 Imm32(u32 value);
    U64 Imm64(u64 value);
    F32 ImmF32(f32 value);
    F64 ImmF64(f64 value);
    V4F ImmV4F(v4f value);

    U32 IntLoad(const Symbol& a );
    U32 IntAdd(const U32& a, const U32& b );
    U8 IntCompEqual(const U32& a, const U32& b );
    U8 IntCompGreaterThan(const U32& a, const U32& b );
    U8 IntCompLesserThan(const U32& a, const U32& b );
    U8 IntCompGreaterEqual(const U32&, const U32& b );
    U8 IntCompLesserEqual(const U32&, const U32& b );
    Void IntStore(const Symbol& a, const U32& b );
    U32 IntTruncate(const F32& a );

    V4F VectorLoad(const Symbol& a);
    Void VectorStore(const Symbol& a, const V4F& b);
    F32 VectorExtract(const V4F& a, const U32& b);
    V4F VectorInsert(const V4F& a, const U32& b, const F32& c);
    V4F VectorShuffle(const V4F& a, const U8& b);
    V4F VectorSelect(const V4F& a, const V4F& b, const U8& c);
    F32 VectorDot(const V4F& a, const V4F& b);
    F32 VectorDistance(const V4F& a, const V4F& b);
    V4F VectorMul(const V4F& a, const V4F& b);
    V4F VectorAdd(const V4F& a, const V4F& b);
    V4F VectorReciprocal(const V4F& a);
    V4F VectorSquareRoot(const V4F& a);
    V4F VectorInverseSquareRoot(const V4F& a);
    V4F VectorNeg(const V4F& a);
    V4F VectorCompEqual(const V4F& a, const V4F& b);
    V4F VectorCompGreaterThan(const V4F& a, const V4F& b);
    V4F VectorCompLesserThan(const V4F& a, const V4F& b);
    V4F VectorCompGreaterEqual(const V4F& a, const V4F& b);
    V4F VectorCompLesserEqual(const V4F& a, const V4F& b);

    void SetTerm(const Terminal& terminal);

    void SetInsertionPoint(IR::Inst* new_insertion_point);
    void SetInsertionPoint(IR::Block::iterator new_insertion_point);

protected:
    IR::Block::iterator insertion_point;

    template<typename T = Value, typename ...Args>
    T Inst(Opcode op, Args ...args) {
        auto iter = block.PrependNewInst(insertion_point, op, {Value(args)...});
        return T(Value(&*iter));
    }
};

} // namespace Marssel::IR
