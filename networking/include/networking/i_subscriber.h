#pragma once

#include <any>
#include <typeindex>

namespace networking {

struct ISubscriber
{
  virtual ~ISubscriber() = default;
  virtual void Callback(const std::any& data) const = 0;
  virtual std::type_index Type() const = 0;
};

} // namespace networking
