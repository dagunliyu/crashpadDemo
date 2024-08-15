# -------------------------------- CrashPad --------------------------------


if(WIN32)
    # set(IBE_LIBPACK_DIR $ENV{IBE_LIBPACK_DIR} CACHE PATH  "Directory of the IBE 3rdparty libpack")
    # MESSAGE(STATUS "Found libpack env variable: ${IBE_LIBPACK_DIR}")
    
    # $ENV{TEST_CRASHPAD_DIR} or ${TEST_CRASHPAD_DIR}
    set(TEST_CRASHPAD_DIR $ENV{TEST_CRASHPAD_DIR} CACHE PATH  "Directory of the IBE 3rdparty libpack")
    MESSAGE(STATUS "Found libpack env variable: ${IBE_LIBPACK_DIR}")

    set(TEST_CRASHPAD_DBG_DIR
        ${TEST_CRASHPAD_DIR}/x64/debug)
    
    set(TEST_CRASHPAD_REL_DIR
        ${TEST_CRASHPAD_DIR}/x64/release)

    set(CRASHPAD_INCLUDE_DIR
        ${TEST_CRASHPAD_DIR}
        ${TEST_CRASHPAD_DIR}/third_party/mini_chromium/mini_chromium
        ${TEST_CRASHPAD_REL_DIR}/gen
    )

    
    # x64 x86
    # debug base     x64/debug/obj/third_party/mini_chromium/mini_chromium/base
    # debug client   x64/debug/obj/client
    # debug handler  x64/debug/obj/handler
    # debug util     x64/debug/obj/util
    set(TEST_CRASHPAD_REL_LIB_DIR
        ${TEST_CRASHPAD_REL_DIR}/obj
    )
    set(TEST_CRASHPAD_DBG_LIB_DIR
        ${TEST_CRASHPAD_DBG_DIR}/obj
    )
    set(CRASHPAD_REL_LIBRARY_DIR
        ${TEST_CRASHPAD_REL_LIB_DIR}/third_party/mini_chromium/mini_chromium/base
        ${TEST_CRASHPAD_REL_LIB_DIR}/client
        ${TEST_CRASHPAD_REL_LIB_DIR}/handler
        ${TEST_CRASHPAD_REL_LIB_DIR}/util
    )
    set(CRASHPAD_DBG_LIBRARY_DIR
        ${TEST_CRASHPAD_DBG_LIB_DIR}/third_party/mini_chromium/mini_chromium/base
        ${TEST_CRASHPAD_DBG_LIB_DIR}/client
        ${TEST_CRASHPAD_DBG_LIB_DIR}/handler
        ${TEST_CRASHPAD_DBG_LIB_DIR}/util
    )
    
    # MESSAGE(STATUS CRASHPAD_INCLUDE_DIR = ${CRASHPAD_INCLUDE_DIR})
    # MESSAGE(STATUS CRASHPAD_LIBRARY_DIR = ${CRASHPAD_LIBRARY_DIR})
    
    if(CRASHPAD_INCLUDE_DIR AND CRASHPAD_REL_LIBRARY_DIR)
        if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
            set(CRASHPAD_LIBRARY_DIR ${CRASHPAD_DBG_LIBRARY_DIR})
        endif()

        if (${CMAKE_BUILD_TYPE} MATCHES "Release")
            set(CRASHPAD_LIBRARY_DIR ${CRASHPAD_REL_LIBRARY_DIR})
        endif()

        set(CRASHPAD_LIBRARIES
            optimized base
            optimized client
            optimized handler
            optimized util
            # optimized common # same dir with client
            debug base
            debug client
            debug handler
            debug util
            # debug common
            )
    endif(CRASHPAD_INCLUDE_DIR AND CRASHPAD_REL_LIBRARY_DIR)
 
    if(CRASHPAD_LIBRARIES)
        MESSAGE(STATUS "CrashPad found:")
        MESSAGE(STATUS "  HeaderDir:  ${CRASHPAD_INCLUDE_DIR}")
        MESSAGE(STATUS "  RelLibsDir:  ${CRASHPAD_REL_LIBRARY_DIR}")
        MESSAGE(STATUS "  DBGLibsDir:  ${CRASHPAD_DBG_LIBRARY_DIR}")
        MESSAGE(STATUS "  Libs:  ${CRASHPAD_LIBRARIES}")
    else(CRASHPAD_LIBRARIES)    
        MESSAGE(STATUS "================================================================\n"
                       "CrashPad not found!\n"
                       "================================================================\n")
    endif(CRASHPAD_LIBRARIES)

else(WIN32)
    MESSAGE(STATUS "Add the crashpad library manually.\n")
endif(WIN32)


