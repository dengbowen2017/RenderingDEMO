add_executable (${PROJECT_NAME})

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES} ${SOURCE_FILES})

target_sources(${PROJECT_NAME} PUBLIC ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries (${PROJECT_NAME} PUBLIC
	glfw
	glad
	opengl32.lib)

target_link_directories (${PROJECT_NAME} PUBLIC 
	${PROJECT_SOURCE_DIR}/dependence/glfw-3.4/include
	${PROJECT_SOURCE_DIR}/dependence/glad/include)

target_include_directories (${PROJECT_NAME} PUBLIC
	${PROJECT_SOURCE_DIR}/dependence/spdlog/include
	${PROJECT_SOURCE_DIR}/src)