// Copyright (c) 2019 hawtian.wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <memory>
#include <unordered_map>
#include <string>

#include "khala/base/emitter.hh"

#include "driver/source_file.hh"

namespace coutel::driver {

class Project : std::enable_shared_from_this<Project> {
 public:
  Project(std::string root);

  // Load a project in the given folder.
  void Load();

  const std::string& GetRoot() const;

 private:
  const std::string project_root_;
};

inline const std::string& Project::GetRoot() const { return project_root_; }

}  // namespace coutel::driver

