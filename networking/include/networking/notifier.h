#pragma once

#include <string>
#include <unordered_map>

#include <networking/i_server.h>
#include <networking/i_subscriber.h>

namespace networking {

class Notifier
{
public:
  Notifier(IServer& server);
  void Receive();
  void SendAndStopStream();
  void AddSubscriber(const ISubscriber& subscriber, const std::string& subscriber_name);
private:
  template<typename T>
  void NotifySubscribers(const T& data)
  {
    for (const auto& subscriber : subscribers_)
    {
      if (subscriber.second.get().Type() == typeid(T))
      {
        subscriber.second.get().Callback(data);
      }
    }
  }
  
  IServer& server_;
  std::unordered_map<std::string, std::reference_wrapper<const ISubscriber>> subscribers_;
};

} // namespace networking
