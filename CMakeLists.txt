cmake_minimum_required(VERSION 3.1)

project(WindowsEx)

set(CMAKE_CXX_STANDARD 11)

set(WINDOWS_EX_SOURCES
    EscapeCommandLineArg.c
    FileSystem.c
    WinApiError.cpp
)

if(WINDOWS_EX_GENERATE_GET_ERROR_LABEL_C)

    find_package(Python 3.7)

    message("Generating GetErrorLabel.c")
    execute_process(
        COMMAND python generate_GetErrorLabel_c/main.py
            --output ${CMAKE_CURRENT_BINARY_DIR}/GetErrorLabel.c
            --cache ${CMAKE_CURRENT_BINARY_DIR}/.error_codes.txt
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        ERROR_VARIABLE CODE_GENERATION_ERROR
    )
    if(CODE_GENERATION_ERROR)
        message(FATAL "${CODE_GENERATION_ERROR}")
    endif()

    list(APPEND WINDOWS_EX_SOURCES
        ${CMAKE_CURRENT_BINARY_DIR}/GetErrorLabel.c
    )

else()

    list(APPEND WINDOWS_EX_SOURCES GetErrorLabel.c)

endif()

add_library(${PROJECT_NAME}
    STATIC ${WINDOWS_EX_SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}
)

if(MINGW)
    set(GCC_C_WARNINGS
        -Wall
        -Wextra
        -Wpedantic
        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wenum-compare
        -Wfloat-equal
        -Wredundant-decls
        -Wsign-conversion
    )
    set(GCC_CXX_WARNINGS
        ${GCC_C_WARNINGS}
        -Weffc++
        -Wctor-dtor-privacy
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wsign-promo
    )
    target_compile_options(${PROJECT_NAME}
        PUBLIC # enable diagnostic warnings in project
            $<$<COMPILE_LANGUAGE:C>:${GCC_C_WARNINGS}>
            $<$<COMPILE_LANGUAGE:CXX>:${GCC_CXX_WARNINGS}>
    )
endif()

if(WINDOWS_EX_BUILD_TESTS)
    add_subdirectory(Tests)
    enable_testing()
    add_test(WindowsExTests tests/bin/WindowsExTests.exe)
endif()
