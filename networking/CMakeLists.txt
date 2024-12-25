cmake_minimum_required(VERSION 3.14)
project(networking)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(serializer REQUIRED)

add_library(${PROJECT_NAME} STATIC
  src/client.cpp
  src/notifier.cpp
  src/publisher.cpp
  src/server.cpp
  src/socket_communicator.cpp
  src/subscriber.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Install the library and headers
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

# Export the targets for downstream projects
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Config.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  serializer::serializer
)