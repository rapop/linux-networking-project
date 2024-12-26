#include <chrono>
#include <iostream>
#include <thread>

#include <networking/notifier.h>
#include <networking/server.h>
#include <networking/socket_communicator.h>
#include <networking/subscriber.h>

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "[Usage] notifier-app <remote_port>" << std::endl;
    return 1;
  }

  const int port_number = std::atoi(argv[1]);

  networking::SocketCommunicator socket_communicator;
  networking::Server server(socket_communicator);

  server.BindAndListen(port_number);

  networking::Subscriber subscriberA("SubscriberA");
  networking::Subscriber subscriberB("SubscriberB");

  networking::Notifier notifier(server);
  notifier.AddSubscriber(subscriberA, "SubscriberA");
  notifier.AddSubscriber(subscriberB, "SubscriberB");

  std::thread cli_thread([&notifier](){
    std::string input = "";
    std::getline(std::cin, input);
    printf("Received %s", input.c_str());
    if (input == "stop")
    {
      notifier.SendAndStopStream();
    }
  });
  cli_thread.detach();

  std::thread socket_receive_thread([&notifier](){
    while (true)
    {
      notifier.Receive();
    }
  });
  socket_receive_thread.detach();

  while (true) 
  {
    std::this_thread::sleep_for(1000ms);
  }
  
  return 0;
}