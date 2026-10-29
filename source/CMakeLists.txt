



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
)

target_include_directories(Ball_Arena SYSTEM PUBLIC "${raygui_SOURCE_DIR}/src" "${raygui_SOURCE_DIR}")

if(MINGW) # makes mingw able to use the <print> header
    target_link_libraries(Ball_Arena PRIVATE stdc++exp)
endif()

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:Ball_Arena>/Assets"
)

add_dependencies(Ball_Arena copy_assets)

set_target_properties(Ball_Arena PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)