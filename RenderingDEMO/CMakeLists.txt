add_subdirectory ("dependence")

add_executable (${PROJECT_NAME})

aux_source_directory (src SRC)
target_sources(${PROJECT_NAME} PUBLIC ${SRC})

target_link_libraries (${PROJECT_NAME} PUBLIC glfw opengl32.lib)

target_link_directories (${PROJECT_NAME} PUBLIC 
	dependence/glfw-3.4/include)

target_include_directories (${PROJECT_NAME} PUBLIC
	dependence/spdlog/include)