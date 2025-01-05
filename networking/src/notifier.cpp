#include <networking/notifier.h>

#include <format>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "cmd_types.h"
#include <serializer/serializer.h>

namespace networking
{

Notifier::Notifier(IServer &server) : server_(server)
{}

void Notifier::Receive()
{
  const auto packet = server_.Read();
  const serializer::MsgType packet_type = serializer::unpackType(packet);

  if (packet_type == serializer::MsgType::CharVectorType)
  {
    const std::vector<char> subscriber_name = serializer::unpackVector<char>(packet);
    const std::string subscriber_name_str(subscriber_name.begin(), subscriber_name.end());

    auto subscriber_it = subscribers_.find(subscriber_name_str);
    if (subscriber_it != subscribers_.end())
    {
      std::cout << std::format("Received request to unsubscribe subscriber with name {}", 
                                subscriber_name_str) << std::endl;
      subscribers_.erase(subscriber_it);
    }
    else
    {
      throw std::runtime_error(std::format("Cannot remove subscriber with name {}", subscriber_name_str));
    }
  }
  else if (packet_type == serializer::MsgType::DoubleVectorType)
  {
    const std::vector<double> position = serializer::unpackVector<double>(packet);
    NotifySubscribers<std::vector<double>>(position);
  }
  else
  {
    throw std::runtime_error("Notifier received unknown packet.");
  }
}

void Notifier::SendAndStopStream()
{
  server_.Write(serializer::pack<char>(static_cast<char>(CmdTypes::StopPositionStream)));
}

// void Notifier::NotifySubscribers(const std::vector<double>& position)
// {
//   for (const auto& subscriber : subscribers_) 
//   {
//     subscriber.second.get().Callback(position);
//   }
// }

// void Notifier::NotifySubscribers(const std::vector<double>& position)
// {
//   for (const auto& [name, sub] : subscribers_)
//   {
//     std::visit([&position](const auto& subscriber)
//                 {
//                   using T = std::decay_t<decltype(subscriber.get())>;
//                   if constexpr (std::is_same_v<T, ISubscriber<std::vector<double>>>)
//                   {
//                     subscriber->Callback(position);
//                   }
//                 }, sub);
//   }
// }

// void Notifier::AddSubscriber(const ISubscriber& subscriber, const std::string& subscriber_name)
// {
//   subscribers_.emplace(subscriber_name, std::ref(subscriber));
// }

} // namespace networking