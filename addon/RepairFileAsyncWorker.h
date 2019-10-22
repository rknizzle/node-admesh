#ifndef REPAIRFILEASYNCWORKER_H
#define REPAIRFILEASYNCWORKER_H

#include <napi.h>
#include "../src/stl.h"

class RepairFileAsyncWorker : public Napi::AsyncWorker
{
  public:
    RepairFileAsyncWorker(Napi::Function &callback, Napi::Promise::Deferred deferred, stl_file *stl);
    void Execute();
    void OnOK();
    void OnError(const Napi::Error& e);
    Napi::Value getRepairProperties();
  private:
    Napi::Promise::Deferred deferred;
    stl_file *stl;
};
#endif /* REPAIRFILEASYNCWORKER_H */
