
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
#     ${CPHELPER_LIBRARY_DIR}
# )

# include_directories(
#     ${CMAKE_CURRENT_SOURCE_DIR}/singleton/
#     ${CPHELPER_INCLUDE_DIR}
# )

set(CPHELPER_LIBRARIES
    optimized crashpadHandler
    debug crashpadHandler
)

# ${CMAKE_SOURCE_DIR}
# ${CMAKE_BINARY_DIR}
# ${CMAKE_CURRENT_SOURCE_DIR}
# ${CMAKE_CURRENT_BINARY_DIR}
set(CPHELPER_SRCS
    # ${CMAKE_CURRENT_SOURCE_DIR}/singleton/call_once.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/singleton/singleton.h
    cpHelper.h
    cpHelper.cpp
    PreCompiled.h
    # call_once.h
    # singleton.h
)

# handler
add_library(cpHelper SHARED ${CPHELPER_SRCS})

# target_include_directories(crashpadHandler PUBLIC
#     ${CPHELPER_INCLUDE_DIR}
# )

# target_link_directories(crashpadHandler PRIVATE
#     ${CPHELPER_LIBRARY_DIR}
# )

# target_link_libraries(crashpadHandler PRIVATE
#     ${CPHELPER_LIBRARIES}
# )

if(WIN32)

    set(OutputName cpHelper)
    set_target_properties(cpHelper PROPERTIES OUTPUT_NAME ${OutputName})
    set_target_properties(cpHelper PROPERTIES DEBUG_OUTPUT_NAME ${OutputName}_d)
    
endif(WIN32)

# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#     set_target_properties(crashpadHandler PROPERTIES POSTFIX "d")
# endif()
# set_target_properties(crashpadHandler PROPERTIES OUTPUT_NAME)

# macro(SET_BIN_DIR )

if(DEFINED ENV{LC-BIN})
    set(LC_BIN_DIR $ENV{LC-BIN} CACHE PATH "dir of lc-bin")
else()
    set(LC_BIN_DIR ${CMAKE_SOURCE_DIR}/bin CACHE PATH "dir of lc-bin")
endif(DEFINED )

macro(SET_BIN_DIR projName outName)
    set_target_properties(${projName} PROPERTIES OUTPUT_NAME ${outName})
    if(WIN32)
        set_target_properties(${projName} PROPERTIES DEBUG_OUTPUT_NAME ${outName}_d)
        if(${ARGC} EQUAL 2)
            # runtime output
            set_target_properties(${projName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LC_BIN_DIR}/bin)
            set_target_properties(${projName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LC_BIN_DIR}/Release/bin)
            set_target_properties(${projName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LC_BIN_DIR}/Debug/bin)
            # lib output set
            set_target_properties(${projName} properties library_output_directory ${LC_BIN_DIR}/lib)
            set_target_properties(${projName} PROPERTIESE LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LC_BIN_DIR}/lib)
            set_target_properties(${projName} PROPERTIESE LIBRARY_OUTPUT_DIRECTORY_DEBUG ${LC_BIN_DIR}/lib)
        endif(${ARGC} EQUAL 2)
        
        if(${ARGC} GREATER 2)
            # TODO
        endif(${ARGC} GREATER 2)
    else(WIN32)
        # TODO
    endif(WIN32)
endmacro(SET_BIN_DIR)


macro(LC_INSTALL projectName targetPath install_cmake)
    if(INSTALL_PLATFORM)
        if(WIN32)
            # TODO
        else(WIN32)
        endif(WIN32)        
    endif(INSTALL_PLATFORM)
endmacro()

