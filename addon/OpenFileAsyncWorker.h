#ifndef OPENFILEASYNCWORKER_H
#define OPENFILEASYNCWORKER_H

#include <napi.h>
#include "../src/stl.h"

class OpenFileAsyncWorker : public Napi::AsyncWorker
{
  public:
    OpenFileAsyncWorker(Napi::Function &callback, Napi::Promise::Deferred deferred, stl_file *stl, std::string infileName);
    void Execute();
    void OnOK();
    void OnError(const Napi::Error& e);
  private:
    Napi::Promise::Deferred deferred;
    stl_file *stl;
    std::string infileName;
};
#endif /* OPENFILEASYNCWORKER_H */
