project(notifier-app)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(notifier-app PRIVATE
  networking
)