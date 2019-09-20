cmake_minimum_required(VERSION 3.0)
project (diffuse)

add_subdirectory(allolib)

add_executable(diffuse
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/reverb.hpp
    ${CMAKE_CURRENT_LIST_DIR}/reverb.cpp
)

set_target_properties(diffuse PROPERTIES
  DEBUG_POSTFIX d
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
)

target_link_libraries(diffuse PRIVATE al)