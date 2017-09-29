#include <node.h>

#include "src/TableDrawer.h"

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Array;

void EntryPoint(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  // Local<Array> arr = Local<Array>::Cast(args[0]);

  // std::vector<double> v = { arr->Get(0)->NumberValue(), arr->Get(1)->NumberValue() };
  // for (int i = 0; i < v.size(); i++) {
  //   std::cout << v[i] << std::endl;
  // }

  tabledrawer::printTable(1, 1, {
    { "1", "2" },
    { "3", "4" }
  });
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "printTable", EntryPoint);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)