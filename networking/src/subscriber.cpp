#include <networking/subscriber.h>

#include <format>
#include <iostream>

namespace networking {

Subscriber::Subscriber(const std::string subscriber_name) : subscriber_name_(subscriber_name)
{}

void Subscriber::Callback(const std::vector<double>& position) const
{
  std::cout << std::format("Position received for subscriber named {}", subscriber_name_);
  for (const auto& val: position)
  {
    std::cout << val;
  }
  std::cout << std::endl;
}

} // namespace networking