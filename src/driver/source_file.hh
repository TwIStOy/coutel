// Copyright (c) 2019 hawtian.wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <memory>
#include <string>

namespace coutel::driver {

class Project;

struct SourceFile : std::enable_shared_from_this<SourceFile> {
  /**
   * Find or create a **SourceFile** object in cached database.
   */
  static SourceFile* FindOrCreate(const std::string& path);

  Project* GetProject() const;

 private:
  Project* project_;
};

inline Project* SourceFile::GetProject() const {
  return project_;
}

}  // namespace coutel::driver

