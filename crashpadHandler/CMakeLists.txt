
cmake_minimum_required(VERSION 3.18)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# ext cmake
include(../cMake/InitBuildOption.cmake)
include(../cMake/SetGlobalCompilerAndLinkerSettings.cmake)
include(../cMake/FindCrashPad.cmake)

# exe macro
InitBuildOptions()
SetGlobalCompilerAndLinkerSettings()

# compile_options should take before executable
# MTd MT: statically link the runtime libraries
if(MSVC)
    add_compile_options(
        $<$<CONFIG:Debug>:/MDd>
        $<$<CONFIG:Release>:/MD>
    )
endif()

# link_directories(
#     ${CRASHPAD_LIBRARY_DIR}
# )

# include_directories(
#     ${CMAKE_CURRENT_SOURCE_DIR}/singleton/
#     ${CRASHPAD_INCLUDE_DIR}
# )

set(CRASHPADHANDLER_LIBRARIES
    optimized crashpadHandler
    debug crashpadHandler
)

# ${CMAKE_SOURCE_DIR}
# ${CMAKE_BINARY_DIR}
# ${CMAKE_CURRENT_SOURCE_DIR}
# ${CMAKE_CURRENT_BINARY_DIR}
set(CRASHPADHANDLER_SRCS
    # ${CMAKE_CURRENT_SOURCE_DIR}/singleton/call_once.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/singleton/singleton.h
    crashpadHandler.h
    crashpadHandler.cpp
    # call_once.h
    # singleton.h
)

# handler
add_library(crashpadHandler STATIC ${CRASHPADHANDLER_SRCS})

target_include_directories(crashpadHandler PUBLIC
    ${CRASHPAD_INCLUDE_DIR}
)

target_link_directories(crashpadHandler PRIVATE
    ${CRASHPAD_LIBRARY_DIR}
)

target_link_libraries(crashpadHandler PRIVATE
    ${CRASHPAD_LIBRARIES}
    # base
    # client
    # handler
    # util
    # common
)

# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#     set_target_properties(crashpadHandler PROPERTIES POSTFIX "d")
# endif()

if(WIN32)
    set(OutputName crashpadHandler)
    set_target_properties(crashpadHandler PROPERTIES OUTPUT_NAME ${OutputName})
    set_target_properties(crashpadHandler PROPERTIES DEBUG_OUTPUT_NAME ${OutputName}_d)
endif(WIN32)
