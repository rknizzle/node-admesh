#ifndef WRAPPER_H
#define WRAPPER_H

#include <napi.h>
#include "../src/stl.h"
#include "WriteFileAsyncWorker.h"
#include "OpenFileAsyncWorker.h"
#include "RepairFileAsyncWorker.h"
#include "ScaleAsyncWorker.h"


class Wrapper : public Napi::ObjectWrap<Wrapper> {
 public:
   //Init function for setting the export key to JS
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  //Constructor to initialise
  Wrapper(const Napi::CallbackInfo& info);
  bool has_mesh_data();

 private:
  //reference to store the class definition that needs to be exported to JS
  static Napi::FunctionReference constructor;
  Napi::Value open(const Napi::CallbackInfo& info);
  Napi::Value write(const Napi::CallbackInfo& info);
  Napi::Value repair(const Napi::CallbackInfo& info);
  Napi::Value scale(const Napi::CallbackInfo& info);
  Napi::Value getProperties(const Napi::CallbackInfo& info);

  // STL instance
  stl_file stl;
};
#endif /* WRAPPER_H */
