cmake_minimum_required(VERSION 3.14)
project(notifier-app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(serializer REQUIRED)
find_package(networking REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(notifier-app PRIVATE
  networking::networking
  # serializer::serializer
)