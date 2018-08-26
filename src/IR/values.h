// Copyright 2018 Dynarmic Project / 2018 Marssel Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <string>

class Inst;

/**
 * A representation of a value in the IR.
 * A value may either be an immediate or the result of a microinstruction.
 */
class Value {
public:
    Value() : type(Type::Void) {}
    explicit Value(Inst* value);
    explicit Value(bool value);
    explicit Value(u8 value);
    explicit Value(u16 value);
    explicit Value(u32 value);
    explicit Value(u64 value);
    explicit Value(v4f value);
    explicit Value(v4i value);
    Value(Type specialType) : type(specialType) {}

    bool IsEmpty() const;
    bool IsImmediate() const;
    Type GetType() const;

    Inst* GetInst() const;
    bool GetU1() const;
    u8 GetU8() const;
    u16 GetU16() const;
    u32 GetU32() const;
    u64 GetU64() const;
    v4f GetV4F() const;
    v4i GetV4I() const;
    std::string toString() const;

private:
    Type type;

    union {
        Inst* inst; // type == Type::Opaque
        bool imm_u1;
        u8 imm_u8;
        u16 imm_u16;
        u32 imm_u32;
        u64 imm_u64;
        f32 imm_f32;
        f64 imm_f64;
        v4f imm_v4f;
        v4i imm_v4i;
    } inner;

    u32 index;
};
static_assert(sizeof(Value) <= 2 * sizeof(u64), "IR::Value should be kept small in size");

template <Type type_>
class TypedValue final : public Value {
public:
    TypedValue() = default;

    template <Type other_type, typename = std::enable_if_t<(other_type & type_) != Type::Void>>
    /* implicit */ TypedValue(const TypedValue<other_type>& value) : Value(value) {
        ASSERT((value.GetType() & type_) != Type::Void);
    }

    explicit TypedValue(const Value& value) : Value(value) {
        ASSERT((value.GetType() & type_) != Type::Void);
    }
};

using U1 = TypedValue<Type::U1>;
using U8 = TypedValue<Type::U8>;
using U16 = TypedValue<Type::U16>;
using U32 = TypedValue<Type::U32>;
using U64 = TypedValue<Type::U64>;
using F32 = TypedValue<Type::F32>;
using F64 = TypedValue<Type::F64>;
using V4F = TypedValue<Type::V4F>;
using V4I = TypedValue<Type::V4I>;
using Symbol = TypedValue<Type::Symbol>;
