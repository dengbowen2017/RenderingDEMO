add_executable (${PROJECT_NAME})

add_compile_definitions (GLFW_INCLUDE_NONE)

set (DEPENDENCES_DIR ${PROJECT_SOURCE_DIR}/RenderingDEMO/dependence)
set (SOURCE_DIR ${PROJECT_SOURCE_DIR}/RenderingDEMO/src)

file (GLOB_RECURSE HEADER_FILES "*.h")
file (GLOB_RECURSE SOURCE_FILES "*.cpp")

source_group (TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES} ${SOURCE_FILES})

target_sources (${PROJECT_NAME} PUBLIC ${HEADER_FILES} ${SOURCE_FILES} ${DEPENDENCES_DIR}/stb_image/stb_image.cpp)

target_link_libraries (${PROJECT_NAME} PUBLIC
	glfw
	glad
	imgui
	opengl32.lib
	d3d11.lib
	dxgi.lib
	dxguid.lib
	winmm.lib
	d3dcompiler.lib)

target_link_directories (${PROJECT_NAME} PUBLIC 
	${DEPENDENCES_DIR}/glfw-3.4/include
	${DEPENDENCES_DIR}/glad/include
	${DEPENDENCES_DIR}/imgui)

target_include_directories (${PROJECT_NAME} PUBLIC
	${DEPENDENCES_DIR}/spdlog/include
	${DEPENDENCES_DIR}/stb_image
	${DEPENDENCES_DIR}/eigen
	${SOURCE_DIR})

target_precompile_headers (${PROJECT_NAME} PUBLIC pch.h)

set (POST_BUILD_COMMANDS
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADER_DIR} ${BIN_PROJECT_DIR}/shader
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSET_DIR} ${BIN_PROJECT_DIR}/asset)

add_custom_command (TARGET ${PROJECT_NAME} ${POST_BUILD_COMMANDS})