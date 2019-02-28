// Copyright (c) 2019 Hawtian.Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <cstdint>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

#include "khala/base/reflection.hh"

namespace coutel {
namespace protocol {

struct Position {
  int32_t line{-1};
  int32_t column{-1};

  Position() = default;
  Position(int32_t line, int32_t column);

  static std::optional<Position> FromString(const std::string& str);
  std::string Repr() const;

  bool IsValid() const;
};

REFLECTION(Position, line, column);

inline bool Position::IsValid() const { return line >= 0; }

inline bool operator==(const Position& lhs, const Position& rhs) {
  return lhs.line == rhs.line && lhs.column == rhs.column;
}

inline bool operator<(const Position& lhs, const Position& rhs) {
  return lhs.line == rhs.line ? lhs.column < rhs.column : lhs.line < rhs.line;
}

inline bool operator<=(const Position& lhs, const Position& rhs) {
  return !(rhs < lhs);
}

inline std::string Position::Repr() const {
  std::ostringstream os;
  os << line << ":" << column;
  return os.str();
}

}  // namespace protocol
}  // namespace coutel

