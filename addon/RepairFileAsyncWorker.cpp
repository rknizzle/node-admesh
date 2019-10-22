#include "RepairFileAsyncWorker.h"

RepairFileAsyncWorker::RepairFileAsyncWorker(Napi::Function &callback, Napi::Promise::Deferred deferred, stl_file *stl)
  : Napi::AsyncWorker(callback), deferred(deferred), stl(stl)
{
}

void RepairFileAsyncWorker::Execute() {
  float    tolerance = 0;
  float    increment = 0;
  int      fixall_flag = 1;	       /* Default behavior is to fix all. */
  int      exact_flag = 0;	       /* All checks turned off by default. */
  int      tolerance_flag = 0;	       /* Is tolerance specified on cmdline */
  int      nearby_flag = 0;
  int      remove_unconnected_flag = 0;
  int      fill_holes_flag = 0;
  int      normal_directions_flag = 0;
  int      normal_values_flag = 0;
  int      reverse_all_flag = 0;
  int      iterations = 2;	       /* Default number of iterations. */
  int      increment_flag = 0;

  // call function to repair mesh data with default values
  stl_repair(stl, fixall_flag,
           exact_flag,
           tolerance_flag,
           tolerance,
           increment_flag,
           increment,
           nearby_flag,
           iterations,
           remove_unconnected_flag,
           fill_holes_flag,
           normal_directions_flag,
           normal_values_flag,
           reverse_all_flag,
           1);

  if (stl->error) {
    std::string error_msg = "Error repairing mesh data";
    // return rejected promise
    SetError(error_msg);
  }
}

void RepairFileAsyncWorker::OnError(const Napi::Error& e) {
  Napi::HandleScope scope(Env());
  // reject promise with error value
  deferred.Reject(e.Value());

  // Call empty function
  Callback().Call({});
}

void RepairFileAsyncWorker::OnOK() {
  Napi::HandleScope scope(Env());
  // value to return
  deferred.Resolve(getRepairProperties());

  // Call empty function
  Callback().Call({});
}

Napi::Value RepairFileAsyncWorker::getRepairProperties() {
  Napi::Object props = Napi::Object::New(Env());
  props.Set("numberOfParts", stl->stats.number_of_parts);
  props.Set("facetsAdded", stl->stats.facets_added);
  props.Set("facetsRemoved", stl->stats.facets_removed);
  props.Set("degenerateFacets", stl->stats.degenerate_facets);
  props.Set("edgesFixed", stl->stats.edges_fixed);
  props.Set("facetsReversed", stl->stats.facets_reversed);
  props.Set("backwardsEdges", stl->stats.backwards_edges);
  props.Set("normalsFixed", stl->stats.normals_fixed);
  return props;
}
