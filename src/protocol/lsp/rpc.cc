// Copyright (c) 2019 Hawtian.Wang (twistoy.wang@gmail.com)
//

#include "protocol/lsp/rpc.hh"

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "khala/base/string_utility.hh"
#include "spdlog/spdlog.h"
#include "uriparser/Uri.h"

namespace coutel {
namespace protocol {
namespace lsp {

RequestId::RequestId(int64_t id) : value(id), tp_(Type::Number) {}

RequestId::RequestId(const std::string& id) : tp_(Type::String) {
  try {
    value = std::stoll(id);
  } catch (...) {
    value = -1;
    tp_ = Type::None;
  }
}

}  // namespace lsp
}  // namespace protocol
}  // namespace coutel
