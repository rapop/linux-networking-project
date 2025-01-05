#include <networking/publisher.h>

#include <iostream>

#include "cmd_types.h"
#include "serializer/types.h"
#include <serializer/serializer.h>

namespace networking {

Publisher::Publisher(IClient& client) : client_(client)
{}

void Publisher::SendPositionCommand(const std::vector<double>& position)
{
  client_.Write(serializer::packVector<serializer::MsgTypes::PositionCommandMsg>(position));
}

void Publisher::SendStopSubscriber(const std::string& subscriber_name)
{
  const std::vector<char> subscriber_name_c_str(subscriber_name.begin(), subscriber_name.end());
  client_.Write(serializer::packVector<serializer::MsgTypes::StopSubscriberMsg>(subscriber_name_c_str));
}

bool Publisher::StopPositionStream()
{
  const auto packet = client_.Read();
  if (serializer::unpackType(packet) == serializer::MsgTypes::CharType &&
      serializer::unpack<serializer::MsgTypes::CharType>(packet) == static_cast<char>(CmdTypes::StopPositionStream)) 
  {
    std::cout << "Received request to stop position stream." << std::endl;
    return true;
  }

  return false;
}

} // namespace networking