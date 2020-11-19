cmake_minimum_required(VERSION 3.16)

set(FULL_VERSION "1.14.0")

string(REGEX MATCH "^[0-9]+.[0-9]+.[0-9]+" cmake_compat_version ${FULL_VERSION})
project(gpgme VERSION ${cmake_compat_version})

set(VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(VERSION_MICRO ${PROJECT_VERSION_PATCH})

set(PACKAGE_STRING "${CMAKE_PROJECT_NAME} ${FULL_VERSION}")
set(PACKAGE_VERSION "${FULL_VERSION}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    find_file(GPGME_HEADER gpgme.h REQUIRED)
    get_filename_component(GPGME_INCLUDE_DIR ${GPGME_HEADER} DIRECTORY)
    find_library(GPGME_LIB gpgme.lib REQUIRED)

    find_file(ASSUAN_HEADER assuan.h REQUIRED)
    get_filename_component(ASSUAN_INCLUDE_DIR ${ASSUAN_HEADER} DIRECTORY)
    find_library(ASSUAN_LIB assuan.lib REQUIRED)

    find_file(GPG_ERROR_HEADER gpg-error.h REQUIRED)
    get_filename_component(GPG_ERROR_INCLUDE_DIR ${GPG_ERROR_HEADER} DIRECTORY)
    find_library(GPG_ERROR_LIB gpg-error.lib REQUIRED)


    set(GPGME_INCLUDE_DIRS ${GPGME_INCLUDE_DIR} ${ASSUAN_INCLUDE_DIR} ${GPG_ERROR_INCLUDE_DIR})
    set(GPGME_LIBRARIES ${GPGME_LIB} ${ASSUAN_LIB} ${GPG_ERROR_LIB})
    set(GPGME_FOUND ON)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GPGME REQUIRED gpgme)
endif()

include(CMakeDependentOption)
include(CheckIncludeFile)
include(CheckFunctionExists)
include(GNUInstallDirs)

set(GPGME_CONFIG_AVAIL_LANG "")

option(WITH_CPP "Build C++ bindings" OFF)
if (WITH_CPP)
    set(GPGME_CONFIG_AVAIL_LANG "${GPGME_CONFIG_AVAIL_LANG} cpp")
endif()

cmake_dependent_option(WITH_QT "Build Qt bindings" OFF "WITH_CPP" OFF)

if (WITH_QT)
    find_package(Qt5 COMPONENTS Core)
    set(GPGME_CONFIG_AVAIL_LANG "${GPGME_CONFIG_AVAIL_LANG} qt")
endif()

function(parse_lt name)
    file(READ "${CMAKE_SOURCE_DIR}/configure.ac" configure_ac)
    string(REGEX MATCH "${name}_LT_CURRENT=([0-9]+)" _ ${configure_ac})
    set(${name}_LT_CURRENT ${CMAKE_MATCH_1} PARENT_SCOPE)
    string(REGEX MATCH "${name}_LT_AGE=([0-9]+)" _ ${configure_ac})
    set(${name}_LT_AGE ${CMAKE_MATCH_1} PARENT_SCOPE)
    string(REGEX MATCH "${name}_LT_REVISION=([0-9]+)" _ ${configure_ac})
    set(${name}_LT_REVISION ${CMAKE_MATCH_1} PARENT_SCOPE)
endfunction()

add_subdirectory(lang)
#add_subdirectory(src)
