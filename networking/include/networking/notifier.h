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
  void NotifySubscribers(const std::vector<double>& position);
  IServer& server_;
  std::unordered_map<std::string, std::reference_wrapper<const ISubscriber>> subscribers_;
};

} // namespace networking
