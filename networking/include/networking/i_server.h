#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace networking {

struct IServer
{
  virtual ~IServer() = default;
  virtual void BindAndListen(int port_number);
  virtual std::vector<uint8_t> Read() const;
  virtual void Write(const std::vector<uint8_t>& msg) const;
};

} // namespace networking