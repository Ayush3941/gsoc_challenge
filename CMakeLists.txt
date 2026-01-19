cmake_minimum_required(VERSION 3.16)
project(challenge LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1) Build ggml from extern/

add_subdirectory(extern/ggml)

# 2) Your standalone C matmul (no ggml, no xlns)

add_executable(stand_alone_matmul stand_alone_matmul.c)

# 3) ggml demos (C++ files)

add_executable(ggml_demo  ggml_demo.cpp)
add_executable(ggml_demo2 ggml_demo2.cpp)

# Link ggml libs (most ggml builds expose ggml + ggml-cpu)

target_link_libraries(ggml_demo  PRIVATE ggml ggml-cpu)
target_link_libraries(ggml_demo2 PRIVATE ggml ggml-cpu)



# 4) Optional: build xlns tests from extern/xlnscpp (no installation needed)

add_executable(xlns16test extern/xlnscpp/xlns16test.cpp)
add_executable(xlns32test extern/xlnscpp/xlns32test.cpp)

# xlns tests need to compile with xlns sources available

target_include_directories(xlns16test PRIVATE extern/xlnscpp)
target_include_directories(xlns32test PRIVATE extern/xlnscpp)
