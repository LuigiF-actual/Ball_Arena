

set(HEADER_FILES
	"include/AppLayer.hpp"
	"include/Layer.hpp"

)

set(SOURCES_FILES
	"AppLayer.cpp"

)


add_library(Layers STATIC)

set_target_properties(Layers PROPERTIES LINKER_LANGUAGE CXX)

target_sources(Layers
	
	PUBLIC
		${HEADER_FILES}
	PRIVATE
		${SOURCES_FILES}

)

target_include_directories(Layers
    PUBLIC
        "include"
)

target_link_libraries(Layers
    PUBLIC
        Objects
        raylib
)