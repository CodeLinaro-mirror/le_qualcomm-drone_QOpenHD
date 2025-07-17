# Platform-specific macro definitions
if(WIN32)
    add_compile_definitions(__windows__)
endif()

if(ANDROID)
    add_compile_definitions(__android__)
endif()

if(APPLE)
    if(IOS)
        add_compile_definitions(__ios__)
    else()
        add_compile_definitions(__macos__)
    endif()
endif()

if(UNIX AND NOT ANDROID AND NOT APPLE)
    add_compile_definitions(__desktoplinux__)
endif()