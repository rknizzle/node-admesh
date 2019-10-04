#include "Wrapper.h"

Napi::Value EmptyCallback(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return env.Undefined();
}

Napi::FunctionReference Wrapper::constructor;

Napi::Object Wrapper::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  // define the "Mesh" functions and values here
  Napi::Function func = DefineClass(env, "Mesh", {
    InstanceMethod("open", &Wrapper::open),
    InstanceMethod("write", &Wrapper::write),
    InstanceMethod("repair", &Wrapper::repair)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Mesh", func);
  return exports;
}

// constructor
Wrapper::Wrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Wrapper>(info)  {
}

// open an stl file and read in the data
Napi::Value Wrapper::open(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
  int length = info.Length();
  Napi::String fileName;

  if (length == 1 && info[0].IsString()) {
    fileName = info[0].As<Napi::String>();
  }
  else if (length > 0 && !info[0].IsString()) {
    deferred.Reject(Napi::String::New(Env(), "Expected string argument"));
    return deferred.Promise();
  }
  else {
    deferred.Reject(Napi::String::New(Env(), "Incorrect argument provided"));
    return deferred.Promise();
  }

  std::string fileNameAsString = std::string(fileName);
  Napi::Function callback = Napi::Function::New(env, EmptyCallback);

  // create async worker for stl_open function
  OpenFileAsyncWorker *worker = new OpenFileAsyncWorker(callback, deferred, &stl, fileNameAsString);
  worker->Queue();

  return deferred.Promise();
}

// write mesh data to file
Napi::Value Wrapper::write(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
  Napi::Function callback = Napi::Function::New(env, EmptyCallback);
  int length = info.Length();
  Napi::String fileName;

  if (length == 1 && info[0].IsString()) {
    fileName = info[0].As<Napi::String>();
  }
  else if (length > 0 && !info[0].IsString()) {
    deferred.Reject(Napi::String::New(Env(), "Expected string argument"));
    return deferred.Promise();
  }
  else {
    deferred.Reject(Napi::String::New(Env(), "Incorrect argument provided"));
    return deferred.Promise();
  }

  if (!has_mesh_data()) {
    deferred.Reject(Napi::String::New(Env(), "No mesh data to write"));
    return deferred.Promise();
  }

  std::string fileNameAsString = std::string(fileName);

  // create async worker for stl_write function
  WriteFileAsyncWorker *worker = new WriteFileAsyncWorker(callback, deferred, &stl, fileNameAsString);
  worker->Queue();

  return deferred.Promise();
}

// run repair algorithm on mesh
Napi::Value Wrapper::repair(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
  Napi::Function callback = Napi::Function::New(env, EmptyCallback);

  if (!has_mesh_data()) {
    deferred.Reject(Napi::String::New(Env(), "No mesh data to repair"));
    return deferred.Promise();
  }


  // create async worker for stl_repair function
  RepairFileAsyncWorker *worker = new RepairFileAsyncWorker(callback, deferred, &stl);
  worker->Queue();

  return deferred.Promise();
}

bool Wrapper::has_mesh_data() {
  if (stl.stats.number_of_facets > 0) {
    return true;
  }
  return false;
}
