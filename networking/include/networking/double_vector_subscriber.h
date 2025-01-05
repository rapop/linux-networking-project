#pragma once

#include <string>
#include <vector>

#include <networking/i_subscriber.h>

namespace networking {

class DoubleVectorSubscriber : public ISubscriber<std::vector<double>>
{
public:
  DoubleVectorSubscriber(const std::string subscriber_name);
  void Callback(const std::vector<double>& position) const override;
private:
  const std::string subscriber_name_;
};

} // namespace networking