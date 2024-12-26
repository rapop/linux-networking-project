#include <networking/subscriber.h>

#include <chrono>
#include <format>
#include <iostream>

namespace networking {

Subscriber::Subscriber(const std::string subscriber_name) : subscriber_name_(subscriber_name)
{}

void Subscriber::Callback(const std::vector<double>& position) const
{
  const auto now = std::chrono::system_clock::now();
  const std::time_t now_t = std::chrono::system_clock::to_time_t(now);
  const std::tm* now_tm = std::localtime(&now_t);
  const std::string time_str = std::format("{:02}:{:02}:{:02}", 
                                       now_tm->tm_hour, 
                                       now_tm->tm_min, 
                                       now_tm->tm_sec);

  const auto epoch = now.time_since_epoch();
  const auto us = std::chrono::duration_cast<std::chrono::microseconds>(epoch).count() % 1000000;

  std::cout << std::format("Position received for subscriber named {} at system clock time {}{} : ", 
                                subscriber_name_,
                                time_str,
                                us);
  for (const auto& val: position)
  {
    std::cout << val << " ";
  }
  std::cout << std::endl;
}

} // namespace networking