cmake_minimum_required (VERSION 3.8)

project ("RenderingDEMO")

set (SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/RenderingDEMO/shader)
set (ASSET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/RenderingDEMO/asset)
set (BIN_PROJECT_DIR ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_subdirectory ("RenderingDEMO/dependence")
add_subdirectory ("RenderingDEMO/src")
