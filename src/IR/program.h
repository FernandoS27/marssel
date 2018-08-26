// Copyright 2018 Marssel Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "value.h"
#include "instruction.h"
#include "terminal.h"
#include "basic_block.h"
#include "ir_emitter.h"
#include "opcode.h"
#include "symbol_table.h"

#include <unordered_map>
#include <array>

class Program {

private:
  SymbolTable symbol_table;
  unordered_map<LocationDescriptor, Instruction * > location_table;
  std::vector<Block> code;
}
