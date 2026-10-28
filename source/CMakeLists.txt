



add_executable (Ball_Arena "main.cpp")
set_target_properties(Ball_Arena PROPERTIES LINKER_LANGUAGE CXX)

set_property(TARGET Ball_Arena PROPERTY CXX_STANDARD 23)

add_subdirectory(Layers)
add_subdirectory(Objects)

target_link_libraries(Ball_Arena
    PRIVATE
        Objects
        Layers
        raylib
        RmlUi::RmlUi
)

target_include_directories(Ball_Arena SYSTEM PUBLIC "${raygui_SOURCE_DIR}/src" "${raygui_SOURCE_DIR}")

target_sources(Ball_Arena PRIVATE
    "${rmlui_SOURCE_DIR}/Backends/RmlUi_Renderer_GL3.cpp"
)

target_include_directories(Ball_Arena PRIVATE
    "${rmlui_SOURCE_DIR}/Backends"
)

target_sources(Ball_Arena PRIVATE
    "${rmlui_SOURCE_DIR}/Backends/RmlUi_Renderer_GL3.cpp"
)

target_include_directories(Ball_Arena PRIVATE
    "${rmlui_SOURCE_DIR}/Backends"
    "${raylib_SOURCE_DIR}/src/external"
)


# Tell RmlUi to use raylib's already-linked GLAD declarations.
target_compile_definitions(Ball_Arena PRIVATE
    RMLUI_GL3_CUSTOM_LOADER=<glad.h>
)

find_package(OpenGL REQUIRED)

if(MINGW) # makes mingw able to use the <print> header
    target_link_libraries(Ball_Arena PRIVATE stdc++exp)
endif()