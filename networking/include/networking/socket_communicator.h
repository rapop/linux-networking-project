#pragma once

#include <networking/i_socket_communicator.h>

namespace networking {

struct SocketCommunicator : public ISocketCommunicator
{
  std::vector<uint8_t> Read(int socket_file_descriptor) const override;
  void Write(int socket_file_descriptor, const std::vector<uint8_t>& msg) const override;
};

} // namespace networking