// Copyright (c) 2019 Hawtian.Wang (twistoy.wang@gmail.com)
//

#include "protocol/range.hh"

#include <cstdio>

namespace coutel {
namespace protocol {

Range::Range(Position st, Position ed)
    : start(std::move(st)), end(std::move(ed)) {}

std::optional<Range> Range::FromString(const std::string &str) {
  int32_t st_line{-1};
  int32_t st_column{-1};
  int32_t ed_line{-1};
  int32_t ed_column{-1};

  auto ret = sscanf(str.c_str(), "%d:%d-%d:%d", &st_line, &st_column, &ed_line,
                    &ed_column);

  if (ret == 4 && st_line >= 0 && st_column >= 0 && ed_line >= 0 &&
      ed_column >= 0) {
    return Range{Position{st_line, st_column}, Position{ed_line, ed_column}};
  } else {
    return std::nullopt;
  }
}

}  // namespace protocol
}  // namespace coutel

