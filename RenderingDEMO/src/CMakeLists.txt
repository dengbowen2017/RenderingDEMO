add_executable (${PROJECT_NAME})

add_compile_definitions (GLFW_INCLUDE_NONE)

set (DEPENDENCES_DIR ${PROJECT_SOURCE_DIR}/RenderingDEMO/dependence)
set (SOURCE_DIR ${PROJECT_SOURCE_DIR}/RenderingDEMO/src)

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES} ${SOURCE_FILES})

target_sources(${PROJECT_NAME} PUBLIC ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries (${PROJECT_NAME} PUBLIC
	glfw
	glad
	imgui
	opengl32.lib)

target_link_directories (${PROJECT_NAME} PUBLIC 
	${DEPENDENCES_DIR}/glfw-3.4/include
	${DEPENDENCES_DIR}/glad/include
	${DEPENDENCES_DIR}/imgui)

target_include_directories (${PROJECT_NAME} PUBLIC
	${DEPENDENCES_DIR}/spdlog/include
	${SOURCE_DIR})

target_precompile_headers (${PROJECT_NAME} PUBLIC pch.h)