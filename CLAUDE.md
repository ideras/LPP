# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

LPP (Lenguaje de Programación para Principiantes) is a Spanish-language programming language interpreter with an integrated development environment (IDE). The project consists of three main components:

- **interp/**: Core interpreter written in C++17
- **ide/**: Qt-based IDE for editing and running LPP programs  
- **test_interp/**: Unit tests for the interpreter using doctest

## Build Commands

### Unified Build (Recommended)
Build all components at once:
```bash
mkdir build && cd build
cmake ..
cmake --build . --parallel 4
```

### Selective Build Options
Control which components to build:
```bash
# Build only interpreter
cmake .. -DBUILD_IDE=OFF -DBUILD_TESTS=OFF
cmake --build .

# Build only tests
cmake .. -DBUILD_INTERPRETER=OFF -DBUILD_IDE=OFF
cmake --build .

# Build interpreter and tests (no IDE)
cmake .. -DBUILD_IDE=OFF
cmake --build .
```

### Individual Component Build (Legacy)
```bash
# Interpreter only
mkdir build-interp && cd build-interp
cmake ../interp && cmake --build .

# IDE only (requires Qt and re2c)
mkdir build-ide && cd build-ide
cmake ../ide && cmake --build .

# Tests only
mkdir build-test && cd build-test
cmake ../test_interp && cmake --build .
```

### Convenience Targets
```bash
# Copy interpreter to IDE directory (after building both)
cmake --build . --target setup_ide

# Run tests (from build directory)
./test_interp/lpp_test      # Linux/macOS
.\test_interp\lpp_test.exe  # Windows
```

## Development Requirements

- CMake
- re2c (for lexer generation)
- C++ compiler with C++17 support
- Qt 6.2 (for IDE only)

## Architecture

### Interpreter Core (`interp/`)
- **LppLexer**: Tokenizes LPP source code
- **LppParser**: Recursive descent parser that builds AST
- **LppInterp**: Main interpreter class with semantic analysis and execution
- **Ast namespace**: Abstract syntax tree node definitions
- **LppRuntime**: Built-in function implementations
- **Terminal**: Cross-platform terminal I/O (separate Linux/Windows implementations)
- **LppFileManager**: File operations for LPP programs

### IDE (`ide/`)
- **MainWindow**: Main Qt application window
- **LPPHighlighter**: Syntax highlighting using re2c-generated lexer
- **LppInterpCtrl**: Controls interpreter process execution
- **LppEditor**: Custom text editor widget

### Key Data Structures
- **LppVariant**: Polymorphic value type supporting integers, reals, chars, booleans, strings, and arrays
- **TypeInfo**: Type system information for semantic analysis
- **SymbolTable**: Template-based symbol table for variables, types, and procedures

## Usage

### Running LPP Programs
```bash
./lpp_interp --action run programa.lpp
./lpp_interp --action compile programa.lpp
```

### IDE Setup
Copy the interpreter executable to the same directory as the IDE:
```bash
cp build-interp/lpp_interp build-ide/
cd build-ide && ./lpp_ide
```

## Testing

The project uses doctest for unit testing. Tests focus on:
- Serialization functionality
- File manager operations
- Core interpreter components

Run tests with `./lpp_test` after building the test target.

## Platform Support

The codebase supports Linux and Windows with platform-specific implementations for:
- Terminal I/O (`lpp_terminal_linux.cpp` / `lpp_terminal_win.cpp`)
- Interpreter control (`lpp_interp_ctrl_linux.cpp` / `lpp_interp_ctrl_win.cpp`)