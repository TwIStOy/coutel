// Copyright (c) 2019 hawtian.wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <optional>

namespace coutel::model {

struct DocumentUri {
  static std::optional<DocumentUri> FromString(const std::string& uri);

  const std::string& GetPath() const;

 private:
  DocumentUri() = default;
  std::string path_;
  std::string raw_uri_;
};

inline const std::string& DocumentUri::GetPath() const { return path_; }

}  // namespace coutel::model

