cmake_minimum_required(VERSION 3.1)

project(WindowsExTests)

set(CMAKE_CXX_STANDARD 11)

set(CONAN_SYSTEM_INCLUDES ON) # disable warnings from external libraries
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME}
    Main.cpp
    GTest.cpp

    EscapeCommandLineArgA.cpp
    GetErrorLabelA.cpp

    TestDirectoryPath.c

    FileTest.cpp
    ResizeFile.cpp
    WriteFile.cpp
    SetFileSparse.cpp
    GetFileAllocationBlockSize.cpp
    QueryFileAllocatedRanges.cpp
    SetFileZeroData.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/..
)

get_target_property(TARGET_COMPILE_OPTIONS WindowsEx COMPILE_OPTIONS)
target_compile_options(${PROJECT_NAME}
    PUBLIC ${TARGET_COMPILE_OPTIONS}
)

if(MINGW)
    target_link_options(${PROJECT_NAME}
        PRIVATE -static # static link with runtime library
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
