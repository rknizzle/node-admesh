#ifndef SCALEASYNCWORKER_H
#define SCALEASYNCWORKER_H

#include <napi.h>
#include "../src/stl.h"

class ScaleAsyncWorker : public Napi::AsyncWorker
{
  public:
    ScaleAsyncWorker(Napi::Function &callback, Napi::Promise::Deferred deferred, stl_file *stl, int factor);
    void Execute();
    void OnOK();
    void OnError(const Napi::Error& e);
  private:
    int factor;
    Napi::Promise::Deferred deferred;
    stl_file *stl;
};
#endif /* SCALEASYNCWORKER_H */
