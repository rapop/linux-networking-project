project(notifier-app)

# find_package(networking REQUIRED)

# add_subdirectory(../networking networking) 
# add_subdirectory(../serializer serializer)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(notifier-app PRIVATE
  networking
)