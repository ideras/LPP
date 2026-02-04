cmake_minimum_required (VERSION 3.8)
project(lpp_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(__LPP_TESTING__)

set(LPP_SRCDIR "${PROJECT_SOURCE_DIR}/../interp")

add_executable(${PROJECT_NAME} ${LPP_SRCDIR}/parser/lpp_parser.cpp
                               ${LPP_SRCDIR}/parser/lpp_parser.h
                               ${LPP_SRCDIR}/parser/lpp_lexer.cpp
                               ${LPP_SRCDIR}/parser/lpp_lexer.h
                               ${LPP_SRCDIR}/runtime/lpp_exception.cpp
                               ${LPP_SRCDIR}/runtime/lpp_exception.h
                               ${LPP_SRCDIR}/runtime/lpp_runtime.cpp
                               ${LPP_SRCDIR}/runtime/lpp_runtime.h
                               ${LPP_SRCDIR}/ast/lpp_ast.cpp
                               ${LPP_SRCDIR}/ast/lpp_ast.h
                               ${LPP_SRCDIR}/semantic/lpp_type_info.cpp
                               ${LPP_SRCDIR}/semantic/lpp_type_info.h
                               ${LPP_SRCDIR}/semantic/lpp_proc_info.cpp
                               ${LPP_SRCDIR}/semantic/lpp_proc_info.h
                               ${LPP_SRCDIR}/runtime/variant/lpp_variant.cpp
                               ${LPP_SRCDIR}/runtime/variant/lpp_variant.h
                               ${LPP_SRCDIR}/runtime/variant/lpp_object.h
                               ${LPP_SRCDIR}/runtime/variant/lpp_string.h
                               ${LPP_SRCDIR}/runtime/variant/lpp_array.h
                               ${LPP_SRCDIR}/runtime/variant/lpp_array.cpp
                               ${LPP_SRCDIR}/runtime/variant/lpp_record.h
                               ${LPP_SRCDIR}/runtime/variant/lpp_record.cpp
                               ${LPP_SRCDIR}/io/lpp_serializer.cpp
                               ${LPP_SRCDIR}/io/lpp_serializer.h
                               ${LPP_SRCDIR}/semantic/lpp_semantics.cpp
                               ${LPP_SRCDIR}/runtime/lpp_interp.cpp
                               ${LPP_SRCDIR}/runtime/lpp_interp.h
                               ${LPP_SRCDIR}/semantic/lpp_symb_table.h
                               ${LPP_SRCDIR}/utils/str_util.h
                               ${LPP_SRCDIR}/project_manager/lpp_project.cpp
                               ${LPP_SRCDIR}/project_manager/lpp_project_parser.cpp
                               ${LPP_SRCDIR}/project_manager/lpp_project_loader.cpp
                               serializer_helper.h
                               serializer_helper.cpp
                               lpp_filemanager.cpp
                               lpp_sources.h
                               lpp_terminal.cpp
                               test_serializer.cpp
                               test_file.cpp
                               test_initializers.cpp
                               test_project.cpp
                               test_multi_file.cpp
                               test_main.cpp
              )

target_include_directories(${PROJECT_NAME} BEFORE PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${LPP_SRCDIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${LPP_SRCDIR}/ast)
target_include_directories(${PROJECT_NAME} PRIVATE ${LPP_SRCDIR}/parser)
target_include_directories(${PROJECT_NAME} PRIVATE ${LPP_SRCDIR}/semantic)
target_include_directories(${PROJECT_NAME} PRIVATE ${LPP_SRCDIR}/runtime)
target_include_directories(${PROJECT_NAME} PRIVATE ${LPP_SRCDIR}/runtime/variant)
target_include_directories(${PROJECT_NAME} PRIVATE ${LPP_SRCDIR}/io)
target_include_directories(${PROJECT_NAME} PRIVATE ${LPP_SRCDIR}/utils)
target_include_directories(${PROJECT_NAME} PRIVATE ${LPP_SRCDIR}/project_manager)
