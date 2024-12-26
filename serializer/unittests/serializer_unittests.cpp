#include <serializer/serializer.h>

#include <gtest/gtest.h>

namespace serializer_unittests {

TEST(serializer_unittests, pack_unpack_double)
{
  const double expected_val = 19;
  const std::vector<uint8_t> packed_data = serializer::pack<double>(expected_val);
  const double unpacked_data = serializer::unpack<double>(packed_data);
  EXPECT_EQ(expected_val, unpacked_data);
}

TEST(serializer_unittests, pack_unpackVector_double)
{
  const std::vector<double> expected_val = {1.1, 1.2, 1.3};
  const std::vector<uint8_t> packed_data = serializer::packVector<double>(expected_val);
  const std::vector<double> unpacked_data = serializer::unpackVector<double>(packed_data);
  EXPECT_EQ(expected_val, unpacked_data);
}

TEST(serializer_unittests, pack_unpack_string)
{
  const std::string str = "test";
  const std::vector<char> expected_val(str.begin(), str.end());
  const std::vector<uint8_t> packed_data = serializer::packVector<char>(expected_val);
  const std::vector<char> unpacked_data = serializer::unpackVector<char>(packed_data);
  EXPECT_EQ(expected_val, unpacked_data);
}

TEST(serializer_unittests, pack_unpack_char_type)
{
  const char expected_val = 'a';
  const std::vector<uint8_t> packed_data = serializer::pack<char>(expected_val);
  const serializer::MsgType type = serializer::unpackType(packed_data);
  EXPECT_EQ(type, serializer::MsgType::CharType);
}

TEST(serializer_unittests, pack_unpack_vector_char_type)
{
  const std::string str = "test";
  const std::vector<char> expected_val(str.begin(), str.end());
  const std::vector<uint8_t> packed_data = serializer::packVector<char>(expected_val);
  const serializer::MsgType type = serializer::unpackType(packed_data);
  EXPECT_EQ(type, serializer::MsgType::CharVectorType);
}

} // namespace serializer_unittests