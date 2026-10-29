find_package(OpenGL REQUIRED)

set(HEADER_FILES
    "include/AppLayer.hpp"
    "include/Layer.hpp"
    "include/MenuLayer.hpp"
)

set(SOURCE_FILES
    "AppLayer.cpp"
    "MenuLayer.cpp"
    "${rmlui_SOURCE_DIR}/Backends/RmlUi_Renderer_GL3.cpp"
)

add_library(Layers STATIC)

target_sources(Layers
    PRIVATE
        ${SOURCE_FILES}
    PUBLIC
        ${HEADER_FILES}
)

target_include_directories(Layers
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${rmlui_SOURCE_DIR}/Backends"
        "${raylib_SOURCE_DIR}/src/external"
    SYSTEM PUBLIC
        "${raygui_SOURCE_DIR}/src"
)

target_compile_definitions(Layers
    PUBLIC
        RMLUI_GL3_CUSTOM_LOADER=<glad.h>
)

target_link_libraries(Layers
    PUBLIC
        Objects
        raylib
        RmlUi::RmlUi
        OpenGL::GL
)
