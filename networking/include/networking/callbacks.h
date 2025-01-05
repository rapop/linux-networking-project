#pragma once

#include <any>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

namespace callbacks {

inline void double_vector_callback(const std::string& name, const std::any& any_data)
{
  const auto position = std::any_cast<const std::vector<double>&>(any_data);
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
                                name,
                                time_str,
                                us);
  for (const auto& val: position)
  {
    std::cout << val << " ";
  }
  std::cout << std::endl;
};

} // namespace callbacks