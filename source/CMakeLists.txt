

set(HEADER_FILES
	"include/Box.hpp"
	"include/QuadTree.hpp"
	"include/KinectBody.hpp"
	"include/WorldConfig.hpp"
)

set(SOURCES_FILES
	"main.cpp"
)


add_executable (Ball_Arena)

set_property(TARGET Ball_Arena PROPERTY CXX_STANDARD 23)


target_sources(Ball_Arena

	PUBLIC 
	 ${HEADER_FILES}
	PRIVATE 
	 ${SOURCES_FILES}

)

target_link_libraries(Ball_Arena
	PRIVATE
		raylib

)


if(MINGW)
    target_link_libraries(Ball_Arena PRIVATE stdc++exp)
endif()