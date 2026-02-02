#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <filesystem>
#include <cctype>
#include "lpp_project_parser.h"

namespace fs = std::filesystem;

LppProject LppProjectParser::parse(const std::string& filePath)
{
    std::ifstream in(filePath);
    if (!in.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo de proyecto: " + filePath);
    }

    LppProject project;
    project.projectDir = fs::absolute(fs::path(filePath)).parent_path().string();

    try {
        expect(in, "Proyecto");
        project.name = readString(in);

        while (in >> std::ws && !in.eof()) {
            std::string token = readIdentifier(in);
            if (token == "Version") {
                expect(in, ":");
                project.version = readString(in);
            } else if (token == "Principal") {
                expect(in, ":");
                project.entryPoint = readString(in);
            } else if (token == "Archivos") {
                while (true) {
                    skipWhitespace(in);
                    int peek = in.peek();
                    if (peek == '"') {
                        project.files.push_back(readString(in));
                    } else {
                        std::string endToken = readIdentifier(in);
                        if (endToken == "Fin") {
                            expect(in, "Archivos");
                            break;
                        } else {
                            throw std::runtime_error("Se esperaba nombre de archivo o 'Fin Archivos'");
                        }
                    }
                }
            } else if (token == "Fin") {
                expect(in, "Proyecto");
                break;
            } else if (token.empty()) { 
                break; // EOF
            } else {
                throw std::runtime_error("Token inesperado: " + token);
            }
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Error al analizar archivo de proyecto: " + std::string(e.what()));
    }

    return project;
}

void LppProjectParser::skipWhitespace(std::istream& in) {
    while (isspace(in.peek())) {
        in.get();
    }
}

std::string LppProjectParser::readString(std::istream& in) {
    skipWhitespace(in);
    if (in.get() != '"') {
        throw std::runtime_error("Se esperaba una cadena entre comillas");
    }
    std::string res;
    char c;
    while (in.get(c)) {
        if (c == '"') return res;
        res += c;
    }
    throw std::runtime_error("Cadena no terminada");
}

std::string LppProjectParser::readIdentifier(std::istream& in) {
    skipWhitespace(in);
    std::string res;
    char c;
    while (in.get(c)) {
        if (isalnum(c) || c == '_') {
             res += c;
        } else {
             in.putback(c);
             break;
        }
    }
    return res;
}

void LppProjectParser::expect(std::istream& in, const std::string& expected) {
    skipWhitespace(in);
    std::string token;
    
    if (expected == ":") {
        if (in.peek() == ':') {
            in.get();
            return;
        }
        token = std::string(1, (char)in.peek());
    } else {
        token = readIdentifier(in);
    }
    
    if (token != expected) {
        throw std::runtime_error("Se esperaba '" + expected + "', se encontro '" + token + "'");
    }
}
