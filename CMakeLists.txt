cmake_minimum_required(VERSION 3.20)

project(serverClient LANGUAGES CXX CUDA)
set(TOOLKIT_ROOT_DIR $ENV{CUDA_PATH})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Client-Render)

find_package(cppzmq)

set(HEADERS
	cuda/Cuda.h
	src/Material.h
	src/Primitive.h
	dep/dependencies.h

	src/Mesh.h
	src/cl_rl/Client.h
	src/third_party/stbi_load.h
	src/third_party/stb_image_write.h
	src/third_party/tiny_obj_loader.h
	src/third_party/jsoncpp.hpp
	src/jsonClass.hpp
	src/camera.hpp

	libzmq/include/zmq.h
	libzmq/include/zmq_utils.h
)

set(HOST_SOURCES
	src/Image.hpp
	
	src/main.cpp
	src/Utils.hpp
	src/Threading.hpp

	cppzmq/zmq.hpp
	cppFiles/Mesh.cpp
	cppFiles/Client.cpp
	cppFiles/Material.cpp
	cppFiles/Primitive.cpp
	cppFiles/Accelerators.cpp

)

set(DEVICE_SOURCES
	cuda/Cuda.cpp
)

set(SOURCES 
	${HOST_SOURCES}
	${DEVICE_SOURCES}
)

set_source_files_properties(${HOST_SOURCES} PROPERTIES LANGUAGE CXX)
set_source_files_properties(${DEVICE_SOURCES} PROPERTIES LANGUAGE CUDA)

message(STATUS "====== CUDA Located: ${CUDA_INCLUDE_DIRS}")
add_executable(${PROJECT_NAME} "${SOURCES};${HEADERS}")

target_link_directories(${PROJECT_NAME} PUBLIC
)
target_include_directories(${PROJECT_NAME} PUBLIC
	${CUDA_INCLUDE_DIRS}
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cppFiles>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/cl_rl>
	cppzmq-static
)
target_link_libraries(${PROJECT_NAME} PUBLIC
	cppzmq-static
    ${CUDA_LIBS}
	${CMAKE_DL_LIBS}
)
target_compile_definitions(${PROJECT_NAME} PRIVATE MESH_FOLDER="${CMAKE_SOURCE_DIR}/mesh")
target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:
                       --generate-line-info
                       --use_fast_math
                       >)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:MSVC>:
                       --MTR_ENABLED
                       >)