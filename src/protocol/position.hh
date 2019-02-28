// Copyright (c) 2019 Hawtian.Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

namespace coutel {
namespace protocol {

class Position {
 public:
  static Position FromString(const std::string& str);

  Position() = default;
  Position(int32_t line, uint32_t column);

  bool IsValid() const;
  std::string Repr() const;

  friend bool operator==(const Position& lhs, const Position& rhs);
  friend bool operator<(const Position& lhs, const Position& rhs);

 private:
  int32_t line_{-1};
  int32_t column_{-1};
};

Position::Position(int32_t line, uint32_t column)
    : line_(line), column_(column) {}

inline bool Position::IsValid() const { return line_ >= 0; }

inline bool operator==(const Position& lhs, const Position& rhs) {
  return lhs.line_ == rhs.line_ && lhs.column_ == rhs.column_;
}

inline bool operator<(const Position& lhs, const Position& rhs) {
  return lhs.line_ == rhs.line_ ? lhs.column_ < rhs.column_
                                : lhs.line_ < rhs.line_;
}

inline bool operator<=(const Position& lhs, const Position& rhs) {
  return !(rhs < lhs);
}

inline std::string Position::Repr() const {
  std::ostringstream os;
  os << line_ << ":" << column_;
  return os.str();
}

}  // namespace protocol
}  // namespace coutel

