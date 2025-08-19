cmake_minimum_required(VERSION 3.10)
project(asset_refiner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.c" "externals/imgui/*.cpp")

add_executable(asset_refiner ${SOURCE_FILES}    )

# Add project's own include directory
target_include_directories(asset_refiner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw3/include
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/externals
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/imgui
)

#GLFW3 linking
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

# Assimp linking
target_include_directories(asset_refiner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/externals/assimp-5.4.3/include)
find_library(ASSIMPLIB NAMES assimp-vc143-mt.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/externals/assimp-5.4.3/lib/Release)
if(ASSIMPLIB)
    target_link_libraries(asset_refiner PRIVATE ${ASSIMPLIB})
    message(STATUS "Found and linked Assimp: ${ASSIMPLIB}")
else()
    message(FATAL_ERROR "Assimp library not found.")
endif()

# Copy assimp dll
add_custom_command(TARGET asset_refiner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/externals/assimp-5.4.3/bin/assimp-vc143-mt.dll"
        "$<TARGET_FILE_DIR:asset_refiner>"
    COMMENT "Copying Assimp DLL to output directory"
)

# Copy shader sources
add_custom_command(TARGET asset_refiner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders"
        "$<TARGET_FILE_DIR:asset_refiner>/shaders"
    COMMENT "Copying shader source files to output directory"
)

# Copy assets
add_custom_command(TARGET asset_refiner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:asset_refiner>/assets"
    COMMENT "Copying shader source files to output directory"
)