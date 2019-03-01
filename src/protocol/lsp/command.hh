// Copyright (c) 2019 Hawtian.wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "protocol/lsp/basic.hh"
#include "third_party/json.hpp"

namespace coutel::protocol::lsp {

using nlohmann::json;

struct Command {
  /**
   * Title of the command, like `save`.
   */
  std::string title;
  /**
   * The identifier of the actual command handler.
   */
  std::string command;
  /**
   * Arguments that the command handler should be
   * invoked with.
   * arguments ?: any[];
   */
  std::optional<std::vector<json>> arguments;
};

/**
 * Options to create a file.
 */
struct CreateFileOptions {
  /**
   * Overwrite existing file. Overwrite wins over `ignoreIfExists`
   */
  std::optional<bool> overwrite;
  /**
   * Ignore if exists.
   */
  std::optional<bool> ignoreIfExists;
};

/**
 * Create file operation
 */
struct CreateFile {
  /**
   * A create
   */
  std::string kind = "create";
  /**
   * The resource to create.
   */
  std::string uri;
  /**
   * Additional options
   */
  std::optional<CreateFileOptions> options;
};

/**
 * Rename file options
 */
struct RenameFileOptions {
  /**
   * Overwrite target if existing. Overwrite wins over `ignoreIfExists`
   */
  std::optional<bool> overwrite;
  /**
   * Ignores if target exists.
   */
  std::optional<bool> ignoreIfExists;
};

/**
 * Rename file operation
 */
struct RenameFile {
  /**
   * A rename
   */
  std::string kin = "rename";
  /**
   * The old (existing) location.
   */
  std::string oldUri;
  /**
   * The new location.
   */
  std::string newUri;
  /**
   * Rename options.
   */
  std::optional<RenameFileOptions> options;
};

/**
 * Delete file options
 */
struct DeleteFileOptions {
  /**
   * Delete the content recursively if a folder is denoted.
   */
  std::optional<bool> recursive;
  /**
   * Ignore the operation if the file doesn't exist.
   */
  std::optional<bool> ignoreIfNotExists;
};

/**
 * Delete file operation
 */
struct DeleteFile {
  /**
   * A delete
   */
  std::string kind = "delete";
  /**
   * The file to delete.
   */
  std::string uri;
  /**
   * Delete options.
   */
  std::optional<DeleteFileOptions> options;
};

struct TextEdit {
  /**
   * The range of the text document to be manipulated. To insert
   * text into a document create a range where start === end.
   */
  Range range;

  /**
   * The string to be inserted. For delete operations use an
   * empty string.
   */
  std::string newText;
};

struct TextDocumentIdentifier {
  DocumentUri uri;
};

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

struct VersionedTextDocumentIdentifier : TextDocumentIdentifier {
  /**
   * The version number of this document. If a versioned text document
   * identifier is sent from the server to the client and the file is not open
   * in the editor (the server has not received an open notification before) the
   * server can send `null` to indicate that the version is known and the
   * content on disk is the truth (as speced with document content ownership).
   *
   * The version number of a document will increase after each change, including
   * undo/redo. The number doesn't need to be consecutive.
   */
  std::variant<int64_t, std::nullopt_t> version;
};

struct TextDocumentEdit {
  /**
   * The text document to change.
   */
  VersionedTextDocumentIdentifier textDocument;

  /**
   * The edits to be applied.
   */
  std::vector<TextEdit> edits;
};

struct WorkspaceEdit {
  /**
   * Holds changes to existing resources.
   */
  std::optional<std::unordered_map<std::string, std::vector<TextEdit>>> changes;

  /**
   * Depending on the client capability
   * `workspace.workspaceEdit.resourceOperations` document changes are either an
   * array of `TextDocumentEdit`s to express changes to n different text
   * documents where each text document edit addresses a specific version of a
   * text document. Or it can contain above `TextDocumentEdit`s mixed with
   * create, rename and delete file / folder operations.
   *
   * Whether a client supports versioned document edits is expressed via
   * `workspace.workspaceEdit.documentChanges` client capability.
   *
   * If a client neither supports `documentChanges` nor
   * `workspace.workspaceEdit.resourceOperations` then only plain `TextEdit`s
   * using the `changes` property are supported.
   */
  using ChangesTypeInner =
      std::variant<TextDocumentEdit, CreateFile, RenameFile, DeleteFile>;
  using ChangesType = std::variant<std::vector<TextDocumentEdit>,
                                   std::vector<ChangesTypeInner>>;
  std::optional<ChangesType> documentChanges;
};

}  // namespace coutel::protocol::lsp

