# -------------------------------- CrashPad --------------------------------


if(WIN32)
    # set(IBE_LIBPACK_DIR $ENV{IBE_LIBPACK_DIR} CACHE PATH  "Directory of the IBE 3rdparty libpack")
    # MESSAGE(STATUS "Found libpack env variable: ${IBE_LIBPACK_DIR}")

    # D:\Projects\Proj_Coding_Alog_Interview_Recruit\Proj_Basic_proj\build_crashpad\crashpad_depot2\crashpad
    # or
    # D:\Projects\Proj_Coding_Alog_Interview_Recruit\Proj_Basic_proj\build_crashpad\crashpad_depot\crashpad
    set(TEST_CRASHPAD_DIR $ENV{TEST_CRASHPAD_DIR} CACHE PATH  "Directory of the IBE 3rdparty libpack")
    MESSAGE(STATUS "Found libpack env variable: ${IBE_LIBPACK_DIR}")

    MESSAGE(STATUS CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR})

    set(CRASHPAD_INCLUDE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/crashpad/Include/crashpad
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/crashpad/Include/crashpad/third_party/mini_chromium/mini_chromium
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/crashpad/Include/crashpad/out/Default/gen
    )
 
    set(CRASHPAD_DEBUG_LIBRARY_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/crashpad/Libraries/Windows/MDd
    )
    
    set(CRASHPAD_RELEASE_LIBRARY_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/crashpad/Libraries/Windows/MD
    )
    
    # MESSAGE(STATUS CRASHPAD_INCLUDE_DIR = ${CRASHPAD_INCLUDE_DIR})
    # MESSAGE(STATUS CRASHPAD_LIBRARY_DIR = ${CRASHPAD_LIBRARY_DIR})
    

    if(CRASHPAD_INCLUDE_DIR AND CRASHPAD_DEBUG_LIBRARY_DIR)
        set(CRASHPAD_DEBUG_LIBRARIES
            debug base.lib
            debug client
            debug common
            debug util)
    endif(CRASHPAD_INCLUDE_DIR AND CRASHPAD_DEBUG_LIBRARY_DIR)
 
    if(CRASHPAD_INCLUDE_DIR AND CRASHPAD_RELEASE_LIBRARY_DIR)
        set(CRASHPAD_RELEASE_LIBRARIES
            optimized base
            optimized client
            optimized common
            optimized util)
    endif(CRASHPAD_INCLUDE_DIR AND CRASHPAD_RELEASE_LIBRARY_DIR)

    if(CRASHPAD_DEBUG_LIBRARIES AND CRASHPAD_RELEASE_LIBRARIES)
        MESSAGE(STATUS "CrashPad found:")
        MESSAGE(STATUS "  HeaderDir:  ${CRASHPAD_INCLUDE_DIR}")
        MESSAGE(STATUS "  DBG-LibsDir:  ${CRASHPAD_DEBUG_LIBRARY_DIR}")
        MESSAGE(STATUS "  DBG-Libs:  ${CRASHPAD_DEBUG_LIBRARIES}")
        MESSAGE(STATUS "  REL-LibsDir:  ${CRASHPAD_RELEASE_LIBRARY_DIR}")
        MESSAGE(STATUS "  REL-Libs:  ${CRASHPAD_RELEASE_LIBRARIES}")
    else(CRASHPAD_DEBUG_LIBRARIES AND CRASHPAD_RELEASE_LIBRARIES)    
        MESSAGE(STATUS "================================================================\n"
                       "CrashPad not found!\n"
                       "================================================================\n")
    endif(CRASHPAD_DEBUG_LIBRARIES AND CRASHPAD_RELEASE_LIBRARIES)

else(WIN32)
    MESSAGE(STATUS "Add the crashpad library manually.\n")
endif(WIN32)


