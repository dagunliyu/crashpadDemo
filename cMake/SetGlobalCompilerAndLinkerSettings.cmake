macro(SetGlobalCompilerAndLinkerSettings)

    if(MSVC)
        # essential!!
        message(STATUS CMAKE_SOURCE_SRC = ${CMAKE_SOURCE_SRC})
        message(STATUS CMAKE_BINARY_SRC = ${CMAKE_BINARY_SRC})
        include_directories(${CMAKE_SOURCE_SRC})
        include_directories(${CMAKE_BINARY_SRC})

        # PDB
        if(LC_RELEASE_PDB)
            set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
            add_definitions(/Zi)
            add_definitions(/Od)
            # tell linker to generate debug info!!
            set (CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG")
            set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG")
        endif(LC_RELEASE_PDB)

        # SEH
        if(LC_RELEASE_SEH)
            # remove /EHsc or /EHs flags because they are incompatible with /EHa
            if (${CMAKE_BUILD_TYPE} MATCHES "Release")
                string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
                string(REPLACE "/EHs" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
                set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /EHa")
            endif()
        endif(LC_RELEASE_SEH)

        # MP
        option(LC_USE_MP_COMPILE_FLAG "Add /MP flag to the compiler definitions. Speeds up the compile on multi processor machines" OFF)
        if(LC_USE_MP_COMPILE_FLAG)
            # set "Build with Multiple Processes"
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
        endif()

    else(MSVC)    
        set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DLC_DEBUG")
        #message(STATUS "DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
    endif(MSVC)
    

    if(MINGW)
        
    endif(MINGW)
    

endmacro(SetGlobalCompilerAndLinkerSettings)