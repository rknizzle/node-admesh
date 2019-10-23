#include "RotateAsyncWorker.h"

RotateAsyncWorker::RotateAsyncWorker(Napi::Function &callback, Napi::Promise::Deferred deferred, stl_file *stl, std::string axis, int angle)
  : Napi::AsyncWorker(callback), deferred(deferred), stl(stl), axis(axis), angle(angle)
{
}

void RotateAsyncWorker::Execute() {
  if (axis == "x") {
    stl_rotate_x(stl, angle);
  }
  else if (axis == "y") {
    stl_rotate_y(stl, angle);
  }
  else if (axis == "z") {
    stl_rotate_z(stl, angle);
  }
  else {
    SetError("Must specify x, y, or z axis");
  }

  if (stl->error) {
    // return rejected promise
    SetError(stl->error_msg);
  }
}

void RotateAsyncWorker::OnError(const Napi::Error& e) {
  Napi::HandleScope scope(Env());
  // reject promise with error value
  deferred.Reject(e.Value());

  // Call empty function
  Callback().Call({});
}

void RotateAsyncWorker::OnOK() {
  Napi::HandleScope scope(Env());
  // value to return
  deferred.Resolve(Napi::Boolean::New(Env(), true));

  // Call empty function
  Callback().Call({});
}
