// Copyright (c) 2019 Hawtian.wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace coutel::protocol::lsp {

struct DocumentUri {
  std::optional<DocumentUri> FromString(const std::string& uri);

  const std::string& GetPath() const;

 private:
  DocumentUri() = default;
  std::string path_;
  std::string raw_uri_;
};

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

struct Location {
  DocumentUri uri;
  Range range;
};

struct LocationLink {
  /**
   * Span of the origin of this link.
   *
   * Used as the underlined span for mouse interaction. Defaults to the word
   * range at the mouse position.
   */
  std::optional<Range> originSelectionRange;

  /**
   * The target resource identifier of this link.
   */
  std::string targetUri;

  /**
   * The full target range of this link. If the target for example is a symbol
   * then target range is the range enclosing this symbol not including
   * leading/trailing whitespace but everything else like comments. This
   * information is typically used to highlight the range in the editor.
   */
  Range targetRange;

  /**
   * The range that should be selected and revealed when this link is being
   * followed, e.g the name of a function. Must be contained by the the
   * `targetRange`. See also `DocumentSymbol#range`
   */
  Range targetSelectionRange;
};

enum class DiagnosticSeverity : int32_t {
  /**
   * Reports an error.
   */
  Error = 1,
  /**
   * Reports a warning.
   */
  Warning = 2,
  /**
   * Reports an information.
   */
  Information = 3,
  /**
   * Reports a hint.
   */
  Hint = 4,
};

struct DiagnosticRelatedInformation {
  /**
   * The location of this related diagnostic information.
   */
  Location location;

  /**
   * The message of this related diagnostic information.
   */
  std::string message;
};

struct Diagnostic {
  /**
   * The range at which the message applies.
   */
  Range range;

  /**
   * The diagnostic's severity. Can be omitted. If omitted it is up to the
   * client to interpret diagnostics as error, warning, info or hint.
   */
  int32_t severity;

  /**
   * The diagnostic's code, which might appear in the user interface.
   */
  std::optional<std::variant<int32_t, std::string>> code;

  /**
   * A human-readable string describing the source of this
   * diagnostic, e.g. 'typescript' or 'super lint'.
   */
  std::optional<std::string> source;

  /**
   * The diagnostic's message.
   */
  std::string message;

  /**
   * An array of related diagnostic information, e.g. when symbol-names within
   * a scope collide all definitions can be marked via this property.
   */
  std::optional<std::vector<DiagnosticRelatedInformation>> relatedInformation;
};

inline const std::string& DocumentUri::GetPath() const { return path_; }

}  // namespace coutel::protocol::lsp

