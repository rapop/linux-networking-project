#pragma once

namespace networking {

template <typename CallbackType>
struct ISubscriber
{
  virtual ~ISubscriber() = default;
  virtual void Callback(const CallbackType& data) const = 0;
};

} // namespace networking
