#ifndef ROTATEASYNCWORKER_H
#define ROTATEASYNCWORKER_H

#include <napi.h>
#include "../src/stl.h"

class RotateAsyncWorker : public Napi::AsyncWorker
{
  public:
    RotateAsyncWorker(Napi::Function &callback, Napi::Promise::Deferred deferred, stl_file *stl, std::string axis, int angle);
    void Execute();
    void OnOK();
    void OnError(const Napi::Error& e);
  private:
    std::string axis;
    int angle;
    Napi::Promise::Deferred deferred;
    stl_file *stl;
};
#endif /* ROTATEASYNCWORKER_H */
