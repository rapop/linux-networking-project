#pragma once

namespace networking {

template <typename MsgType>
class tcp_server
{
  public:
    tcp_server(int port_number);
    MsgType read();
    void tcp_server::connect()

  private:
    int client_socket_file_descriptor_;
    int server_socket_file_descriptor_;
};

} // namespace networking