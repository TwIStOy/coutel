// Copyright (c) 2019 Hawtian.Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <khala/base/reflection.hh>

#include "lsp/base.hh"

namespace coutel::lsp {

struct DidOpenTextDocumentParams {
  /**
   * The document that was opened.
   */
  TextDocumentItem textDocument;
};
REFLECTION(DidOpenTextDocumentParams, textDocument);

using DidOpenNotificationMessage =
    NotificationMessage<DidOpenTextDocumentParams>;

template <>
std::string DidOpenNotificationMessage::method = "textDocument/didOpen";

}  // namespace coutel::lsp

