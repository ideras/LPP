cmake_minimum_required (VERSION 3.8)
project(lpp_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(__LPP_TESTING__)

set(LPP_SRCDIR "${PROJECT_SOURCE_DIR}/../interp")

add_executable(${PROJECT_NAME} ${LPP_SRCDIR}/lpp_parser.cpp
                               ${LPP_SRCDIR}/lpp_parser.h
                               ${LPP_SRCDIR}/lpp_lexer.cpp
                               ${LPP_SRCDIR}/lpp_lexer.h
                               ${LPP_SRCDIR}/lpp_exception.cpp
                               ${LPP_SRCDIR}/lpp_exception.h
                               ${LPP_SRCDIR}/lpp_runtime.cpp
                               ${LPP_SRCDIR}/lpp_runtime.h
                               ${LPP_SRCDIR}/lpp_ast.cpp
                               ${LPP_SRCDIR}/lpp_ast.h
                               ${LPP_SRCDIR}/lpp_type_info.cpp
                               ${LPP_SRCDIR}/lpp_type_info.h
                               ${LPP_SRCDIR}/lpp_proc_info.cpp
                               ${LPP_SRCDIR}/lpp_proc_info.h
                               ${LPP_SRCDIR}/lpp_variant.cpp
                               ${LPP_SRCDIR}/lpp_variant.h
                               ${LPP_SRCDIR}/lpp_serializer.cpp
                               ${LPP_SRCDIR}/lpp_serializer.h
                               ${LPP_SRCDIR}/lpp_sem_analysis.cpp
                               ${LPP_SRCDIR}/lpp_interp.cpp
                               ${LPP_SRCDIR}/lpp_interp.h
                               ${LPP_SRCDIR}/lpp_filemanager.h
                               ${LPP_SRCDIR}/lpp_symb_table.h
                               ${LPP_SRCDIR}/lpp_terminal.h
                               ${LPP_SRCDIR}/str_util.h
                               serializer_helper.h
                               serializer_helper.cpp
                               lpp_filemanager.cpp
                               lpp_sources.h
                               lpp_terminal.cpp
                               test_serializer.cpp
                               test_file.cpp
                               test_main.cpp
              )

target_include_directories(${PROJECT_NAME} BEFORE PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${LPP_SRCDIR})
