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

TEST(serializer_unittests, pack_unpack_vector_double)
{
  const std::vector<double> expected_val = {1.1, 1.2, 1.3};
  const std::vector<uint8_t> packed_data = serializer::pack_vector<double>(expected_val);
  const std::vector<double> unpacked_data = serializer::unpack_vector<double>(packed_data);
  EXPECT_EQ(expected_val, unpacked_data);
}

TEST(serializer_unittests, pack_unpack_string)
{
  const std::string str = "test";
  const std::vector<char> expected_val(str.begin(), str.end());
  const std::vector<uint8_t> packed_data = serializer::pack_vector<char>(expected_val);
  const std::vector<char> unpacked_data = serializer::unpack_vector<char>(packed_data);
  EXPECT_EQ(expected_val, unpacked_data);
}

} // namespace serializer_unittests