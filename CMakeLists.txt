cmake_minimum_required(VERSION 3.10)

project(asset_refiner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(MyPetProject ${SOURCE_FILES})