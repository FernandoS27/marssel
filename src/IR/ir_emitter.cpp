#include "common/assert.h"
#include "frontend/ir/ir_emitter.h"
#include "frontend/ir/opcodes.h"

namespace Marssel::IR {

U1 IREmitter::Imm1(bool imm1) {
    return U1(Value(imm1));
}

U8 IREmitter::Imm8(u8 imm8) {
    return U8(Value(imm8));
}

U16 IREmitter::Imm16(u16 imm16) {
    return U16(Value(imm16));
}

U32 IREmitter::Imm32(u32 imm32) {
    return U32(Value(imm32));
}

U64 IREmitter::Imm64(u64 imm64) {
    return U64(Value(imm64));
}

F32 IREmitter::ImmF32(f32 imm32) {
    return F32(Value(imm32));
}

F64 IREmitter::ImmF64(f64 imm64) {
    return F64(Value(imm64));
}

V4F IREmitter::ImmV4F(v4f immv4f) {
    return V4F(Value(immv4f));
}

U32 IREmitter::IntLoad(const Symbol& a )
{
  return Inst<U32>(Opcode::IntLoad, a);
}

U32 IREmitter::IntAdd(const U32& a, const U32& b )
{
  return Inst<U32>(Opcode::IntAdd, a, b);
}

U8 IREmitter::IntCompEqual(const U32& a, const U32& b )
{
  return Inst<U32>(Opcode::IntCompEqual, a, b);
}

U8 IREmitter::IntCompGreaterThan(const U32& a, const U32& b )
{
  return Inst<U32>(Opcode::IntCompGreaterThan, a, b);
}

U8 IREmitter::IntCompLesserThan(const U32& a, const U32& b )
{
  return Inst<U32>(Opcode::IntCompLesserThan, a, b);
}

U8 IREmitter::IntCompGreaterEqual(const U32&, const U32& b )
{
  return Inst<U32>(Opcode::IntCompGreaterEqual, a, b);
}

U8 IREmitter::IntCompLesserEqual(const U32&, const U32& b )
{
  return Inst<U32>(Opcode::IntCompLesserEqual, a, b);
}

Void IREmitter::IntStore(const Symbol& a, const U32& b )
{
  return Inst<Void>(Opcode::IntStore, a, b);
}

U32 IREmitter::IntTruncate(const F32& a )
{
  return Inst<U32>(Opcode::IntTruncate, a);
}

V4F IREmitter::VectorLoad(const Var& a)
{IREmitter::
  return Inst<V4F>(Opcode::VectorLoad, value);
}

Void IREmitter::VectorStore(const Var& a, const V4F& b)
{
  return Inst<Void>(Opcode::VectorStore, a, b);
}

F32 IREmitter::VectorExtract(const V4F& a, const U32& b)
{
  return Inst<F32>(Opcode::VectorExtract, a, b);
}

V4F IREmitter::VectorInsert(const V4F& a, const U32& b, const F32& c)
{
  return Inst<V4F>(Opcode::VectorInsert, a, b, c);
}

V4F IREmitter::VectorShuffle(const V4F& a, const U8& b)
{
  return Inst<V4F>(Opcode::VectorShuffle, a, b);
}

V4F IREmitter::VectorSelect(const V4F& a, const V4F& b, const U8& c)
{
  return Inst<V4F>(Opcode::VectorSelect, a, b, c);
}

F32 IREmitter::VectorDot(const V4F& a, const V4F& b)
{
  return Inst<F32>(Opcode::VectorDot, a, b);
}

F32 IREmitter::VectorDistance(const V4F& a, const V4F& b)
{
  return Inst<F32>(Opcode::VectorDistance, a, b);
}

V4F IREmitter::VectorMul(const V4F& a, const V4F& b)
{
  return Inst<V4F>(Opcode::VectorMul, a, b);
}

V4F IREmitter::VectorAdd(const V4F& a, const V4F& b)
{
  return Inst<V4F>(Opcode::VectorAdd, a, b);
}

V4F IREmitter::VectorReciprocal(const V4F& a)
{
  return Inst<V4F>(Opcode::VectorReciprocal, a, b);
}

V4F IREmitter::VectorSquareRoot(const V4F& a)
{
  return Inst<V4F>(Opcode::VectorSquareRoot, a, b);
}

V4F IREmitter::VectorInverseSquareRoot(const V4F& a)
{
  return Inst<V4F>(Opcode::VectorInverseSquareRoot, a, b);
}

V4F IREmitter::VectorNeg(const V4F& a)
{
  return Inst<V4F>(Opcode::VectorNeg, a);
}

V4F IREmitter::VectorCompEqual(const V4F& a, const V4F& b)
{
  return Inst<V4F>(Opcode::VectorCompEqual, a, b);
}

V4F IREmitter::VectorCompGreaterThan(const V4F& a, const V4F& b)
{
  return Inst<V4F>(Opcode::VectorCompGreaterThan, a, b);
}

V4F IREmitter::VectorCompLesserThan(const V4F& a, const V4F& b)
{
  return Inst<V4F>(Opcode::VectorCompLesserThan, a, b);
}

V4F IREmitter::VectorCompGreaterEqual(const V4F& a, const V4F& b)
{
  return Inst<V4F>(Opcode::VectorCompGreaterEqual, a, b);
}

V4F IREmitter::VectorCompLesserEqual(const V4F& a, const V4F& b)
{
  return Inst<V4F>(Opcode::VectorCompLesserEqual, a, b);
}

void IREmitter::SetTerm(const Terminal& terminal) {
    block.SetTerminal(terminal);
}

void IREmitter::SetInsertionPoint(IR::Inst* new_insertion_point) {
    insertion_point = IR::Block::iterator{*new_insertion_point};
}

void IREmitter::SetInsertionPoint(IR::Block::iterator new_insertion_point) {
    insertion_point = new_insertion_point;
}

} // namespace Marssel::IR
