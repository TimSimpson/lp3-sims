# *********************************************************************
# LP3_SIMS
#       Simplifies writing game "lp3-sims.cpp" files.
# *********************************************************************
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)

if(NOT DEFINED PROJECT_NAME)
    set(NOT_SUBPROJECT ON)
endif()

project(lp3-sims CXX)

include(CTest)
include(CMakePackageConfigHelpers)

# Allow user to ask explicitly to build tests
option(LP3_SIMS_Build_Tests "Build tests when BUILD_TESTING is enabled."
       ${NOT_SUBPROJECT})

add_library(
    sims
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lp3/sims.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lp3/sims/Clock.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lp3/sims/config.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lp3/sims/coroutine.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lp3/sims/dispatcher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lp3/sims/EventSimulator.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lp3/sims/qroutines.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Clock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dispatcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/EventSimulator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/qroutines.cpp)
set_target_properties(sims PROPERTIES OUTPUT_NAME "lp3-sims")

target_compile_definitions(sims PUBLIC "$<$<CONFIG:DEBUG>:LP3_SIMS_DEBUG>")


# Mandate the use of at least C++17 by everything that uses this
target_compile_features(sims PUBLIC cxx_std_17)

target_include_directories(
    sims
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
           $<INSTALL_INTERFACE:include>
    PRIVATE src)

# if(BUILD_SHARED_LIBS)
#     target_compile_definitions(
#         sims
#         PUBLIC LP3_SIMS_API_DYNAMIC
#         PRIVATE LP3_SIMS_API_CREATE)
#     if(MSVC)
#         target_compile_options(sims PRIVATE /wd4251 /wd4275)
#     endif()
# endif()

# *********************************************************************
# Tests and Drivers / Demos
# *********************************************************************

if(BUILD_TESTING AND LP3_SIMS_Build_Tests)
    find_package(Catch2 REQUIRED)
    find_package(fmt REQUIRED)

    function(make_test name)
        add_executable(${name}
                   ${CMAKE_CURRENT_SOURCE_DIR}/tests/${name}.cpp)
        target_link_libraries(${name} sims fmt::fmt Catch2::Catch2)
        if("${CMAKE_SYSTEM_NAME}" MATCHES "Emscripten")
            add_test(NAME "test_${name}"
                     COMMAND node $<TARGET_FILE:${name}>)
        else()
            add_test(NAME "test_${name}" COMMAND ${name})
        endif()
        if(LP3_SETUP_FOLDERS)
            set_target_properties(${name} PROPERTIES FOLDER lp3-sims)
        endif()
    endfunction()

    make_test(coroutine_tests)
    make_test(dispatcher_tests)
    make_test(EventSimulatorTests)
    make_test(qroutines_tests)
endif()

# *********************************************************************
# Package / Install Stuff
# *********************************************************************

install(DIRECTORY include/ DESTINATION include)

add_library(lp3::sims ALIAS sims)

install(
    TARGETS sims
    EXPORT lp3-sims-targets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES
    DESTINATION include)

install(
    EXPORT lp3-sims-targets
    FILE lp3-sims-targets.cmake
    NAMESPACE lp3::
    DESTINATION lib/cmake/lp3-sims)

file(
    WRITE "${PROJECT_BINARY_DIR}/lp3-simsConfig.cmake"
    "
include(CMakeFindDependencyMacro)
include(\"\${CMAKE_CURRENT_LIST_DIR}/lp3-sims-targets.cmake\")
")

write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/lp3-simsConfigVersion.cmake"
    VERSION 1.0.1
    COMPATIBILITY AnyNewerVersion)

install(FILES "${PROJECT_BINARY_DIR}/lp3-simsConfig.cmake"
              "${PROJECT_BINARY_DIR}/lp3-simsConfigVersion.cmake"
        DESTINATION lib/cmake/lp3-sims)
