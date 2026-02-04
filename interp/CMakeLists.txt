cmake_minimum_required (VERSION 3.8)
project(lpp_interp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LPP_SRCDIR "${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/ast)
include_directories(${PROJECT_SOURCE_DIR}/parser)
include_directories(${PROJECT_SOURCE_DIR}/semantic)
include_directories(${PROJECT_SOURCE_DIR}/runtime)
include_directories(${PROJECT_SOURCE_DIR}/runtime/variant)
include_directories(${PROJECT_SOURCE_DIR}/io)
include_directories(${PROJECT_SOURCE_DIR}/utils)
include_directories(${PROJECT_SOURCE_DIR}/project_manager)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if (UNIX)
    set(TERMINAL_SRC "lpp_terminal_linux.cpp")
elseif(WIN32)
    set(TERMINAL_SRC "lpp_terminal_win.cpp")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

add_executable(${PROJECT_NAME} parser/lpp_parser.cpp
                               parser/lpp_parser.h
                               parser/lpp_lexer.cpp
                               parser/lpp_lexer.h
                               runtime/lpp_exception.cpp
                               runtime/lpp_exception.h
                               runtime/lpp_runtime.cpp
                               runtime/lpp_runtime.h
                               ast/lpp_ast.cpp
                               ast/lpp_ast.h
                               semantic/lpp_type_info.cpp
                               semantic/lpp_type_info.h
                               semantic/lpp_proc_info.cpp
                               semantic/lpp_proc_info.h
                               runtime/variant/lpp_variant.cpp
                               runtime/variant/lpp_variant.h
                               runtime/variant/lpp_object.h
                               runtime/variant/lpp_string.h
                               runtime/variant/lpp_array.h
                               runtime/variant/lpp_array.cpp
                               runtime/variant/lpp_record.h
                               runtime/variant/lpp_record.cpp
                               semantic/lpp_semantics.cpp
                               semantic/lpp_semantics.h
                               runtime/lpp_interp.cpp
                               runtime/lpp_interp.h
                               semantic/lpp_symb_table.h
                               utils/str_util.h
                               io/${TERMINAL_SRC}
                               io/lpp_terminal.cpp
                               io/lpp_terminal.h
                               io/lpp_filemanager.h
                               io/lpp_filemanager.cpp
                               io/lpp_serializer.h
                               io/lpp_serializer.cpp
                               utils/lpp_types.h
                               ast/lpp_tokens.h
                               project_manager/lpp_project.h
                               project_manager/lpp_project.cpp
                               project_manager/lpp_project_parser.h
                               project_manager/lpp_project_parser.cpp
                               project_manager/lpp_project_loader.h
                               project_manager/lpp_project_loader.cpp
                               main.cpp
              )