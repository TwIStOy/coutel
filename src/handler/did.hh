// Copyright (c) 2019 hawtian.wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include "lsp/text_document.hh"
#include "model/base.hh"
#include "driver/source_file.hh"

namespace coutel::handler {

struct DisOpenHandler {
  void OnMessage(lsp::DidOpenNotificationMessage& message);
};

void DisOpenHandler::OnMessage(lsp::DidOpenNotificationMessage& message) {
  std::string path;
  {
    auto uri_opt = model::DocumentUri::FromString(message.params.textDocument.uri);
    if (!uri_opt.has_value()) {
      // TODO(hawtian): error response
    }
    path = uri_opt.value().GetPath();
  }

  auto source_file = driver::SourceFile::FindOrCreate(path);

  // TODO(hawtian): send highlight
}



}  // namespace coutel::handler

