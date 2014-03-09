cmake_minimum_required (VERSION 2.6)

project (Genie)
set (Test_VERSION_MAJOR 0)
set (Test_VERSION_MINOR 0)

# libraries used
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Boost 1.40.0 COMPONENTS system REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} )

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
target_link_libraries (GenieMain ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${ZLIB_LIBRARIES} ${Boost_LIBRARIES} )

# copy resources to binary folder
file( COPY "${PROJECT_SOURCE_DIR}/resource/" DESTINATION "${PROJECT_BINARY_DIR}/resource/")

