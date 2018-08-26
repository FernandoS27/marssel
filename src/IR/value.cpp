
#include "common/assert.h"
#include "IR/instruction.h"
#include "IR/value.h"

namespace Marssel::IR {

Value::Value(Inst* value) : type(Type::Opaque) {
    inner.inst = value;
}

Value::Value(bool value) : type(Type::U1) {
    inner.imm_u1 = value;
}

Value::Value(u8 value) : type(Type::U8) {
    inner.imm_u8 = value;
}

Value::Value(u16 value) : type(Type::U16) {
    inner.imm_u16 = value;
}

Value::Value(u32 value) : type(Type::U32) {
    inner.imm_u32 = value;
}

Value::Value(u64 value) : type(Type::U64) {
    inner.imm_u64 = value;
}

Value::Value(f32 value) : type(Type::F32) {
    inner.imm_f32 = value;
}

Value::Value(f64 value) : type(Type::F64) {
    inner.imm_f64 = value;
}

Value::Value(v4f value) : type(Type::V4F) {
    inner.imm_v4f = value;
}

Value::Value(v4i value) : type(Type::V4I) {
    inner.imm_v4i = value;
}

bool Value::IsImmediate() const {
    if (type == Type::Opaque)
        return inner.inst->GetOpcode() == Opcode::Identity ? inner.inst->GetArg(0).IsImmediate() : false;
    return true;
}

bool Value::IsEmpty() const {
    return type == Type::Void;
}

Type Value::GetType() const {
    if (type == Type::Opaque) {
        if (inner.inst->GetOpcode() == Opcode::Identity) {
            return inner.inst->GetArg(0).GetType();
        } else {
            return inner.inst->GetType();
        }
    }
    return type;
}

Inst* Value::GetInst() const {
    ASSERT(type == Type::Opaque);
    return inner.inst;
}

bool Value::GetU1() const {
    if (type == Type::Opaque && inner.inst->GetOpcode() == Opcode::Identity)
        return inner.inst->GetArg(0).GetU1();
    ASSERT(type == Type::U1);
    return inner.imm_u1;
}

u8 Value::GetU8() const {
    if (type == Type::Opaque && inner.inst->GetOpcode() == Opcode::Identity)
        return inner.inst->GetArg(0).GetU8();
    ASSERT(type == Type::U8);
    return inner.imm_u8;
}

u16 Value::GetU16() const {
    if (type == Type::Opaque && inner.inst->GetOpcode() == Opcode::Identity)
        return inner.inst->GetArg(0).GetU16();
    ASSERT(type == Type::U16);
    return inner.imm_u16;
}

u32 Value::GetU32() const {
    if (type == Type::Opaque && inner.inst->GetOpcode() == Opcode::Identity)
        return inner.inst->GetArg(0).GetU32();
    ASSERT(type == Type::U32);
    return inner.imm_u32;
}

u64 Value::GetU64() const {
    if (type == Type::Opaque && inner.inst->GetOpcode() == Opcode::Identity)
        return inner.inst->GetArg(0).GetU64();
    ASSERT(type == Type::U64);
    return inner.imm_u64;
}

f32 Value::GetF32() const {
    if (type == Type::Opaque && inner.inst->GetOpcode() == Opcode::Identity)
        return inner.inst->GetArg(0).GetF32();
    ASSERT(type == Type::F32);
    return inner.imm_f32;
}

f64 Value::GetF64() const {
    if (type == Type::Opaque && inner.inst->GetOpcode() == Opcode::Identity)
        return inner.inst->GetArg(0).GetF64();
    ASSERT(type == Type::F64);
    return inner.imm_f64;
}

f64 Value::GetF64() const {
    if (type == Type::Opaque && inner.inst->GetOpcode() == Opcode::Identity)
        return inner.inst->GetArg(0).GetF64();
    ASSERT(type == Type::F64);
    return inner.imm_f64;
}

v4f Value::GetV4F() const {
    if (type == Type::Opaque && inner.inst->GetOpcode() == Opcode::Identity)
        return inner.inst->GetArg(0).GetV4F();
    ASSERT(type == Type::V4F);
    return inner.imm_v4f;
}

v4i Value::GetV4I() const {
    if (type == Type::Opaque && inner.inst->GetOpcode() == Opcode::Identity)
        return inner.inst->GetArg(0).GetV4I();
    ASSERT(type == Type::V4I);
    return inner.imm_v4i;
}

std::string toString() {
  switch (type) {
    case Type::Void:
      return "void";
    case Type::Opaque:
      return "opaque";
    case Type::Symbol:
      return "symbol";
    case Type::Ptr:
      return "ptr";
    case Type::U1:
      return (inner.imm_u1 ? "b:(true)" | "b:(false)");
    case Type::U8:
      return "u8:("+ std::to_string(inner.imm_u8) + ")";
    case Type::U16:
      return "u16:("+ std::to_string(inner.imm_u16) + ")";
    case Type::U32:
      return "u32:("+ std::to_string(inner.imm_u32) + ")";
    case Type::U64:
      return "u64:("+ std::to_string(inner.imm_u64) + ")";
    case Type::F32:
      return "f32:("+ std::to_string(inner.imm_f32) + ")";
    case Type::F64:
      return "f64:("+ std::to_string(inner.imm_f64) + ")";
    case Type::V4F:
      return "v4f:("+ std::to_string(inner.imm_v4f[0]) + "," +
                      std::to_string(inner.imm_v4f[1]) + "," +
                      std::to_string(inner.imm_v4f[2]) + "," +
                      std::to_string(inner.imm_v4f[3]) + ")";
    case Type::V4I:
      return "v4i:("+ std::to_string(inner.imm_v4i[0]) + "," +
                      std::to_string(inner.imm_v4i[1]) + "," +
                      std::to_string(inner.imm_v4i[2]) + "," +
                      std::to_string(inner.imm_v4i[3]) + ")";
    default:
      return "unknown";
  }
}


} // namespace Marssel::IR
