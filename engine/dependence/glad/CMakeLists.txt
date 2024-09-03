project (GLAD)

aux_source_directory (src SOURCE_FILES)

add_library(glad ${SOURCE_FILES})

target_include_directories (glad PUBLIC ${PROJECT_SOURCE_DIR}/include)
