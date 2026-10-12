# CMakeList.txt : CMake project for Ball_Arena, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.30.0)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Ball_Arena" CXX)
set(CMAKE_CXX_STANDARD 23)

# TODO: Add tests and install targets if needed.
include(Dependencies.cmake)
include(Warnings.cmake)

add_subdirectory("source")

#For some reason my clang-tidy was conflicting with mingw
if(NOT MINGW)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY 
            "${CLANG_TIDY_EXE};--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy;--header-filter=.*(include|source).*;--extra-arg-before=--driver-mode=g++"
        )
    endif()
else()
    unset(CMAKE_CXX_CLANG_TIDY CACHE)
endif()