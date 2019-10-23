#include "ScaleAsyncWorker.h"

ScaleAsyncWorker::ScaleAsyncWorker(Napi::Function &callback, Napi::Promise::Deferred deferred, stl_file *stl, int factor)
  : Napi::AsyncWorker(callback), deferred(deferred), stl(stl), factor(factor)
{
}

void ScaleAsyncWorker::Execute() {
  stl_scale(stl, factor);

  if (stl->error) {
    // return rejected promise
    SetError(stl->error_msg);
  }
}

void ScaleAsyncWorker::OnError(const Napi::Error& e) {
  Napi::HandleScope scope(Env());
  // reject promise with error value
  deferred.Reject(e.Value());

  // Call empty function
  Callback().Call({});
}

void ScaleAsyncWorker::OnOK() {
  Napi::HandleScope scope(Env());
  // value to return
  deferred.Resolve(Napi::Boolean::New(Env(), true));

  // Call empty function
  Callback().Call({});
}
