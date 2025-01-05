project(networking)

add_library(${PROJECT_NAME} STATIC
  src/client.cpp
  src/double_vector_subscriber.cpp
  src/notifier.cpp
  src/publisher.cpp
  src/server.cpp
  src/socket_communicator.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  serializer
)