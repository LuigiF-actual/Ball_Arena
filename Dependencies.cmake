#
# Dependencies
#
include(FetchContent)

set(CMAKE_TLS_VERIFY OFF)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # Don't build the supplied example games
    
FetchContent_Declare(
    raylib
    URL "https://github.com/raysan5/raylib/archive/refs/tags/6.0.tar.gz"
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(raylib) 


FetchContent_Declare(
    raygui
    GIT_REPOSITORY "https://github.com/raysan5/raygui.git"
    GIT_SHALLOW TRUE 
    SYSTEM
)
    
FetchContent_MakeAvailable(raygui)

FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG VER-2-14-1
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(freetype)

if(NOT TARGET Freetype::Freetype)
    add_library(Freetype::Freetype ALIAS freetype)  
endif()

FetchContent_Declare(
    rmlui
    GIT_REPOSITORY https://github.com/mikke89/RmlUi.git
    GIT_SHALLOW TRUE 
)

FetchContent_MakeAvailable(rmlui)