#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>
#include "lpp_interp.h"
#include "lpp_exception.h"
#include "project_manager/lpp_project_parser.h"

namespace fs = std::filesystem;

void reportError(const LPPException& ex) {
    if (!ex.getFilename().empty()) {
        std::cerr << "Archivo '" << ex.getFilename() << "', ";
    }
    std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
}

void usage(const char *progname) {
    std::cerr << "Uso: " << progname << " [ --pause ] --action (run | compile) <programa fuente de LPP>\n"
              << "Ejemplo:  " << progname << " --action run holamundo.lpp\n";
}

int main(int argc, char *argv[])
{
    if (argc < 4) {
        usage(argv[0]);
        return 1;
    }

    const char *prg_name = argv[0];

    argc--;
    argv++;
    int action = 0;
    bool pause = false;
    std::string filepath;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--action") == 0) {
            if (i < argc - 1) {
                if (strcmp(argv[i+1], "compile") == 0)
                    action = 0;
                else if (strcmp(argv[i+1], "run") == 0)
                    action = 1;
                else {
                    usage(prg_name);
                    return 1;
                }

                i++;
            } else {
                usage(prg_name);
                return 1;
            }
        } else if (strcmp(argv[i], "--pause") == 0) {
            pause = true;
        } else {
            filepath = argv[i];
        }
    }

    int ret_code = 0;

    try {
        LppProject project;

        if (fs::path(filepath).extension() == ".lppprj") {
            project = LppProjectParser::parse(filepath);
        } else {
            project = LppProject::fromSingleFile(filepath);
        }

        LppInterp interp;

        if (action == 0) {
            interp.semanticAnalysis(project);
            std::cout << "Programa compila con exito.\n";
        } else {
            interp.execute(project);
        }
    } catch (const LPPException& ex) {
        reportError(ex);
        ret_code = 3;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        ret_code = 4;
    }

    if (pause) {
        std::string s;

        std::cout << std::flush << "\nPresione ENTER para terminar\n" << std::flush;
        std::getline(std::cin, s);
    }

    return ret_code;
}
