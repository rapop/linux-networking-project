#pragma once

namespace serializer {

enum class MsgType 
{
  DoubleType = 0,
  CharType,
  DoubleVectorType,
  CharVectorType,
};

/*
  These templates allow association between the enum MsgType and the type like a map.
  For example,
  double my_var = MsgTypeTrait<DoubleType>;
  DoubleType my_var = ToMsgType<double>;
*/
 
template<MsgType T>
struct MsgTypeTraits; 

template<typename T>
struct MsgTypeEnumTraits;

template<>
struct MsgTypeTraits<MsgType::DoubleType> 
{
    using type = double;
};

template<>
struct MsgTypeTraits<MsgType::CharType> 
{
    using type = char;
};

template<>
struct MsgTypeTraits<MsgType::DoubleVectorType> 
{
    using type = std::vector<double>;
};

template<>
struct MsgTypeTraits<MsgType::CharVectorType> 
{
    using type = std::vector<char>;
};

template<>
struct MsgTypeEnumTraits<double> 
{
    static constexpr MsgType value = MsgType::DoubleType;
};

template<>
struct MsgTypeEnumTraits<char> 
{
    static constexpr MsgType value = MsgType::CharType;
};

template<>
struct MsgTypeEnumTraits<std::vector<double>> 
{
    static constexpr MsgType value = MsgType::DoubleVectorType;
};

template<>
struct MsgTypeEnumTraits<std::vector<char>> 
{
    static constexpr MsgType value = MsgType::CharVectorType;
};

template<MsgType T>
using MsgTypeTrait = typename MsgTypeTraits<T>::type;

template<typename T>
constexpr MsgType ToMsgType = MsgTypeEnumTraits<T>::value;

} // namespace serializer