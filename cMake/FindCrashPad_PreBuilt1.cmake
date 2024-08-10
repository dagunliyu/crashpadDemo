# -------------------------------- CrashPad --------------------------------


if(WIN32)
    # set(IBE_LIBPACK_DIR $ENV{IBE_LIBPACK_DIR} CACHE PATH  "Directory of the IBE 3rdparty libpack")
    # MESSAGE(STATUS "Found libpack env variable: ${IBE_LIBPACK_DIR}")

    set(CRASHPAD_INCLUDE_DIR 
        ${IBE_LIBPACK_DIR}/crashpad/include
        ${IBE_LIBPACK_DIR}/crashpad/include/mini_chromium/mini_chromium)
    set(CRASHPAD_LIBRARY_DIR ${IBE_LIBPACK_DIR}/crashpad/lib)
    
    # MESSAGE(STATUS CRASHPAD_INCLUDE_DIR = ${CRASHPAD_INCLUDE_DIR})
    # MESSAGE(STATUS CRASHPAD_LIBRARY_DIR = ${CRASHPAD_LIBRARY_DIR})
    
    if(CRASHPAD_INCLUDE_DIR AND CRASHPAD_LIBRARY_DIR)
        set(CRASHPAD_LIBRARIES 
            optimized base
            optimized client
            optimized handler
            optimized util
            debug based
            debug clientd
            debug handler
            debug utild)
    endif(CRASHPAD_INCLUDE_DIR AND CRASHPAD_LIBRARY_DIR)
 
    if(CRASHPAD_LIBRARIES)
        MESSAGE(STATUS "CrashPad found:")
        MESSAGE(STATUS "  HeaderDir:  ${CRASHPAD_INCLUDE_DIR}")
        MESSAGE(STATUS "  Libs:  ${CRASHPAD_LIBRARIES}")
    else(CRASHPAD_LIBRARIES)    
        MESSAGE(STATUS "================================================================\n"
                       "CrashPad not found!\n"
                       "================================================================\n")
    endif(CRASHPAD_LIBRARIES)

else(WIN32)
    MESSAGE(STATUS "Add the crashpad library manually.\n")
endif(WIN32)


