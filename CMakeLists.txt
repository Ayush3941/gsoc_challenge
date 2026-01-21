cmake_minimum_required(VERSION 3.16)
project(challenge LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1) Build ggml from extern/

add_subdirectory(extern/ggml)

# 2) Build xlns libraries (extern/xlnscpp)

add_subdirectory(extern/xlnscpp)

# 3) standalone C matmul (no ggml, no xlns)

add_executable(stand_alone_matmul stand_alone_matmul.c)

# 4) xlns matmul demos (C++ linkage; xlns_alt builds)

add_executable(xlns16_matmul xlns16_matmul.c)
set_source_files_properties(xlns16_matmul PROPERTIES LANGUAGE CXX)
target_link_libraries(xlns16_matmul PRIVATE xlns::xlns16)

add_executable(xlns32_matmul xlns32_matmul.c)
set_source_files_properties(xlns32_matmul PROPERTIES LANGUAGE CXX)
target_link_libraries(xlns32_matmul PRIVATE xlns::xlns32)

# 5) ggml demos (C++ files)

add_executable(ggml_demo  ggml_demo.cpp)
add_executable(ggml_demo2 ggml_demo2.cpp)

# Link ggml libs for ggml-cpu

target_link_libraries(ggml_demo  PRIVATE ggml ggml-cpu)
target_link_libraries(ggml_demo2 PRIVATE ggml ggml-cpu)



# 6) build xlns tests from extern/xlnscpp 

add_executable(xlns16test extern/xlnscpp/xlns16test.cpp)
add_executable(xlns32test extern/xlnscpp/xlns32test.cpp)

# xlns tests need to compile with xlns sources available

target_include_directories(xlns16test PRIVATE extern/xlnscpp)
target_include_directories(xlns32test PRIVATE extern/xlnscpp)
