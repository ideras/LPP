cmake_minimum_required(VERSION 3.8)
project(LPP VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build options
option(BUILD_INTERPRETER "Build the LPP interpreter" ON)
option(BUILD_IDE "Build the LPP IDE (requires Qt)" ON)
option(BUILD_TESTS "Build the unit tests" ON)

# Find Qt for IDE (only if needed)
if(BUILD_IDE)
    find_package(QT NAMES Qt6 Qt5 QUIET COMPONENTS Widgets)
    if(NOT QT_FOUND)
        message(WARNING "Qt not found. Disabling IDE build.")
        set(BUILD_IDE OFF)
    else()
        find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
    endif()
endif()

# Find re2c for IDE (only if needed)
if(BUILD_IDE)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
    find_package(RE2C QUIET)
    if(NOT RE2C_FOUND)
        message(WARNING "re2c not found. Disabling IDE build.")
        set(BUILD_IDE OFF)
    endif()
endif()

# Build interpreter
if(BUILD_INTERPRETER)
    message(STATUS "Building LPP Interpreter")
    add_subdirectory(interp)
endif()

# Build IDE
if(BUILD_IDE)
    message(STATUS "Building LPP IDE")
    add_subdirectory(ide)
endif()

# Build tests
if(BUILD_TESTS)
    message(STATUS "Building LPP Tests")
    add_subdirectory(test_interp)
endif()

# Print build summary
message(STATUS "")
message(STATUS "=== LPP Build Configuration ===")
message(STATUS "Interpreter: ${BUILD_INTERPRETER}")
message(STATUS "IDE:         ${BUILD_IDE}")
message(STATUS "Tests:       ${BUILD_TESTS}")
if(BUILD_IDE AND QT_FOUND)
    message(STATUS "Qt Version:  ${QT_VERSION_MAJOR}")
endif()
message(STATUS "===============================")
message(STATUS "")

# Custom targets for convenience
if(BUILD_INTERPRETER AND BUILD_IDE AND BUILD_TESTS)
    # Create a target to build everything
    add_custom_target(all_components 
        DEPENDS lpp_interp lpp_ide lpp_test
        COMMENT "Building all LPP components"
    )
endif()

# Installation rules
if(BUILD_INTERPRETER)
    install(TARGETS lpp_interp 
        RUNTIME DESTINATION bin
        COMPONENT interpreter
    )
endif()

if(BUILD_IDE)
    install(TARGETS lpp_ide
        RUNTIME DESTINATION bin
        COMPONENT ide
    )
endif()

# Create a script to copy interpreter to IDE directory (for convenience)
if(BUILD_INTERPRETER AND BUILD_IDE)
    add_custom_target(setup_ide
        COMMAND ${CMAKE_COMMAND} -E copy 
            $<TARGET_FILE:lpp_interp> 
            $<TARGET_FILE_DIR:lpp_ide>/
        DEPENDS lpp_interp lpp_ide
        COMMENT "Copying interpreter to IDE directory"
    )
endif()