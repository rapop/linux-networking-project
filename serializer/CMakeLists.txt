project(serializer)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
  include
)

install(DIRECTORY include/
    DESTINATION include
)

# # install the headers
# install(DIRECTORY include/ DESTINATION include)

# # install and export the target
# install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
#     INCLUDES DESTINATION include
# )

# # include(CMakePackageConfigHelpers)

# install(EXPORT ${PROJECT_NAME}Targets
#   FILE ${PROJECT_NAME}Targets.cmake
#   DESTINATION lib/cmake/${PROJECT_NAME}
# )

# message("testsssssssssssssssssssS: ${CMAKE_CURRENT_SOURCE_DIR}")
# message("testsssssssssssssssssssS2: ${CMAKE_CURRENT_BINARY_DIR}")
# include(CMakePackageConfigHelpers)
# # generate the config file that is includes the exports
# configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
#   "${CMAKE_CURRENT_BINARY_DIR}/serializerConfig.cmake"
#   INSTALL_DESTINATION "lib/cmake/example"
#   NO_SET_AND_CHECK_MACRO
#   NO_CHECK_REQUIRED_COMPONENTS_MACRO
# )

# # generate the version file for the config file
# write_basic_package_version_file(
#   "${CMAKE_CURRENT_BINARY_DIR}/serializerConfigVersion.cmake"
#   VERSION "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
#   COMPATIBILITY AnyNewerVersion
# )

# # install the configuration file
# install(FILES
#   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
#   DESTINATION lib/cmake/${PROJECT_NAME}
# )

# write_basic_package_version_file(
#   "${CMAKE_CURRENT_BINARY_DIR}/serializerConfigVersion.cmake"
#   VERSION 1.0.0
#   COMPATIBILITY AnyNewerVersion
# )

# configure_package_config_file(Config.cmake.in
#   "${CMAKE_CURRENT_BINARY_DIR}/serializerConfig.cmake"
#   INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
# )

# install(FILES
#   "${CMAKE_CURRENT_BINARY_DIR}/serializerConfig.cmake"
#   "${CMAKE_CURRENT_BINARY_DIR}/serializerConfigVersion.cmake"
#   DESTINATION lib/cmake/${PROJECT_NAME}
# )

# install(EXPORT ${PROJECT_NAME}Targets
#   FILE ${PROJECT_NAME}Targets.cmake
#   NAMESPACE ${PROJECT_NAME}::
#   DESTINATION lib/cmake/${PROJECT_NAME}
# )

# export(EXPORT ${PROJECT_NAME}Targets
#     FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
#     NAMESPACE ${PROJECT_NAME}::
# )

add_subdirectory(unittests)