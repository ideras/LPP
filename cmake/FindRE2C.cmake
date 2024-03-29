#
# This module is designed to find/handle re2c binary
#
# Requirement:
#  CMake >= 2.8.3 (for new version of find_package_handle_standard_args)
#
# The following variables will be defined for your use:
#   - RE2C_EXECUTABLE    : re2c (binary) location
#   - RE2C_VERSION       : complete version of re2c (x.y.z)
#   - RE2C_MAJOR_VERSION : major version of re2c
#   - RE2C_MINOR_VERSION : minor version of re2c
#   - RE2C_PATCH_VERSION : patch version of re2c
#
# The following macro is provided:
#   RE2C_TARGET
#
#  Prototype:
#   RE2C_TARGET([NAME <target>] [INPUT <input>] [OUTPUT <output>] [OPTIONS <options>] [DEPENDS <list of files>])
#
# Argument details:
#   - NAME <target> (mandatory):               cmake target name to build the lexer
#   - INPUT <input> (mandatory):               the input file to give to re2c
#   - OUTPUT <output> (mandatory):             the output file generated by re2c
#   - OPTIONS <options> (optionnal):           command line options to pass to re2c
#   - DEPENDS <file1> ... <file2> (optionnal): a list of files the lexer depends on
#
# How to use:
#   1) Copy this file in the root of your project source directory
#   2) Then, tell CMake to search this non-standard module in your project directory by adding to your CMakeLists.txt:
#        set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
#   3) Finally call find_package(RE2C) once
#
# Here is a complete sample to build an executable:
#
#   set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
#
#   find_package(RE2C REQUIRED) # Note: name is case sensitive
#
#   RE2C_TARGET(NAME foo INPUT foo.re2c OUPUT foo.c OPTIONS "-b" DEPENDS foo.h)
#
#   add_executable(foo foo.c)
#


#=============================================================================
# Copyright (c) 2015, julp
#
# Distributed under the OSI-approved BSD License
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#=============================================================================

include(CMakeParseArguments)
include(FindPackageHandleStandardArgs)

find_program(RE2C_EXECUTABLE NAMES re2c DOC "path to the re2c executable")
mark_as_advanced(RE2C_EXECUTABLE)

if(RE2C_EXECUTABLE)
    execute_process(COMMAND "${RE2C_EXECUTABLE}" --vernum OUTPUT_VARIABLE RE2C_RAW_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
    math(EXPR RE2C_MAJOR_VERSION "${RE2C_RAW_VERSION} / 10000")
    math(EXPR RE2C_MINOR_VERSION "(${RE2C_RAW_VERSION} - ${RE2C_MAJOR_VERSION} * 10000) / 100")
    math(EXPR RE2C_PATCH_VERSION "${RE2C_RAW_VERSION} - ${RE2C_MAJOR_VERSION} * 10000 - ${RE2C_MINOR_VERSION} * 100")
    set(RE2C_VERSION "${RE2C_MAJOR_VERSION}.${RE2C_MINOR_VERSION}.${RE2C_PATCH_VERSION}")

    macro(RE2C_TARGET)
        cmake_parse_arguments(PARSED_ARGS "" "NAME;INPUT;OUTPUT;OPTIONS" "DEPENDS" ${ARGN})

        if(NOT PARSED_ARGS_OUTPUT)
            message(FATAL_ERROR "RE2C_TARGET expect an output filename")
        endif(NOT PARSED_ARGS_OUTPUT)
        if(NOT PARSED_ARGS_INPUT)
            message(FATAL_ERROR "RE2C_TARGET expect an input filename")
        endif(NOT PARSED_ARGS_INPUT)
        if(NOT PARSED_ARGS_NAME)
            message(FATAL_ERROR "RE2C_TARGET expect a target name")
        endif(NOT PARSED_ARGS_NAME)

        add_custom_command(
            OUTPUT ${PARSED_ARGS_OUTPUT}
            COMMAND ${RE2C_EXECUTABLE} ${PARSED_ARGS_OPTIONS} -o ${PARSED_ARGS_OUTPUT} ${PARSED_ARGS_INPUT}
            DEPENDS ${PARSED_ARGS_INPUT} ${PARSED_ARGS_DEPENDS}
            COMMENT "[RE2C][${PARSED_ARGS_NAME}] Building lexer with re2c ${RE2C_VERSION}"
        )
        set(RE2C_${PARSED_ARGS_NAME}_OUTPUT "${PARSED_ARGS_OUTPUT}")
    endmacro(RE2C_TARGET)
endif()

find_package_handle_standard_args(RE2C REQUIRED_VARS RE2C_EXECUTABLE VERSION_VAR RE2C_VERSION)
