



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

if(MINGW) # makes mingw able to use the <print> header
    target_link_libraries(Ball_Arena PRIVATE stdc++exp)
endif()