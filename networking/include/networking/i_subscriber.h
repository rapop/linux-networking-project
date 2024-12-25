#pragma once

#include <vector>

namespace networking {

struct ISubscriber
{
  virtual ~ISubscriber() = default;
  virtual void Callback(const std::vector<double>& position) const = 0;
};

} // namespace networking
