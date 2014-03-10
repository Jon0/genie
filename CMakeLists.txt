cmake_minimum_required (VERSION 2.6)

project (Genie)
set (Test_VERSION_MAJOR 0)
set (Test_VERSION_MINOR 0)

# libraries used
set(GLEW_SOURCE "${PROJECT_SOURCE_DIR}/library/glew-1.10.0/src/glew.c")
add_subdirectory (library/glfw-3.0.4)


include_directories ("${PROJECT_BINARY_DIR}")
include_directories ( ${GLEW_INCLUDE_DIR} )
include_directories ( ${GLFW_INCLUDE_DIR} )
include_directories ("${PROJECT_SOURCE_DIR}/library/glew-1.10.0/include")
include_directories ("${PROJECT_SOURCE_DIR}/library/glfw-3.0.4/include")

#find_package(ZLIB REQUIRED)
#find_package(Boost 1.40.0 COMPONENTS system REQUIRED)
#include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ) #${Boost_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS}

add_library( glew STATIC
	${GLEW_SOURCE}
)

file(GLOB SRC_FILES
    "src/*.cpp"
    "src/Data/*.cpp"
    "src/Graphics/*.cpp"
    "src/Model/*.cpp"
    "src/Network/*.cpp"
    "src/Types/*.cpp"
)


add_definitions(-std=c++11)
add_executable (GenieMain ${SRC_FILES})
target_link_libraries (GenieMain glew glfw ${GLFW_LIBRARIES} ) #${Boost_LIBRARIES} ${ZLIB_LIBRARIES}



# copy resources to binary folder
file( COPY "${PROJECT_SOURCE_DIR}/resource/" DESTINATION "${PROJECT_BINARY_DIR}/resource/")