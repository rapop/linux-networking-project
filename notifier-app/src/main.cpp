#include <iostream>
#include <thread>

#include <networking/notifier.h>
#include <networking/server.h>
#include <networking/socket_communicator.h>
#include <networking/subscriber.h>

int main()
{
  networking::SocketCommunicator socket_communicator;
  networking::Server server(socket_communicator);
  const int port_number = 51715;
  server.BindAndListen(port_number);

  networking::Subscriber subscriberA("SubscriberA");
  networking::Subscriber subscriberB("SubscriberB");

  networking::Notifier notifier(server);
  notifier.AddSubscriber(subscriberA, "SubscriberA");
  notifier.AddSubscriber(subscriberB, "SubscriberB");

  std::thread cli_thread([&notifier](){
    std::string input = "";
    std::getline(std::cin, input);
    if (input == "stop")
    {
      notifier.SendAndStopStream();
    }
  });
  cli_thread.detach();

  std::thread socket_receive_thread([&notifier](){
      notifier.Receive();
  });
  socket_receive_thread.detach();
  
  return 0;
}