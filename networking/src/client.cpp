#include <networking/client.h>

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "utils.h"

namespace networking {

void Client::Connect(const std::string& address, int port_number)
{
  // a file descriptor is a process-unique identifier/handle for a file or 
  // in this case another io resource that is a network socket
  socket_file_descriptor_ = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_file_descriptor_ < 0) {
      exit_with_error({.msg = "ERROR opening socket", .exit_code = 1});
  }

  // contains the name of a host on the Internet, e.g. cs.rpi.edu.
  struct hostent* server = gethostbyname(address.c_str());
  if (server == NULL) {
      exit_with_error({.msg = ("ERROR, no such host: " + address).c_str(), .exit_code = 1});
  }

  struct sockaddr_in server_address;
  bzero((char *) &server_address, sizeof(server_address));
  server_address.sin_family = AF_INET;
  // Same as in the server. However, because the field server->h_addr is a character string, 
  // we use the function. 
  bcopy((char *)server->h_addr, 
        (char *)&server_address.sin_addr.s_addr,
        server->h_length);
  server_address.sin_port = htons(port_number);
  
  if (connect(socket_file_descriptor_,(struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
      exit_with_error({.msg = "ERROR connecting", .exit_code = 1});
  }

  // printf("Please enter the message: ");
}

std::vector<uint8_t> Client::Read() const
{
  if (socket_file_descriptor_ == -1)
  {
    throw std::runtime_error("Socket has not been setup for reading yet.");
  }
  
  return socket_communicator_.Read(socket_file_descriptor_);
}

void Client::Write(const std::vector<uint8_t>& packet) const
{
  if (socket_file_descriptor_ == -1)
  {
    throw std::runtime_error("Socket has not been setup for writing yet.");
  }

  socket_communicator_.Write(socket_file_descriptor_, packet);
}

} // namespace networking