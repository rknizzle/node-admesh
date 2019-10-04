#include "WriteFileAsyncWorker.h"

WriteFileAsyncWorker::WriteFileAsyncWorker(Napi::Function &callback, Napi::Promise::Deferred deferred, stl_file *stl, std::string outfileName)
  : Napi::AsyncWorker(callback), deferred(deferred), outfileName(outfileName), stl(stl)
{
}

void WriteFileAsyncWorker::Execute() {
  // convert std::string outfileName to char* for admesh compatibility
  std::vector<char> chars(outfileName.begin(), outfileName.end());
  chars.push_back('\0');
  char *outfile = &chars[0];
  // call function to write mesh data to STL file
  stl_write_binary(stl, outfile, "processed by admesh node-js wrapper");

  if (stl->error) {
    std::string error_msg = "Error writing file " + outfileName;
    // return rejected promise
    SetError(error_msg);
  }
}

void WriteFileAsyncWorker::OnError(const Napi::Error& e) {
  Napi::HandleScope scope(Env());
  // reject promise with error value
  deferred.Reject(e.Value());

  // Call empty function
  Callback().Call({});
}

void WriteFileAsyncWorker::OnOK() {
  Napi::HandleScope scope(Env());
  // value to return
  deferred.Resolve(Napi::Boolean::New(Env(), true));

  // Call empty function
  Callback().Call({});
}
