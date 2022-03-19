cmake_minimum_required(VERSION 3.20)
project(serverClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Client-Render)

find_package(cppzmq)

set(HEADERS
)

set(SOURCES
	src/Material.h

	src/Image.hpp

	src/Primitive.h

	src/Utils.hpp
	src/Threading.hpp
	src/Mesh.h

	src/main.cpp

	src/third_party/stb_image_write.h
	src/third_party/tiny_obj_loader.h

    	cppzmq/zmq.hpp
  	libzmq/include/zmq.h
 	libzmq/include/zmq_utils.h

	src/cl_rl/Client.h
	src/cl_rl/Render.h
	dep/dependencies.h
	
	cppFiles/Mesh.cpp
	cppFiles/Client.cpp
	cppFiles/Material.cpp
	cppFiles/Primitive.cpp
	cppFiles/Accelerators.cpp
)

add_executable(${PROJECT_NAME} "${SOURCES};${HEADERS}")

target_link_directories(${PROJECT_NAME} PUBLIC
)

target_include_directories(${PROJECT_NAME} PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cppFiles>
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/cl_rl>
cppzmq-static
)

target_link_libraries(${PROJECT_NAME} PUBLIC
cppzmq-static
${CMAKE_DL_LIBS}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE MESH_FOLDER="${CMAKE_SOURCE_DIR}/mesh")