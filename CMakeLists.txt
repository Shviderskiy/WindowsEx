cmake_minimum_required(VERSION 2.8)

project(WindowsEx)

set(WINDOWS_EX_SOURCES
    EscapeCommandLineArg.c
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

if(WINDOWS_EX_BUILD_TESTS)
    add_subdirectory(tests)
    enable_testing()
    add_test(WindowsExTests tests/bin/WindowsExTests.exe)
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}
)

if(MINGW)
    target_compile_options(${PROJECT_NAME}
        PRIVATE # enable diagnostic warnings in project
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
endif()
