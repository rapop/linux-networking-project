cmake_minimum_required(VERSION 3.14)
project(serializer)

# enable CTest testing
# this command needs to be run in the top level CMakeLists.txt file before
# adding subdirectories to discover recursively all the tests and being able
# to run the ctest command.  
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Install the library target and export it
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

# Export the targets for downstream projects
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Config.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)

add_subdirectory(unittests)