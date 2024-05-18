add_executable (${PROJECT_NAME} "RenderingDEMO.cpp" "RenderingDEMO.h")

target_link_libraries (${PROJECT_NAME} PUBLIC glfw opengl32.lib)

target_link_directories (${PROJECT_NAME} PUBLIC 
	${CMAKE_SOURCE_DIR}/dependence/glfw-3.4/include)