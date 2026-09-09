cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=maybe-uninitialized")

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" OFF)

project(print)

include(CPackConfig.cmake)

set(PRINT_VERSION_MAJOR 0)
set(PRINT_VERSION_MINOR 1)
set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_TWEAK 0)

set(PRINT_VERSION
  ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})

set(PRINT_VERSION_STRING "v${PRINT_VERSION}")

if(BUILD_TESTS)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

add_library(print STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp
)

target_include_directories(print PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(BUILD_EXAMPLES)

    file(GLOB EXAMPLE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp"
    )

    foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})

        get_filename_component(
            EXAMPLE_NAME
            ${EXAMPLE_SOURCE}
            NAME_WE
        )

        add_executable(
            ${EXAMPLE_NAME}
            ${EXAMPLE_SOURCE}
        )

        target_link_libraries(
            ${EXAMPLE_NAME}
            print
        )

        install(
            TARGETS ${EXAMPLE_NAME}
            RUNTIME DESTINATION bin
        )

    endforeach()

endif()

install(
    TARGETS print
    EXPORT print-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
)

install(
    EXPORT print-config
    DESTINATION cmake
)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)
add_subdirectory(hello_world_application)
add_subdirectory(solver_application)
add_subdirectory(banking)

if(BUILD_TESTS)

    enable_testing()

    add_subdirectory(third-party/gtest)

    file(GLOB ${PROJECT_NAME}_TEST_SOURCES
        tests/*.cpp
    )

    add_executable(
        check
        ${${PROJECT_NAME}_TEST_SOURCES}
    )

    target_link_libraries(
        check
        ${PROJECT_NAME}
        gtest_main
    )

    add_test(
        NAME check
        COMMAND check
    )

    add_executable(
        banking_tests
        banking/tests/test_account.cpp
        banking/tests/test_transaction.cpp
    )

    target_include_directories(
        banking_tests PUBLIC
        banking
    )

    target_link_libraries(
        banking_tests
        banking
        gtest
        gtest_main
        gmock
        pthread
    )

    add_test(
        NAME banking_tests
        COMMAND banking_tests
    )

endif()

