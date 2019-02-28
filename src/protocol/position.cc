// Copyright (c) 2019 Hawtian.Wang (twistoy.wang@gmail.com)
//

#include "protocol/position.hh"

#include <cstdio>
#include <optional>
#include <string>

namespace coutel {
namespace protocol {

Position::Position(int32_t line, int32_t column) : line(line), column(column) {}

std::optional<Position> Position::FromString(const std::string &str) {
  int32_t line{-1};
  int32_t column{-1};

  auto ret = sscanf(str.c_str(), "%d:%d", &line, &column);
  if (ret == 2 && line >= 0 && column >= 0) {
    return Position{line, column};
  } else {
    return std::nullopt;
  }
}

}  // namespace protocol
}  // namespace coutel

