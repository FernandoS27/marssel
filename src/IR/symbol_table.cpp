#include "IR\symbol_table.h"

namespace Marssel::IR {

  constexpr u32 PRERESERVE = 64;
  const std::string constant_prefix = "const_";
  const std::string variable_prefix = "var_";
  const std::string function_prefix = "func_";
  const std::string function_parameter_prefix = "fparam_";

  SymbolTable::SymbolTable() {
    start_index = nullSymbol() + 1;
    inner_size = PRERESERVE;
    function_start_id = 0;
    expand();
  }

  u32 SymbolTable::declareConstant(Value val) {
    std::string tmp_key = constant_prefix + value.toString();
    u32 new_symbol = registerNewSymbol(tmp_key);
    types[new_symbol] = val.GetType();
    values[new_symbol] =  val;
    symbol_category[new_symbol] = SymbolType::Constant;
    return new_symbol;
  }

  u32 SymbolTable::declareConstant(std::string key, Value val) {
    std::string tmp_key = constant_prefix + key;
    u32 new_symbol = registerNewSymbol(tmp_key);
    types[new_symbol] = val.GetType();
    values[new_symbol] =  val;
    symbol_category[new_symbol] = SymbolType::Constant;
    return new_symbol;
  }

  u32 SymbolTable::declareVariable(std::string key, Type type, u32 flags) {
    std::string tmp_key = variable_prefix + key;
    u32 new_symbol = registerNewSymbol(tmp_key);
    types[new_symbol] = type;
    values[new_symbol] =  Value(Type::Symbol);
    symbol_category[new_symbol] = SymbolType::Variable;
    symbol_data[new_symbol].var_data.flags = flags;
    return new_symbol;
  }

  u32 SymbolTable::declareVariableArray(std::string key, Type type, u32 flags, u32 size) {
    u32 new_symbol = declareVariable(key, type, flags | VariableFlags::Array);
    symbol_data[new_symbol].var_data.size = size;
    return new_symbol;
  }

  u32 SymbolTable::declareFunction(std::string key, Type type, u32 flags) {
    std::string tmp_key = function_prefix + key;
    u32 new_symbol = registerNewSymbol(tmp_key);
    types[new_symbol] = type;
    values[new_symbol] =  Value(Type::Symbol);
    symbol_category[new_symbol] = SymbolType::Function;
    symbol_data[new_symbol].func_data.flags = flags;
    symbol_data[new_symbol].func_data.id = function_start_id;
    function_start_id++;
    return new_symbol;
  }

  u32 SymbolTable::findConstant(std::string key) {
    std::string tmp_key = constant_prefix + key;
    return findSymbol(tmp_key);
  }

  u32 SymbolTable::findConstant(Value value) {
    std::string tmp_key = constant_prefix + value.toString();
    return findSymbol(tmp_key);
  }

  u32 SymbolTable::findVariable(std::string key) {
    std::string tmp_key = variable_prefix + key;
    return findSymbol(tmp_key);
  }

  u32 SymbolTable::findFunction(std::string key) {
    std::string tmp_key = function_prefix + key;
    return findSymbol(tmp_key);
  }

  u32 SymbolTable::registerNewSymbol(std::string key) {
    u32 new_index = start_index;
    start_index++;
    if (start_index > inner_size) {
      inner_size *= 2;
      expand();
    }
    symbol_ids[key] = new_index;
    return new_index;
  }

  u32 SymbolTable::findSymbol(std::string key) {
    if (symbol_ids.count(key))
      return symbol_ids[key];
    return nullSymbol();
  }

  void SymbolTable::expand() {
    symbol_ids.reserve(inner_size);
    types.reserve(inner_size);
    values.reserve(inner_size);
    symbol_category.reserve(inner_size);
    symbol_data.reserve(inner_size);
  }

} // Marssel::IR
