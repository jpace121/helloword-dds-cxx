project(helloworld LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5)

find_package(CycloneDDS-CXX REQUIRED)

idlcxx_generate(TARGET HelloWorld_lib FILES "HelloWorld.idl")

add_executable(pub publisher.cpp)
target_link_libraries(pub CycloneDDS-CXX::ddscxx HelloWorld_lib)
set_property(TARGET pub PROPERTY CXX_STANDARD 11)

add_executable(sub subscriber.cpp)
target_link_libraries(sub CycloneDDS-CXX::ddscxx HelloWorld_lib)
set_property(TARGET sub PROPERTY CXX_STANDARD 11)
