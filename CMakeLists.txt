
cmake_minimum_required(VERSION 3.18)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(crashpadDemo)

# ext cmake
include(cMake/InitBuildOption.cmake)
include(cMake/SetGlobalCompilerAndLinkerSettings.cmake)
include(cMake/FindCrashPad.cmake)

# exe macro
InitBuildOptions()
SetGlobalCompilerAndLinkerSettings()

set(targetNames
    cpdemo1
    cpdemo2
    # cpHandlerDemo
)

# # compile_options should take before executable
# if(MSVC)
#     add_compile_options(
#         $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
#         $<$<CONFIG:Release>:/MT> #--|
#     )
# endif()
add_subdirectory(util)

# handler
# BUILDSYSTEM_VARIABLES in add_subdir will create a same name dir
add_subdirectory(crashpadHandler)

# demos that use crashpadHandler
add_executable(cpHandlerDemo 
    cpHandlerDemo.cpp
    PreCompiled.h)
message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}") 
message(STATUS "CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}") 
message(STATUS "CRASHPADHANDLER_LIBRARIES = ${CRASHPADHANDLER_LIBRARIES}") 
target_include_directories(cpHandlerDemo PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/crashpadHandler
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_directories(cpHandlerDemo PUBLIC
    ${CRASHPAD_LIBRARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/crashpadHandler/Release # libs can be moved to target-dir through IBE_INSTALL
    ${CMAKE_CURRENT_BINARY_DIR}/crashpadHandler/Debug
    ${CMAKE_CURRENT_BINARY_DIR}/cpHalper/Release
    ${CMAKE_CURRENT_BINARY_DIR}/cpHalper/Debug
)
target_link_libraries(cpHandlerDemo
    ${CRASHPAD_LIBRARIES}
    # ${CRASHPADHANDLER_LIBRARIES}
    debug crashpadHandler
    optimized crashpadHandler
    # ${cpHelper} # why it is doesnt work?
    debug cpHelper_d
    optimized cpHelper
)

# demos that use crashpad in 3rdParty dierctly
add_executable(cpdemo1 cpdemo1.cpp)
add_executable(cpdemo2 cpdemo2.cpp)

###### method1 ######
foreach(target_Name ${targetNames})
    message(STATUS "target_Name = ${target_Name}")
    target_include_directories(${target_Name} PUBLIC
        ${CRASHPAD_INCLUDE_DIR}
    )
    target_link_directories(${target_Name} PUBLIC
        ${CRASHPAD_LIBRARY_DIR}
    ) 
    target_link_libraries(${target_Name} PUBLIC
        ${CRASHPAD_LIBRARIES}
    )
endforeach()
