#pragma once

#include <networking/i_server.h>
#include <networking/i_socket_communicator.h>

namespace networking {

class Server : public IServer
{
public:
  Server(ISocketCommunicator& socket_communicator);
  void BindAndListen(int port_number) override;
  std::vector<uint8_t> Read() const override;
  void Write(const std::vector<uint8_t>& packet) const override;
private:
  ISocketCommunicator& socket_communicator_;
  int socket_file_descriptor_ = -1;
};

} // namespace networking