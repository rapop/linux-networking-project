project(networking)

# find_package(serializer REQUIRED)

add_library(${PROJECT_NAME} STATIC
  src/client.cpp
  src/notifier.cpp
  src/publisher.cpp
  src/server.cpp
  src/socket_communicator.cpp
  src/subscriber.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  include
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  serializer
)