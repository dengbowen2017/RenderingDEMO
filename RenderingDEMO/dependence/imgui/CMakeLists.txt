project ("IMGUI")

aux_source_directory (. SRC_FILES)

set (BACKENDS
    "backends/imgui_impl_glfw.cpp"
    "backends/imgui_impl_opengl3.cpp"
    "backends/imgui_impl_dx11.cpp")

add_library (imgui ${SRC_FILES} ${BACKENDS})

target_include_directories (imgui PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${RenderingDEMO_SOURCE_DIR}/RenderingDEMO/dependence/glfw-3.4/include)
