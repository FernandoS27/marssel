// Copyright 2018 Marssel Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <string>
#include <unordered_map>
#include <vector>
#include "IR/value.h"
#include "IR/opcode.h"

namespace Marssel::IR {

class SymbolTable {
public:

  SymbolTable();

  ~SymbolTable() = default;

  u32 declareConstant(std::string key, Value val);
  u32 declareVariable(std::string key, Type type, u32 flags);
  u32 declareVariableArray(std::string key, Type type, u32 flags, u32 size);
  u32 declareFunction(std::string key, Type type, u32 flags);

  u32 findConstant(std::string key);
  u32 findConstant(Value value);

  u32 findVariable(std::string key);

  u32 findFunction(std::string key);

  u32 nullSymbol() { return 0; }

  enum class VariableFlags {
    Array = 1 << 0,
    Input = 1 << 1,
    Output = 1 << 2,
    Uniform = 1 << 3,
    Atomic = 1 << 4,
    ReadOnly = 1 << 5
  }

private:
  enum class SymbolType {
    Variable,
    Function,
    Constant,
    FunctionParameter
  }
  struct VariableData {
    u32 flags;
    size_t size;
  }
  struct FunctionData {
    u32 flags;
    u32 parameters;
    u32 id;
  }
  struct SymbolDeclare {
    union {
      VariableData var_data;
      FunctionData func_data;
      u32 id; // for parameters
    }
  }

  u32 registerNewSymbol(std::string key);
  u32 findSymbol(std::string key);
  void expand();

  u32 start_index;
  u32 inner_size;
  u32 function_start_id;
  std::unordered_map<std::string, u32> symbol_ids;
  std::vector<Type> types;
  std::vector<Value> values;
  std::vector<SymbolType> symbol_category;
  std::vector<SymbolDeclare> symbol_data;
}

} // Marssel::IR
