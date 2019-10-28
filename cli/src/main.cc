#include <napi.h>

#include "List.hh"

static auto InitAll(Napi::Env env, Napi::Object exports) -> Napi::Object {
  Lab1::List<std::string> l;
  l.insert("sss");
  return exports;
}

NODE_API_MODULE(dscliaddon, InitAll)