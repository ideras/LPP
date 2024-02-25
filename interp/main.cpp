#include <iostream>
#include <fstream>
#include <cstring>
#include "lpp_parser.h"
#include "lpp_lexer.h"
#include "lpp_interp.h"
#include "lpp_exception.h"

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

    std::ifstream in(filepath, std::ios::binary | std::ios::in);

    if (!in.is_open()) {
        std::cerr << "No se puedo abrir el archivo '" << filepath << " '\n";
        return 2; 
    }

    LppLexer lexer(in);
    LppParser parser(lexer);

    try {
        Ast::NodeUPtr prg = parser.parse();

        LppInterp interp;

        if (action == 0) {
            interp.semAnalysis(prg.get());
            std::cout << "Programa compila con exito.\n";
        } else {
            interp.exec(prg.get());
        }
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        in.close();
        return 3;
    }
    if (pause) {
        std::string s;

        std::cout << std::flush << "\nPresione ENTER para terminar\n" << std::flush;
        std::getline(std::cin, s);
    }

    in.close();
    return 0;
}
