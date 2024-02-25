cmake_minimum_required (VERSION 3.8)
project(lpp_interp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LPP_SRCDIR "${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if (UNIX)
    set(TERMINAL_SRC "lpp_terminal_linux.cpp")
elseif(WIN32)
    set(TERMINAL_SRC "lpp_terminal_win.cpp")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

add_executable(${PROJECT_NAME} lpp_parser.cpp
                               lpp_parser.h
                               lpp_lexer.cpp
                               lpp_lexer.h
                               lpp_exception.cpp
                               lpp_exception.h
                               lpp_runtime.cpp
                               lpp_runtime.h
                               lpp_ast.cpp
                               lpp_ast.h
                               lpp_type_info.cpp
                               lpp_type_info.h
                               lpp_proc_info.cpp
                               lpp_proc_info.h
                               lpp_variant.cpp
                               lpp_variant.h
                               lpp_sem_analysis.cpp
                               lpp_interp.cpp
                               lpp_interp.h
                               lpp_symb_table.h
                               str_util.h
                               ${TERMINAL_SRC}
                               lpp_terminal.cpp
                               lpp_terminal.h
                               lpp_filemanager.h
                               lpp_filemanager.cpp
                               lpp_serializer.h
                               lpp_serializer.cpp
                               lpp_types.h
                               lpp_tokens.h
                               main.cpp
              )



