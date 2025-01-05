#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

#include <networking/double_vector_subscriber.h>
#include <networking/i_server.h>
#include <networking/i_subscriber.h>

namespace networking {

class Notifier
{
public:
  Notifier(IServer& server);
  void Receive();
  void SendAndStopStream();
  template <typename T>
  void AddSubscriber(const std::shared_ptr<ISubscriber<T>>& subscriber, const std::string& subscriber_name)
  {
    subscribers_.emplace(subscriber_name, subscriber);
  }
private:
  template <typename CallbackType>
  void NotifySubscribers(const CallbackType& position)
  {
    for (const auto& [name, sub] : subscribers_)
    {
      std::visit([&position](const auto& subscriber)
                  {
                    using T = std::decay_t<decltype(subscriber)>;
                    if constexpr (std::is_same_v<T, std::shared_ptr<ISubscriber<CallbackType>>>)
                    {
                      subscriber->Callback(position);
                    }
                  }, sub);
    }
  }

  IServer& server_;

  // add new variants that we want to support here
  // we cannot use reference_wrapper with variant since variant needs already initialized elements
  // and reference wrapper lacks a default ctor.
  // std::variant is stricly typed. This means that it can hold a value of DoubleVectorSubscriber exactly not to one of it's interface.
  using SubscriberVariant = std::variant<std::shared_ptr<ISubscriber<std::vector<double>>>>;
  std::unordered_map<std::string, SubscriberVariant> subscribers_;
};

} // namespace networking
