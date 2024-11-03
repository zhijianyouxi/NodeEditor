#pragma once

#include <Nodes/utils/api.h>
#include <string>
#include <vector>

namespace NodeEditor {

struct ParamDescriptor {
  std::string type, name, defl, doc;

  NODE_API ParamDescriptor(std::string const &type,
	  std::string const &name, std::string const &defl, std::string const &doc = "");
  NODE_API ~ParamDescriptor();
};

struct SocketDescriptor {
  std::string type, name, defl, doc;

  NODE_API SocketDescriptor(std::string const &type,
	  std::string const &name, std::string const &defl = {}, std::string const &doc = {});
  NODE_API ~SocketDescriptor();

  //[[deprecated("use {\"sockType\", \"sockName\"} instead of \"sockName\"")]]
  SocketDescriptor(const char *name)
      : SocketDescriptor({}, name) {}
};

struct Descriptor {
  std::vector<SocketDescriptor> inputs;
  std::vector<SocketDescriptor> outputs;
  std::vector<ParamDescriptor> params;
  std::vector<std::string> categories;
  std::string doc;

  NODE_API Descriptor();
  NODE_API Descriptor(
	  std::vector<SocketDescriptor> const &inputs,
	  std::vector<SocketDescriptor> const &outputs,
	  std::vector<ParamDescriptor> const &params,
	  std::vector<std::string> const &categories,
      std::string const &doc = "");
};

}
