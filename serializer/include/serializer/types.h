#pragma once

#include <vector>

namespace serializer {

enum class MsgTypes
{
  DoubleType = 0,
  CharType,
  DoubleVectorType,
  CharVectorType,
  PositionCommandMsg,
  StopSubscriberMsg,
};

/*
  These templates allow association between the enum MsgType and the type like a map.
  For example,
  double my_var = MsgTypeTrait<DoubleType>;
  DoubleType my_var = ToMsgType<double>;
*/
 
template<MsgTypes T>
struct MsgTypeTraits; 

template<>
struct MsgTypeTraits<MsgTypes::DoubleType> 
{
    using type = double;
    static constexpr char type_code = static_cast<char>(MsgTypes::DoubleType);
};

template<>
struct MsgTypeTraits<MsgTypes::CharType> 
{
    using type = char;
    static constexpr char type_code = static_cast<char>(MsgTypes::CharType);
};

template<>
struct MsgTypeTraits<MsgTypes::DoubleVectorType> 
{
    using type = double;
    static constexpr char type_code = static_cast<char>(MsgTypes::DoubleVectorType);
};

template<>
struct MsgTypeTraits<MsgTypes::CharVectorType> 
{
    using type = char;
    static constexpr char type_code = static_cast<char>(MsgTypes::CharVectorType);
};

template<>
struct MsgTypeTraits<MsgTypes::PositionCommandMsg> 
{
    using type = double;
    static constexpr char type_code = static_cast<char>(MsgTypes::PositionCommandMsg);
};

template<>
struct MsgTypeTraits<MsgTypes::StopSubscriberMsg> 
{
    using type = char;
    static constexpr char type_code = static_cast<char>(MsgTypes::StopSubscriberMsg);
};

template<MsgTypes T>
using MsgTypeTrait = typename MsgTypeTraits<T>::type;

template<MsgTypes T>
constexpr char ToMsgTypeCode = MsgTypeTraits<T>::type_code;

// this feature doesn't work anymore if we want to support multiple type of msgs for
// the same type

// template<typename T>
// struct MsgTypeEnumTraits;

// template<>
// struct MsgTypeEnumTraits<double> 
// {
//     static constexpr MsgTypes value = MsgTypes::DoubleType;
// };

// template<>
// struct MsgTypeEnumTraits<char> 
// {
//     static constexpr MsgTypes value = MsgTypes::CharType;
// };

// template<>
// struct MsgTypeEnumTraits<std::vector<double>> 
// {
//     static constexpr MsgTypes value = MsgTypes::DoubleVectorType;
// };

// template<>
// struct MsgTypeEnumTraits<std::vector<char>> 
// {
//     static constexpr MsgTypes value = MsgTypes::CharVectorType;
// };

// template<typename T>
// constexpr MsgTypes ToMsgType = MsgTypeEnumTraits<T>::value;

} // namespace serializer