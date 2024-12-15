project(serializer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} INTERFACE
  # src/double_vector.cpp
  # src/double.cpp
  # src/string.cpp 
  # src/type_register.cpp
)

target_include_directories(${PROJECT_NAME} INTERFACE
  include
)



add_subdirectory(unittests)