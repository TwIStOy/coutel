// Copyright (c) 2019 Hawtian.Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <khala/base/reflection.hh>

#include <cstdint>
#include <optional>
#include <string>

namespace coutel::lsp {

struct Position {
  /**
   * Line position in a document (zero-based).
   */
  int32_t line;

  /**
   * Character offset on a line in a document (zero-based). Assuming that the
   * line is represented as a string, the `character` value represents the gap
   * between the `character` and `character + 1`.
   *
   * If the character value is greater than the line length it defaults back to
   * the line length.
   */
  int32_t character;
};
REFLECTION(Position, line, column);

struct Range {
  /**
   * The range's start position.
   */
  Position start;

  /**
   * The range's end position.
   */
  Position end;
};
REFLECTION(Range, start, end);

using DocumentUri = std::string;

struct Location {
  DocumentUri uri;
  Range range;
};
REFLECTION(Location, uri, range);

struct TextDocumentItem {
  /**
   * The text document's URI.
   */
  DocumentUri uri;

  /**
   * The text document's language identifier.
   */
  std::string languageId;

  /**
   * The version number of this document (it will increase after each
   * change, including undo/redo).
   */
  int64_t version;

  /**
   * The content of the opened text document.
   */
  std::string text;
};

template <typename ParamsType>
struct NotificationMessage {
  /**
   * The method to be invoked.
   */
  static std::string method;

  /**
   * The notification's params.
   */
  ParamsType params;
};

}  // namespace coutel::lsp

