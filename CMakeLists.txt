cmake_minimum_required(VERSION 3.10)
project(ActiveMqTraining C CXX)
SET(CMAKE_CXX_STANDARD 11)

option(BUILD_EXAMPLES "Build Example applications" TRUE)
option(BUILD_TESTS "Build Test applications" FALSE)
option(CMAKE_VERBOSE_MAKEFILE "Use verbose output" TRUE)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(COTERIZE_BUILD FALSE)
if(DEFINED COTERIZE_BUILD)
    set(COTIRE_DEBUG TRUE)
    set(COTIRE_VERBOSE TRUE)
    set(COTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES 2)
    include(cotire)
endif()

if(BUILD_TESTS)
    find_package(cppunit)
endif()
find_package(Expat 2.2.0 REQUIRED)
find_package(APR REQUIRED)
find_package(Threads REQUIRED)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/security/ServiceRegistry.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/util/concurrent/windows/*.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemqES
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/io/*.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/net/*.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/nio/*.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/security/provider/*.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/security/windows/*.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/security/Engine.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/security/SecurityRuntime.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cp-cpp/src/main/decaf/internal/util/concurrent/ExecutorsSupport.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/util/concurrent/SynchronizableImpl.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/util/concurrent/Threading.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/util/concurrent/ThreadLocalImpl.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/util/zip/*.c
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/util/ByteArrayAdapter.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/util/GenericResource.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/util/HexStringParser.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/util/Resource.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/util/ResourceLifecycleManager.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/util/StringUtils.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/util/TimerTaskHeap.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/AprPool.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/internal/DecafRuntime.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/io/*.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/lang/*.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/net/*.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/nio/*.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/security/*.cpp
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf/util/*.cpp
        )

file(GLOB_RECURSE ActiveMq_SOURCES
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/activemq/*.cpp
        )
file(GLOB_RECURSE Cms_SOURCES
        ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/cms/*.cpp
        )

######################  LIBRARY SECTION  ###################################

set(DECAF_UTIL_PATH ${CMAKE_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main)
add_library(Decaf STATIC ${SOURCES} ${ActiveMq_SOURCES} ${Cms_SOURCES})
target_include_directories(Decaf
    PRIVATE
        ${APR_INCLUDE_DIR}
        ${DECAF_UTIL_PATH})

if (NOT CMAKE_GENERATOR MATCHES "NMake Makefiles" AND MSVC)
    target_compile_options(Decaf PRIVATE /MP16 /wd4101)
    message(INFO " Enabling parrallel jobs on this project")
elseif(MSVC)
    target_compile_options(Decaf PRIVATE /wd4101 /wd4005)
endif()

target_link_libraries(Decaf PRIVATE ${APR_LIBRARIES})
if(DEFINED COTERIZE_BUILD)
    set_target_properties(Decaf PROPERTIES
        COTIRE_ADD_UNITY_BUILD FALSE
        COTIRE_PREFIX_HEADER_INCLUDE_PATH ${APR_INCLUDE_DIR})
    cotire(Decaf)
endif()

######################  EXAMPLES SECTION  ###################################
add_subdirectory(external/activemq-cpp/activemq-cpp/src/examples)

########### TEST SECTION ##################
if (cppunit_FOUND AND BUILD_TESTS)
    SET(TEST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/test)
    file(GLOB_RECURSE TESTS_SRCS
            ${TEST_PATH}/activemq/*.cpp
            ${TEST_PATH}/decaf/*.cpp)
    add_executable(ActiveMQTest ${TEST_PATH}/main.cpp ${TEST_PATH}/testRegistry.cpp ${TEST_PATH}/util/teamcity/TeamCityProgressListener.cpp ${TESTS_SRCS})
    target_link_libraries(ActiveMQTest PRIVATE ${APR_LIBRARIES} Decaf cppunit::cppunit)
    target_include_directories(ActiveMQTest PRIVATE ${TEST_PATH})
    target_compile_options(ActiveMQTest PUBLIC /wd4101)
endif ()

########### INSTALLATION SECTION ##################

set(include_install_dir "include")
set(config_install_dir "lib/cmake")

set(project_config "${CMAKE_CURRENT_BINARY_DIR}/generated/ActiveMQConfig.cmake")
set(targets_export_name "ActiveMQTargets")

set(namespace "${PROJECT_NAME}::")

configure_file("${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in" "${project_config}" @ONLY)

# Install target (will install the library to specified CMAKE_INSTALL_PREFIX variable)
install(
        TARGETS Decaf
        EXPORT ${targets_export_name}
        ARCHIVE DESTINATION lib/
        LIBRARY DESTINATION lib/
        RUNTIME DESTINATION lib/
        INCLUDES DESTINATION ${include_install_dir})

install(
        DIRECTORY "${PROJECT_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/activemq" "${PROJECT_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/decaf" "${PROJECT_SOURCE_DIR}/external/activemq-cpp/activemq-cpp/src/main/cms"
        DESTINATION ${include_install_dir}
        FILES_MATCHING PATTERN "*.*h")

install(
        FILES "${project_config}"
        DESTINATION "${config_install_dir}")

install(
        EXPORT "${targets_export_name}"
        NAMESPACE "${namespace}"
        DESTINATION "${config_install_dir}")

add_custom_target(install_${PROJECT_NAME}
        $(MAKE) install
        DEPENDS Decaf
        COMMENT "Installing ${PROJECT_NAME}")

##########################  STATIC ANALYSIS SECTION ##########################
include(CppcheckTargets)
if (CPPCHECK_FOUND AND CMAKE_BUILD_TYPE MATCHES "Debug")
    message(INFO " Found CppCheck version: ${CPPCHECK_VERSION} ")
    add_cppcheck(Decaf POSSIBLE_ERROR)
endif ()


