// Copyright (c) 2019 Hawtian.wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <string>

namespace coutel {

class Project {
 public:
  Project(std::string root);

 private:
  std::string root_;
};

}  // namespace coutel

