project(serializer_unittests)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} serializer_unittests.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE 
  GTest::gtest
  GTest::gtest_main
  pthread
  serializer
)

gtest_discover_tests(${PROJECT_NAME})
