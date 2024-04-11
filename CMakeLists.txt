cmake_minimum_required(VERSION 3.0)
project(MyProject)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Demo1
add_executable(AppDemo1 demo1/app.cpp)
target_link_libraries(AppDemo1 vsomeip3)
set_target_properties(AppDemo1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/demo1/build")

# Demo2 - Server
add_executable(ServerDemo2 demo2/server.cpp)
target_link_libraries(ServerDemo2 vsomeip3)
set_target_properties(ServerDemo2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/demo2/build")

# Demo2 - Client
add_executable(ClientDemo2 demo2/client.cpp)
target_link_libraries(ClientDemo2 vsomeip3)
set_target_properties(ClientDemo2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/demo2/build")

# Demo3 - Server
add_executable(ServerDemo3 demo3/server.cpp)
target_link_libraries(ServerDemo3 vsomeip3)
set_target_properties(ServerDemo3 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/demo3/build")

# Demo3 - Client
add_executable(ClientDemo3 demo3/client.cpp)
target_link_libraries(ClientDemo3 vsomeip3 pthread) # 添加pthread链接
set_target_properties(ClientDemo3 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/demo3/build")

# Demo4 - Server
add_executable(ServerDemo4 demo4/server.cpp)
target_link_libraries(ServerDemo4 vsomeip3 pthread)
set_target_properties(ServerDemo4 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/demo4/build")

# Demo4 - Client
add_executable(ClientDemo4 demo4/client.cpp)
target_link_libraries(ClientDemo4 vsomeip3 pthread) # 添加pthread链接
set_target_properties(ClientDemo4 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/demo4/build")
