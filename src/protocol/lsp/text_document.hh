// Copyright (c) 2019 Hawtian.Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include "protocol/lsp/basic.hh"
#include "protocol/range.hh"

namespace coutel::protocol::lsp {

struct DidOpenTextDocumentParams {
	/**
	 * The document that was opened.
	 */
  TextDocumentItem textDocument;
}



}  // namespace coutel::protocol::lsp

