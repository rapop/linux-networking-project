#include <networking/tcp_server.h>

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <networking/utils.h>

namespace networking {

tcp_server::tcp_server(int port_number)
{
    // AF_INET for the internet domain, chosing IPv4 Internet protocols
    // SOCK_STREAM is for the type of socket, tcp in this case
    int server_socket_file_descriptor_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_file_descriptor_ < 0)
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
    if (bind(server_socket_file_descriptor_, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        exit_with_error({.msg = "ERROR on binding", .exit_code = 1});
    }

   
}

void tcp_server::connect()
{
    // The listen system call allows the process to listen on the socket for connections.
    // The second argument is  size of the backlog queue, i.e., the number of connections 
    // that can be waiting while the process is handling a particular connection. 
    // This should be set to 5, the maximum size permitted by most systems.
    listen(server_socket_file_descriptor_, 5);

    sockaddr_in client_address;
    socklen_t client_address_length = sizeof(client_address);

    printf("Waiting for connections...\n");

    // The accept() system call causes the process to block until a client connects to the server. 
    // Thus, it wakes up the process when a connection from a client has been successfully established. 
    // It returns a new file descriptor, and all communication on this connection should be done using 
    // the new file descriptor.
    client_socket_file_descriptor_ = accept(server_socket_file_descriptor_, (struct sockaddr *)&client_address, 
                                        &client_address_length);
    
    if (client_socket_file_descriptor_ < 0)
    {
        exit_with_error({.msg = "ERROR on accept", .exit_code = 1});
    }
}

template <typename MsgType>
MsgType tcp_server::read()
{
    char buffer[256];
    bzero(buffer, 256);

    printf("Waiting for messages...\n");

    // read() will block until there is something for it to read in the socket 
    // It will read either the total number of characters in the socket or 255, 
    // whichever is less, and return the number of characters read. 
    int n = read(client_socket_file_descriptor_, buffer, 255);

    if (n < 0)
    {
        exit_with_error({.msg = "ERROR reading from socket", .exit_code = 1});
    }
        
    printf("Here is the message: %s\n", buffer);
}

} // namespace networking