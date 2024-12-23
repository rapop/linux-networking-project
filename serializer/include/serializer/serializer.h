#pragma once

#include <cstdint>
#include <cstring>
#include <vector>
#include <stdexcept>
#include <string>

#include <serializer/types.h>

namespace serializer {

// packet = data type code + length + msg
template <typename DataType>
std::vector<uint8_t> pack(const DataType& data)
{
  std::vector<uint8_t> buffer;
  buffer.resize(2 + sizeof(DataType));

  const uint8_t int_type_code = static_cast<uint8_t>(ToMsgType<DataType>);

  std::memcpy(buffer.data(), &int_type_code, sizeof(int_type_code));
  std::size_t offset = sizeof(int_type_code);

  const uint8_t message_length = sizeof(DataType);

  std::memcpy(buffer.data() + offset, &message_length, sizeof(message_length));
  offset += sizeof(message_length);

  std::memcpy(buffer.data() + offset, &data, sizeof(DataType));

  return buffer;
}

MsgType unpackType(const std::vector<uint8_t>& packet)
{
  if (packet.empty()) 
  {
    throw std::invalid_argument("Cannot unpack type of empty packet.");
  }
  return static_cast<MsgType>(packet[0]);
}

template <typename DataType>
DataType unpack(const std::vector<uint8_t>& packet)
{
  MsgType msg_type = unpackType(packet);
  if (ToMsgType<DataType> != msg_type)
  {
    throw std::runtime_error("Trying to unpack packet to wrong type.");
  }
  
  uint8_t message_length;
  // skipping the first bit which is the msg type.
  std::size_t offset = 1; 
  std::memcpy(&message_length, packet.data() + offset, sizeof(message_length));
  offset += sizeof(message_length);

  DataType data;
  // we don't really need the message length if we know the type?
  std::memcpy(&data, packet.data() + offset, message_length);

  return data;
}

template <typename DataType>
std::vector<uint8_t> packVector(const std::vector<DataType>& data)
{
  const uint8_t message_length = sizeof(DataType)*data.size();

  std::vector<uint8_t> buffer;
  buffer.resize(2 + message_length);
    
  const uint8_t int_type_code = static_cast<uint8_t>(ToMsgType<DataType>);
  std::memcpy(buffer.data(), &int_type_code, sizeof(int_type_code));

  std::size_t offset = sizeof(int_type_code);

  std::memcpy(buffer.data() + offset, &message_length, sizeof(message_length));
  offset += sizeof(message_length);

  std::memcpy(buffer.data() + offset, data.data(), message_length);

  return buffer;
}

template <typename DataType>
std::vector<DataType> unpackVector(const std::vector<uint8_t>& packet)
{
  MsgType msg_type = unpackType(packet);
  if (ToMsgType<DataType> != msg_type)
  {
    throw std::runtime_error("Trying to unpack packet to wrong type.");
  }

  uint8_t message_length;
  // skipping the first bit which is the msg type.
  std::size_t offset = 1; 
  std::memcpy(&message_length, packet.data() + offset, sizeof(message_length));
  offset += sizeof(message_length);

  std::vector<DataType> data;
  const std::size_t nb_element = message_length/sizeof(DataType);
  data.resize(nb_element);

  std::memcpy(data.data(), packet.data() + offset, message_length);
  return data;
}

} // namespace serializer