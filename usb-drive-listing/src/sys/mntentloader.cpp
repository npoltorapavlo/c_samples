#include "mntentloader.h"

#include <mntent.h>

using namespace std;

namespace {
  MountLoader::MountPtr create(const string& node, const string& path) {
    return std::make_shared<Mount>(node, path);
  }
}

MountLoader::MountPtr MntentLoader::Load(const std::string& node) {
  MountPtr result;

  struct mntent *ent;
  FILE *file = setmntent("/proc/mounts", "r");
  if (file != nullptr) {
    while (nullptr != (ent = getmntent(file))) {
      if (string(ent->mnt_fsname) == node) {
        result = create(ent->mnt_fsname, ent->mnt_dir);
        break;
      }
    }
    endmntent(file);
  }

  return result;
}
