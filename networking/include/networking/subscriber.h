#pragma once

#include <functional>
#include <string>
#include <vector>

#include <networking/i_subscriber.h>

namespace networking {

template <typename T>
class Subscriber : public ISubscriber
{
public:
  Subscriber(const std::string subscriber_name,  std::function<void(const std::string& name, const std::any&)> callback)
  : subscriber_name_(subscriber_name),
    callback_(std::move(callback))
  {}

  void Callback(const std::any& data) const override
  {
    callback_(subscriber_name_, data);
  }
  std::type_index Type() const override 
  {
    return typeid(T);
  }
private:
  const std::string subscriber_name_;
  std::function<void(const std::string& name, const std::any&)> callback_;
};

} // namespace networking