#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace networking {

struct IClient
{
  virtual ~IClient() = default;
  virtual void Connect(const std::string& address, int port_number);
  virtual std::vector<uint8_t> Read() const;
  virtual void Write(const std::vector<uint8_t>& msg) const;
};

} // namespace networking