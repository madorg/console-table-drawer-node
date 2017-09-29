#include <vector>
#include <string>

#include "node.h"

#include "src/TableDrawer.h"

// TODO: is it good name?
std::vector<std::vector<std::string>> ConvertV8ArrayBasedTableToCppVectorBasedTable(v8::Local<v8::Array> v8ArrayBasedTable) {
  std::vector<std::vector<std::string>> cppVectorBasedTable(v8ArrayBasedTable->Length());

  for (unsigned int i = 0; i < v8ArrayBasedTable->Length(); i++) {
    v8::Local<v8::Array> v8ArrayBasedRow = v8::Local<v8::Array>::Cast(v8ArrayBasedTable->Get(i));

    for (unsigned int j = 0; j < v8ArrayBasedRow->Length(); j++) {
      v8::String::Utf8Value cell(v8ArrayBasedRow->Get(j)->ToString());
      cppVectorBasedTable[i].push_back(std::string(*cell));
    }
  }

  return cppVectorBasedTable;
}

void EntryPoint(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  // TODO: validate args

  v8::Local<v8::Array> v8ArrayBasedTable = v8::Local<v8::Array>::Cast(args[0]);
  std::vector<std::vector<std::string>> cppVectorBasedTable = ConvertV8ArrayBasedTableToCppVectorBasedTable(v8ArrayBasedTable);

  tabledrawer::printTable(1, 1, cppVectorBasedTable);
}

void Init(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "printTable", EntryPoint);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)