// Copyright (c) 2019 hawtian.wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <functional>
#include <unordered_map>

#include "khala/base/emitter.hh"
#include "third_party/fmt/format.h"

#include "protocol/lsp/lsp.hh"
#include "receiver/receiver.hh"

namespace coutel {

using nlohmann::json;
using fmt::operator"" _format;

class MessageCenter final : public khala::base::Emitter<MessageCenter> {
 public:
  using MessageHandler = std::function<void(protocol::lsp::RequestMessage&)>;

  void RegisterMessageHandler(const std::string& method,
                              MessageHandler handler);

 private:
  template<typename T>
  void OnClientRequest(protocol::lsp::RequestMessage& event, T&);

  template<typename T>
  void SendResponse(const T& response);

 private:
  std::unordered_map<std::string, MessageHandler> message_handlers_;
};

inline void MessageCenter::RegisterMessageHandler(const std::string& method,
                                                  MessageHandler handler) {
  message_handlers_.emplace(method, std::move(handler));
}

template<typename T>
void MessageCenter::OnClientRequest(protocol::lsp::RequestMessage& msg, T&) {
  if (!msg.id.IsValid()) {
    // TODO(hawtian): impl
    return;
  }
  auto it = message_handlers_.find(msg.method);
  if (it == message_handlers_.end()) {
    protocol::lsp::ResponseError response;
    response.code = protocol::lsp::ErrorCode::InvalidRequest;
    response.message = "unknown request method: {}"_format(msg.method);

    SendResponse(response);
    return;
  }

  (it->second)(msg);
}

}  // namespace coutel

