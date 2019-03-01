// Copyright (c) 2019 hawtian.wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <functional>

#include "khala/base/emitter.hh"

#include "protocol/lsp/lsp.hh"
#include "receiver/receiver.hh"

namespace coutel {

using nlohmann::json;

class MessageCenter final : public khala::base::Emitter<MessageCenter> {
 private:
  template <typename T>
  void OnClientRequest(protocol::lsp::RequestMessage& event, T&);

 private:
};

template <typename T>
void MessageCenter::OnClientRequest(protocol::lsp::RequestMessage& msg, T&) {
  if (!msg.id.IsValid()) {
  }
}

}  // namespace coutel

