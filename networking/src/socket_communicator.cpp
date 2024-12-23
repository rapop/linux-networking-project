#include <networking/socket_communicator.h>

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

std::vector<uint8_t> SocketCommunicator::Read(int socket_file_descriptor) const
{
  if (socket_file_descriptor == -1)
  {
    throw std::runtime_error("Socket has not been setup for reading yet.");
  }
  
  // char buffer[256];
  // bzero(buffer, 256);

  std::vector<uint8_t> data;

  //printf("Waiting for messages...\n");

  uint8_t data_type; 

  // read() will block until there is something for it to read in the socket 
  // It will read either the total number of characters in the socket or nbytes(last argument), 
  // whichever is less, and return the number of characters read. 
  // here we read the first byte expected to be the data type
  int type_bytes_read = read(socket_file_descriptor, &data_type, 1);

  if (type_bytes_read < 0)
  {
    exit_with_error({.msg = "ERROR reading message type from socket", .exit_code = 1});
  }

  // read the length of the message that we expect
  uint8_t msg_length;
  int length_bytes_read = read(socket_file_descriptor, &msg_length, 1);

  if (length_bytes_read < 0)
  {
    exit_with_error({.msg = "ERROR reading message length from socket", .exit_code = 1});
  }

  std::vector<uint8_t> packet;
  // the first two bytes are the msg type and the msg length
  packet.resize(2 + msg_length);
  packet[0] = data_type;
  packet[1] = msg_length;

  int total_message_bytes_read = 0;
  std::size_t offset = 2;
  while (total_message_bytes_read < msg_length)
  {
    int message_bytes_read = read(socket_file_descriptor, packet.data() + offset, msg_length);
    total_message_bytes_read += message_bytes_read;
    offset += message_bytes_read;
  }

  return packet;

  //printf("Here is the message: %s\n", buffer);
}

void SocketCommunicator::Write(int socket_file_descriptor, const std::vector<uint8_t>& packet) const
{
  if (socket_file_descriptor == -1)
  {
    throw std::runtime_error("Socket has not been setup for writing yet.");
  }

  // char buffer[256];
  // bzero(buffer,256);
  // fgets(buffer,255, stdin);
  const int total_bytes_to_send = packet.size();
  int total_bytes_sent = 0;
  int nb_bytes_sent = 0;
  while (total_bytes_sent < total_bytes_to_send)
  {
    nb_bytes_sent = write(socket_file_descriptor, packet.data(), packet.size());
    total_bytes_sent += nb_bytes_sent;

    if (nb_bytes_sent < 0)
    {
      exit_with_error({.msg = "ERROR writing to socket", .exit_code = 0});
    }
  }

  // printf("%s\n",buffer);
  // close(socket_file_descriptor_);
}

} // namespace networking