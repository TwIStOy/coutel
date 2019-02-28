// Copyright (c) 2019 Hawtian.Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <optional>
#include <string>

#include "protocol/position.hh"

namespace coutel {
namespace protocol {

struct Range {
  Position start;
  Position end;

  Range() = default;
  Range(Position st, Position ed);

  static std::optional<Range> FromString(const std::string& str);
  std::string Repr() const;

  bool IsValid() const;
  bool Contains(const Position& pos) const;
  bool Contains(int32_t line, int32_t column) const;
};

REFLECTION(Range, start, end);

}  // namespace protocol
}  // namespace coutel

