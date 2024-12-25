cmake_minimum_required(VERSION 3.14)
project(linux-networking-project)

# enable CTest testing
# this command needs to be run in the top level CMakeLists.txt file before
# adding subdirectories to discover recursively all the tests and being able
# to run the ctest command.  
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(serializer)
add_subdirectory(networking)
add_subdirectory(notifier-app)