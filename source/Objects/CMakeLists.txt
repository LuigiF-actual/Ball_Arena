

set(HEADER_FILES
	"include/Box.hpp"
	"include/QuadTree.hpp"
	"include/KinectBody.hpp"
	"include/WorldConfig.hpp"
	"include/Application.hpp"
	"include/CameraHandler.hpp"
)

set(SOURCES_FILES
	
	"Application.cpp"

)


add_library(Objects STATIC)

target_sources(Objects
	PUBLIC
		${HEADER_FILES}
	PRIVATE
		${SOURCES_FILES}
)

target_include_directories(Objects
	PUBLIC 
		"include"

)


target_link_libraries(Objects
    PUBLIC
		Layers
        raylib
)