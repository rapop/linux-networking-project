#include <networking/publisher.h>

#include "cmd_types.h"
#include <serializer/serializer.h>

namespace networking {

Publisher::Publisher(IClient& client) : client_(client)
{}

void Publisher::SendPositionCommand(const std::vector<double>& position)
{
  client_.Write(serializer::packVector<double>(position));
}

void Publisher::SendStopSubscriber(const std::string& subscriber_name)
{
  const std::vector<char> subscriber_name_c_str(subscriber_name.begin(), subscriber_name.end());
  client_.Write(serializer::packVector<char>(subscriber_name_c_str));
}

bool Publisher::StopPositionStream()
{
  const auto packet = client_.Read();
  if (serializer::unpackType(packet) == serializer::MsgType::CharType &&
      serializer::unpack<char>(packet) == static_cast<char>(CmdTypes::StopPositionStream)) 
  {
    return true;
  }

  return false;
}

} // namespace networking