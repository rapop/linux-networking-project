#pragma once

#include <string>
#include <vector>

#include <networking/i_client.h>
#include <networking/i_publisher.h>

namespace networking {
  
class Publisher : public IPublisher
{
public:
  Publisher(IClient& client);
  void SendPositionCommand(const std::vector<double>& position) override;
  void SendStopSubscriber(const std::string& subscriber_name) override;
  bool StopPositionStream() override;
private:
  IClient& client_;
};

} // namespace networking