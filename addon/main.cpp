#include <napi.h>
#include "Wrapper.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return Wrapper::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
