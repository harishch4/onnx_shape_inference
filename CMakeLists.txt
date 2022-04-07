cmake_minimum_required(VERSION 3.0.0)
project(shape_infer VERSION 0.1.0)

include(CTest)
enable_testing()
set(CMAKE_CXX_FLAGS "-DONNX_ML=1 -DONNX_NAMESPACE=onnx")
set(ONNX_SRC_DIR "/home/harry/github/onnx")
set(ONNX_BUILD_DIR "/home/harry/github/onnx/.setuptools-cmake-build")
include_directories(${ONNX_BUILD_DIR})
include_directories(${ONNX_SRC_DIR})

add_executable(shape_infer main.cpp)
target_link_libraries(shape_infer PUBLIC ${ONNX_BUILD_DIR}/libonnx_proto.so ${ONNX_BUILD_DIR}/libonnx.so -lprotobuf)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
