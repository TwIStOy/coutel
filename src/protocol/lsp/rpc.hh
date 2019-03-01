// Copyright (c) 2019 Hawtian.Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <optional>
#include <string>
#include <variant>

#include "khala/base/reflection.hh"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"

#include "protocol/lsp/error_code.hh"

namespace coutel {
namespace protocol {
namespace lsp {

struct Message {
  std::string jsonrpc;
};

struct RequestId {
  int64_t value;

  enum class Type { None, Number, String };

  bool IsValid() const noexcept;
  RequestId(int64_t id);
  RequestId(const std::string& id);

 private:
  Type tp_{Type::None};
};

struct RequestMessage : Message {
  /**
   * The request id.
   */
  RequestId id;

  /**
   * The method to be invoked.
   */
  std::string method;

  /**
   * The method's params.
   */
  std::optional<rapidjson::Document> params;
};

struct ResponseError {
  ErrorCode code;
  std::string message;
  std::optional<rapidjson::Document> data;
};

struct ResponseMessageSuccess : Message {
  /**
   * The request id.
   */
  RequestId id;

  /**
   * The result of a request. This member is REQUIRED on success.
   * This member MUST NOT exist if there was an error invoking the method.
   */
  std::variant<std::string, int64_t, bool, rapidjson::Document> result;
};

struct ResponseMessageError : Message {
  /**
   * The request id.
   */
  RequestId id;

  /**
   * The error object in case a request fails.
   */
  std::optional<ResponseError> error;
};

struct NotificationMessage {
  /**
   * The method to be invoked.
   */
  std::string method;

  /**
   * The notification's params.
   */
  rapidjson::Document params;
};

struct CancelParams {
  /**
   * The request id to cancel.
   */
  RequestId id;
};

inline bool RequestId::IsValid() const noexcept { return tp_ != Type::None; }

}  // namespace lsp
}  // namespace protocol
}  // namespace coutel

