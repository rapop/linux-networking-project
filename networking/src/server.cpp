#include <networking/server.h>

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "utils.h"

namespace networking {

Server::Server(ISocketCommunicator& socket_communicator) 
: socket_communicator_(socket_communicator)
{}

void Server::BindAndListen(int port_number)
{
  // AF_INET for the internet domain, chosing IPv4 Internet protocols
  // SOCK_STREAM is for the type of socket, tcp in this case
  int binded_socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (binded_socket_file_descriptor < 0)
  {
      exit_with_error({.msg = "ERROR opening socket", .exit_code = 1});
  }

  sockaddr_in server_address;
  // sets all values in a buffer to zero
  bzero((char *)&server_address, sizeof(server_address));

  server_address.sin_family = AF_INET;
  // This field contains the IP address of the host. For server code, 
  // this will always be the IP address of the machine on which the server is running, 
  // and there is a symbolic constant INADDR_ANY which gets this address.
  server_address.sin_addr.s_addr = INADDR_ANY;
  // It's necessary to convert the port number to network byte order.
  server_address.sin_port = htons(port_number);

  // Binds a socket to an address
  if (bind(binded_socket_file_descriptor, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
      exit_with_error({.msg = "ERROR on binding", .exit_code = 1});
  }

  // The listen system call allows the process to listen on the socket for connections.
  // The second argument is  size of the backlog queue, i.e., the number of connections 
  // that can be waiting while the process is handling a particular connection. 
  // This should be set to 5, the maximum size permitted by most systems.
  listen(binded_socket_file_descriptor, 5);

  sockaddr_in client_address;
  socklen_t client_address_length = sizeof(client_address);

  printf("Waiting for connections...\n");

  // The accept() system call causes the process to block until a client connects to the server. 
  // Thus, it wakes up the process when a connection from a client has been successfully established. 
  // It returns a new file descriptor, and all communication on this connection should be done using 
  // the new file descriptor.
  socket_file_descriptor_ = accept(binded_socket_file_descriptor, (struct sockaddr *)&client_address, 
                                      &client_address_length);
  
  if (socket_file_descriptor_ < 0)
  {
      exit_with_error({.msg = "ERROR on accept", .exit_code = 1});
  }
}

std::vector<uint8_t> Server::Read() const
{
  if (socket_file_descriptor_ == -1)
  {
    throw std::runtime_error("Socket has not been setup for reading yet.");
 }
  
  return socket_communicator_.Read(socket_file_descriptor_);
}

void Server::Write(const std::vector<uint8_t>& packet) const
{
  if (socket_file_descriptor_ == -1)
  {
    throw std::runtime_error("Socket has not been setup for writing yet.");
  }

  socket_communicator_.Write(socket_file_descriptor_, packet);
}

} // namespace networking