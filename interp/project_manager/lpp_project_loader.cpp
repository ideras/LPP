#include <fstream>
#include <filesystem>
#include <stdexcept>
#include "lpp_project_loader.h"
#include "lpp_lexer.h"
#include "lpp_parser.h"
#include "lpp_exception.h"

namespace fs = std::filesystem;

std::vector<ParsedFile> LppProjectLoader::load(const LppProject& project)
{
    std::vector<ParsedFile> parsedFiles;

    for (const auto& file : project.files) {
        fs::path fullPath = fs::path(project.projectDir) / file;

        std::ifstream in(fullPath);
        if (!in.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo fuente: " + fullPath.string());
        }

        LppLexer lexer(in);
        LppParser parser(lexer);

        try {
            Ast::NodeUPtr ast = parser.parse();
            parsedFiles.emplace_back(file, std::move(ast));
        } catch (LPPException& e) {
            e.setFilename(file);
            throw;
        } catch (const std::exception& e) {
            throw std::runtime_error("Error al analizar archivo '" + file + "': " + e.what());
        }
    }

    return parsedFiles;
}
