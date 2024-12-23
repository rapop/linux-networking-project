#pragma once

#include <string>
#include <vector>

namespace networking {
  
struct IPublisher
{
  virtual ~IPublisher() = default;
  virtual void SendPositionCommand(const std::vector<double>& position);
  virtual void SendStopSubscriber(const std::string& subscriber_name);
  virtual bool StopPositionStream();
};

} // namespace networking