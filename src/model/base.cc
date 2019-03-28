// Copyright (c) 2019 hawtian.wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include "model/base.hh"

#include <uriparser/Uri.h>

#include <memory>
#include <optional>
#include <vector>

#include "khala/base/string_utility.hh"

namespace coutel::model {

template <typename T>
static std::string FromRange(const T& rg) {
  std::string ret;
  std::copy(rg.first, rg.afterLast, std::back_inserter(ret));
  return ret;
}

struct UriUriStructADeleter {
  void operator()(UriUriStructA* uri) const { uriFreeUriMembersA(uri); };
};

std::optional<DocumentUri> DocumentUri::FromString(const std::string& uri) {
  DocumentUri ret;

  std::unique_ptr<UriUriStructA, UriUriStructADeleter> tmp;
  const char* errorPos;
  if (uriParseSingleUriA(tmp.get(), uri.c_str(), &errorPos) != URI_SUCCESS) {
    return std::nullopt;
  }

  ret.raw_uri_ = uri;
  if (!(tmp->scheme.first)) {
    return std::nullopt;
  }
  std::string scheme = FromRange(tmp->scheme);
  if (scheme != "file") return std::nullopt;

  if (!(tmp->pathHead)) {
    return std::nullopt;
  }

  std::vector<std::string> paths;
  for (UriPathSegmentA* p = tmp->pathHead; p; p = p->next) {
    paths.push_back(FromRange(p->text));
  }

  ret.path_ = khala::base::StringJoin(paths, "/");

  return ret;
}

}  // namespace coutel::model

