#include "processinfo.h"

#include <core/core.h>

using namespace WPEFramework;

void ProcessInfo::PrintInfo() {
  const Core::WorkerPool::Metadata& snapshot = Core::WorkerPool::Instance().Snapshot();
  printf("Snapshot, pending=%d, occupation=%d, slots=%d\n", snapshot.Pending, snapshot.Occupation, snapshot.Slots);
}
