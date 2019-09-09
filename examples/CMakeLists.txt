cmake_minimum_required(VERSION 2.8)

project(WindowsExExample)

add_executable(${PROJECT_NAME}
    main.c
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
    )
    foreach(X ${COMPILER_FLAGS})
        # static link with MSVC runtime
        string(REPLACE "/MD" "/MT" ${X} "${${X}}")
        # enable more diagnostic warnings
        string(REPLACE "/W3" "/W4" ${X} "${${X}}")
    endforeach()

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}"
        PARENT_SCOPE
    )
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}"
        PARENT_SCOPE
    )
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}"
        PARENT_SCOPE
    )
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO}"
        PARENT_SCOPE
    )
    set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL}"
        PARENT_SCOPE
    )
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE WindowsEx
)
