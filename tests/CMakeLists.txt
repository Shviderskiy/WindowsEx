cmake_minimum_required(VERSION 2.8)

project(WindowsExTests)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME}
    main.cpp
    EscapeCommandLineArgA.cpp
    GetErrorLabelA.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/..
)

if(MINGW)
    target_link_options(${PROJECT_NAME}
        PRIVATE -static # static link with clib
    )
endif()

if(MSVC)
    set(COMPILER_FLAGS
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS_MINSIZEREL
    )
    foreach(X ${COMPILER_FLAGS})
        # static link with MSVC runtime
        string(REPLACE "/MD" "/MT" ${X} "${${X}}")
        # enable more diagnostic warnings
        string(REPLACE "/W3" "/W4" ${X} "${${X}}")
        set(${X} "${${X}}" PARENT_SCOPE)
    endforeach()
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${CONAN_LIBS} WindowsEx
)
