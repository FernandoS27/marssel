//     opcode name,             return type,    arg1 type,      arg2 type,      arg3 type,      ...

OPCODE(Void,                    T::Void,                                                        )
OPCODE(Identity,                T::Opaque,      T::Opaque                                       )
OPCODE(OpPhi,                   T::Opaque,      T::Opaque,      T::Opaque                       )
OPCODE(AccessChain              T::Symbol,      T::Ptr,         T::U32                          )

OPCODE(IntLoad,                 T::U32,         T::Symbol                                       )
OPCODE(IntAdd,                  T::U32,         T::U32,         T::U32                          )
OPCODE(IntCompEqual,            T::U8,          T::U32,         T::U32                          )
OPCODE(IntCompGreaterThan,      T::U8,          T::U32,         T::U32                          )
OPCODE(IntCompLesserThan,       T::U8,          T::U32,         T::U32                          )
OPCODE(IntCompGreaterEqual,     T::U8,          T::U32,         T::U32                          )
OPCODE(IntCompLesserEqual,      T::U8,          T::U32,         T::U32                          )
OPCODE(IntStore,                T::Void,        T::Symbol,      T::U32                          )
OPCODE(IntTruncate,             T::U32,         T::F32                                          )

OPCODE(VectorLoad,              T::V4F,         T::Symbol                                       )
OPCODE(VectorStore,             T::Void,        T::Symbol,      T::V4F                          )
OPCODE(VectorExtract,           T::F32,         T::V4F,         T::U32                          )
OPCODE(VectorInsert,            T::V4F,         T::V4F,         T::U32,         T::F32          )
OPCODE(VectorShuffle,           T::V4F,         T::V4F,         T::U8                           )
OPCODE(VectorSelect,            T::V4F,         T::V4F,         T::V4F,         T::U8           )
OPCODE(VectorDot,               T::F32,         T::V4F,         T::V4F                          )
OPCODE(VectorDistance,          T::F32,         T::V4F,         T::V4F                          )
OPCODE(VectorMul,               T::V4F,         T::V4F,         T::V4F                          )
OPCODE(VectorAdd,               T::V4F,         T::V4F,         T::V4F                          )
OPCODE(VectorReciprocal,        T::V4F,         T::V4F                                          )
OPCODE(VectorSquareRoot,        T::V4F,         T::V4F                                          )
OPCODE(VectorInverseSquareRoot, T::V4F,         T::V4F                                          )
OPCODE(VectorNeg,               T::V4F,         T::V4F                                          )
OPCODE(VectorCompEqual,         T::V4F,         T::V4F,         T::V4F                          )
OPCODE(VectorCompGreaterThan,   T::V4F,         T::V4F,         T::V4F                          )
OPCODE(VectorCompLesserThan,    T::V4F,         T::V4F,         T::V4F                          )
OPCODE(VectorCompGreaterEqual,  T::V4F,         T::V4F,         T::V4F                          )
OPCODE(VectorCompLesserEqual,   T::V4F,         T::V4F,         T::V4F                          )