#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

#include <networking/client.h>
#include <networking/publisher.h>
#include <networking/socket_communicator.h>
#include <networking/subscriber.h>

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "[Usage] publisher-app <address> <remote_port>" << std::endl;
    return 1;
  }

  // from cpp reference:
  // If argv[0] is not a null pointer (or, equivalently, if argc > 0), 
  // it points to a string that represents the name used to invoke the program, or to an empty string. 
  const std::string address(argv[1]);
  const int port_number = std::atoi(argv[2]);

  networking::SocketCommunicator socket_communicator;
  networking::Client client(socket_communicator);

  client.Connect(address, port_number);

  networking::Publisher publisher(client);

  std::thread cli_thread([&publisher](){
    while (true)
    {
      std::string input = "";
      std::getline(std::cin, input);
      if (input == "stop")
      {
        std::cout << "Enter subscriber name:" << std::endl;
        std::string subscriber_name = "";
        std::getline(std::cin, subscriber_name);
        publisher.SendStopSubscriber(subscriber_name);
      }
    }
  });
  cli_thread.detach();

  std::atomic<bool> run_position_stream(true);

  std::thread publisher_send_positions_thread([&publisher, &run_position_stream](){
      while (run_position_stream.load())
      {
        publisher.SendPositionCommand({1.1,1.2});
        std::this_thread::sleep_for(100ms);
      }
  });

  publisher_send_positions_thread.detach();

  std::thread stop_position_stream_thread([&publisher, 
                                            &run_position_stream](){
      if(publisher.StopPositionStream())
      {
        run_position_stream.store(false);
      }
  });

  stop_position_stream_thread.detach();
  
  while (true) 
  {
    std::this_thread::sleep_for(1000ms);
  }

  return 0;
}