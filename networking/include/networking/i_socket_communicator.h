#pragma once

#include <cstdint>
#include <vector>

namespace networking {

struct ISocketCommunicator
{
  virtual ~ISocketCommunicator() = default;
  virtual std::vector<uint8_t> Read(int socket_file_descriptor) const;
  virtual void Write(int socket_file_descriptor, const std::vector<uint8_t>& msg) const;
};

} // namespace networking