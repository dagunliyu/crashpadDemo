# -------------------------------- CrashPad --------------------------------


if(WIN32)
    # set(IBE_LIBPACK_DIR $ENV{IBE_LIBPACK_DIR} CACHE PATH  "Directory of the IBE 3rdparty libpack")
    # MESSAGE(STATUS "Found libpack env variable: ${IBE_LIBPACK_DIR}")

    # D:\Projects\Proj_Coding_Alog_Interview_Recruit\Proj_Basic_proj\build_crashpad\crashpad_depot2\crashpad
    # or
    # D:\Projects\Proj_Coding_Alog_Interview_Recruit\Proj_Basic_proj\build_crashpad\crashpad_depot\crashpad
    set(TEST_CRASHPAD_DIR $ENV{TEST_CRASHPAD_DIR} CACHE PATH  "Directory of the IBE 3rdparty libpack")
    MESSAGE(STATUS "Found libpack env variable: ${IBE_LIBPACK_DIR}")

    set(CRASHPAD_INCLUDE_DIR
        ${TEST_CRASHPAD_DIR}
        ${TEST_CRASHPAD_DIR}/third_party/mini_chromium/mini_chromium
        # ${TEST_CRASHPAD_DIR}/x64t/debug/gen
        ${TEST_CRASHPAD_DIR}/x86-t/debug/gen
        # x86-t
        # /gen/build
        # ${IBE_LIBPACK_DIR}/crashpad/include
        # ${IBE_LIBPACK_DIR}/crashpad/include/mini_chromium/mini_chromium)
    )

    
    # debug base     x86-t/debug/obj/third_party/mini_chromium/mini_chromium/base
    # debug client   x86-t/debug/obj/client
    # debug handler  x86-t/debug/obj/handler
    # debug util     x86-t/debug/obj/util
    set(TEST_CRASHPAD_LIB_DIR 
        # ${TEST_CRASHPAD_DIR}/x64t/debug/obj
        ${TEST_CRASHPAD_DIR}/x86-t/debug/obj
        # x64t
        # x86-t
    )
    set(CRASHPAD_LIBRARY_DIR
        ${TEST_CRASHPAD_LIB_DIR}/third_party/mini_chromium/mini_chromium/base
        ${TEST_CRASHPAD_LIB_DIR}/client
        ${TEST_CRASHPAD_LIB_DIR}/handler
        ${TEST_CRASHPAD_LIB_DIR}/util
        # ${TEST_CRASHPAD_DIR}/crashpad/lib
    )
    
    # MESSAGE(STATUS CRASHPAD_INCLUDE_DIR = ${CRASHPAD_INCLUDE_DIR})
    # MESSAGE(STATUS CRASHPAD_LIBRARY_DIR = ${CRASHPAD_LIBRARY_DIR})
    

    if(CRASHPAD_INCLUDE_DIR AND CRASHPAD_LIBRARY_DIR)
        set(CRASHPAD_LIBRARIES 
            optimized base
            optimized client
            optimized handler
            optimized util
            # debug based
            # debug clientd
            # debug handler
            # debug utild)
            debug base.lib
            debug client.lib
            debug handler.lib
            debug util.lib)
    endif(CRASHPAD_INCLUDE_DIR AND CRASHPAD_LIBRARY_DIR)
 
    if(CRASHPAD_LIBRARIES)
        MESSAGE(STATUS "CrashPad found:")
        MESSAGE(STATUS "  HeaderDir:  ${CRASHPAD_INCLUDE_DIR}")
        MESSAGE(STATUS "  LibsDir:  ${CRASHPAD_LIBRARY_DIR}")
        MESSAGE(STATUS "  Libs:  ${CRASHPAD_LIBRARIES}")
    else(CRASHPAD_LIBRARIES)    
        MESSAGE(STATUS "================================================================\n"
                       "CrashPad not found!\n"
                       "================================================================\n")
    endif(CRASHPAD_LIBRARIES)

else(WIN32)
    MESSAGE(STATUS "Add the crashpad library manually.\n")
endif(WIN32)


