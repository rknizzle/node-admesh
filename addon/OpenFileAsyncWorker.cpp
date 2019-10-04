#include "OpenFileAsyncWorker.h"

OpenFileAsyncWorker::OpenFileAsyncWorker(Napi::Function &callback, Napi::Promise::Deferred deferred, stl_file *stl, std::string infileName)
  : Napi::AsyncWorker(callback), deferred(deferred), stl(stl), infileName(infileName)
{
}

void OpenFileAsyncWorker::Execute() {
  // convert std::string infileName to char* for admesh compatibility
  std::vector<char> chars(infileName.begin(), infileName.end());
  chars.push_back('\0');
  char *infile = &chars[0];
  // open and read in the stl file
  stl_open(stl, infile);

  if (stl->error) {
    // return rejected promise
    SetError(stl->error_msg);
  }
}

void OpenFileAsyncWorker::OnError(const Napi::Error& e) {
  Napi::HandleScope scope(Env());
  // reject promise with error value
  deferred.Reject(e.Value());

  // Call empty function
  Callback().Call({});
}

void OpenFileAsyncWorker::OnOK() {
  Napi::HandleScope scope(Env());
  // value to return
  deferred.Resolve(Napi::Boolean::New(Env(), true));

  // Call empty function
  Callback().Call({});
}
