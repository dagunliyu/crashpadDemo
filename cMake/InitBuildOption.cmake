
macro(InitBuildOptions)

    if(MSVC)
        option(LC_RELEASE_PDB "Create PDB files for Release version" on)
        option(LC_RELEASE_SEH "Enable Structured Exception Handling for Release version" on)
        option(LC_LIBPACK_USE "Use the LibPack to Build selfDemo (only Win32 so far)." ON)
        option(LC_USE_PCH "Activate precompiled headers where it's used." ON)
    else()
        option(LC_LIBPACK_USE "Use the LibPack to Build selfDemo (only Win32 so far)." ON)
        set(LC_LIBPACK_DIR ""  CACHE PATH  "Directory of the SelfDemo LibPack")
    endif()

endmacro(InitBuildOptions)