

class final EmitSPIRV {

private:
  std::string buffer;

public:
  void EmitVariable();
  void EmitConstant();

  #define OPCODE(name, type, ...) void Emit##name(EmitContext& ctx, IR::Inst* inst);
  #include "frontend/ir/opcodes.inc"
  #undef OPCODE

  // Terminal instruction emitters
  void EmitTerminal(IR::Terminal terminal, IR::LocationDescriptor initial_location);
  virtual void EmitTerminalImpl(IR::Term::ReturnToDispatch terminal, IR::LocationDescriptor initial_location) = 0;
  virtual void EmitTerminalImpl(IR::Term::LinkBlock terminal, IR::LocationDescriptor initial_location) = 0;
  virtual void EmitTerminalImpl(IR::Term::If terminal, IR::LocationDescriptor initial_location) = 0;

};

//dwest06, aitorres
//
