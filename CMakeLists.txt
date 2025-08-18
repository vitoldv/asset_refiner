cmake_minimum_required(VERSION 3.10)
project(asset_refiner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(asset_refiner ${SOURCE_FILES})

# Add project's own include directory
target_include_directories(asset_refiner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#GLFW3 linking
target_include_directories(asset_refiner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw3/include
)
find_library(GLFW3LIB
    NAMES glfw3          
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw3/lib-vc2022
)
if(GLFW3LIB)
    target_link_libraries(asset_refiner PRIVATE ${GLFW3LIB})
    message(STATUS "Found and linked GLFW3: ${GLFW3LIB}")
else()
    message(FATAL_ERROR "GLFW3 library not found.")
endif()