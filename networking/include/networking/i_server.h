#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace networking {

struct IServer
{
  virtual ~IServer() = default;
  virtual void BindAndListen(int port_number) = 0;
  virtual std::vector<uint8_t> Read() const = 0;
  virtual void Write(const std::vector<uint8_t>& msg) const = 0;
};

} // namespace networking