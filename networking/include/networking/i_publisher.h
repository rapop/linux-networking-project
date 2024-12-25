#pragma once

#include <string>
#include <vector>

namespace networking {
  
struct IPublisher
{
  virtual ~IPublisher() = default;
  virtual void SendPositionCommand(const std::vector<double>& position) = 0;
  virtual void SendStopSubscriber(const std::string& subscriber_name) = 0;
  virtual bool StopPositionStream() = 0;
};

} // namespace networking