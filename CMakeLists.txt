cmake_minimum_required (VERSION 3.8)

project ("RenderingDEMO")

set (SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/engine/shader)
set (ASSET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/engine/asset)
set (BIN_PROJECT_DIR ${CMAKE_BINARY_DIR}/engine)

add_subdirectory ("engine/dependence")
add_subdirectory ("engine/src")
