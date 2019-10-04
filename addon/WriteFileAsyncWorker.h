#ifndef WRITEFILEASYNCWORKER_H
#define WRITEFILEASYNCWORKER_H

#include <napi.h>
#include "../src/stl.h"

class WriteFileAsyncWorker : public Napi::AsyncWorker
{
  public:
    WriteFileAsyncWorker(Napi::Function &callback, Napi::Promise::Deferred deferred, stl_file *stl,  std::string outfileName);
    void Execute();
    void OnOK();
    void OnError(const Napi::Error& e);
  private:
    Napi::Promise::Deferred deferred;
    std::string outfileName;
    stl_file *stl;
};
#endif /* WRITEFILEASYNCWORKER_H */
