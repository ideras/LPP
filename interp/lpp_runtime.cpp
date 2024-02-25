#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <random>

#ifdef _WIN32
#include <windows.h>
#else
#include <thread>
#endif

#include "lpp_terminal.h"
#include "lpp_filemanager.h"
#include "str_util.h"
#include "lpp_runtime.h"

#define RUNTIME_FUNCTION(fname) auto fname = [this](std::vector<LppVariant>& args) -> LppVariant
#define REGISTER_RUNTIME_FUNCTION(fname) funcs.emplace(#fname, fname)

bool LppRuntime::contains(const std::string& fname) const
{
    std::string lfname = str::lower(fname);

    return funcs.find(lfname) != funcs.end(); 
}

void LppRuntime::init()
{
    RUNTIME_FUNCTION(nueva_linea) {
        std::cout << '\n';
        return LppVariant::Empty;
    };

    RUNTIME_FUNCTION(entero_a_cadena) {
        Lpp::Int num = args[0].toInt();

        return std::to_string(num);
    };

    RUNTIME_FUNCTION(real_a_cadena) {
        Lpp::Real num = args[0].toReal();
        Lpp::Int prec = args[1].toInt() + 1;
        std::ostringstream ss;

        ss << std::setprecision(prec) << num;
        return ss.str();
    };

    RUNTIME_FUNCTION(longitud) {
        const std::string& str = args[0].stringCRef();
        
        return static_cast<Lpp::Int>(str.length());
    };

    RUNTIME_FUNCTION(valor_ascii) {
        return static_cast<Lpp::Int>(args[0].toChar());
    };

    RUNTIME_FUNCTION(caracter_ascii) {
        return static_cast<Lpp::Char>(args[0].toInt());
    };

    RUNTIME_FUNCTION(inicializar_aleatorio) {
        long seed = std::chrono::steady_clock::now().time_since_epoch().count();
        randEng.seed(seed);

        return LppVariant::Empty;
    };

    RUNTIME_FUNCTION(aleatorio) {
        return randDist(randEng);
    };

    RUNTIME_FUNCTION(limpiar_pantalla) {
        term.clear();

        return LppVariant::Empty;
    };

    RUNTIME_FUNCTION(posicionar_cursor) {
        int col = args[0].toInt() % 80;
        int row = args[1].toInt() % 25;

        term.setCursorPos({row, col});
        return LppVariant::Empty;
    };

    RUNTIME_FUNCTION(color_fondo) {
        int icolor = args[0].toInt();
        Color color = static_cast<Color>(icolor % 16);

        term.setBackColor(color);
        return LppVariant::Empty;
    };

    RUNTIME_FUNCTION(color_texto) {
        int icolor = args[0].toInt();
        Color color = static_cast<Color>(icolor % 16);

        term.setTextColor(color);
        return LppVariant::Empty;
    };

    RUNTIME_FUNCTION(obtener_caracter) {
        int key = term.getch();

        return static_cast<Lpp::Char>(key);
    };

    RUNTIME_FUNCTION(obtener_tecla) {
        return term.getch();
    };

    RUNTIME_FUNCTION(tecla_presionada) {
        return term.kbhit();
    };

    RUNTIME_FUNCTION(pausa) {
        int ms = args[0].toInt();

    #ifdef _WIN32
        Sleep(ms);
    #else
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    #endif

        return LppVariant::Empty;
    };

    RUNTIME_FUNCTION(fda) {
        int fh = args[0].toInt();

        return file_mgr.atEof(fh);
    };

    RUNTIME_FUNCTION(ir_a_inicio) {
        int fh = args[0].toInt();

        return file_mgr.seekStart(fh);
    };

    RUNTIME_FUNCTION(ir_a_fin) {
        int fh = args[0].toInt();

        return file_mgr.seekEnd(fh);
    };

    RUNTIME_FUNCTION(ir_a) {
        int fh = args[0].toInt();
        int pos = args[1].toInt();

        return file_mgr.seek(fh, pos);
    };

    RUNTIME_FUNCTION(posicion_actual) {
        int fh = args[0].toInt();

        return file_mgr.filePos(fh);
    };

    REGISTER_RUNTIME_FUNCTION(limpiar_pantalla);
    REGISTER_RUNTIME_FUNCTION(posicionar_cursor);
    REGISTER_RUNTIME_FUNCTION(color_fondo);
    REGISTER_RUNTIME_FUNCTION(color_texto);
    REGISTER_RUNTIME_FUNCTION(obtener_caracter);
    REGISTER_RUNTIME_FUNCTION(obtener_tecla);
    REGISTER_RUNTIME_FUNCTION(tecla_presionada);
    REGISTER_RUNTIME_FUNCTION(pausa);
    REGISTER_RUNTIME_FUNCTION(nueva_linea) ;
    REGISTER_RUNTIME_FUNCTION(entero_a_cadena);
    REGISTER_RUNTIME_FUNCTION(real_a_cadena);
    REGISTER_RUNTIME_FUNCTION(longitud);
    REGISTER_RUNTIME_FUNCTION(valor_ascii);
    REGISTER_RUNTIME_FUNCTION(caracter_ascii);
    REGISTER_RUNTIME_FUNCTION(inicializar_aleatorio);
    REGISTER_RUNTIME_FUNCTION(aleatorio);
    REGISTER_RUNTIME_FUNCTION(fda);
    REGISTER_RUNTIME_FUNCTION(ir_a_inicio);
    REGISTER_RUNTIME_FUNCTION(ir_a_fin);
    REGISTER_RUNTIME_FUNCTION(ir_a);
    REGISTER_RUNTIME_FUNCTION(posicion_actual);
}

LppVariant LppRuntime::call(const std::string& fname, std::vector<LppVariant>& argv)
{
    auto itf = funcs.find(str::lower(fname));

    if (itf != funcs.end()) {
        IFunc fn = itf->second;
        return fn(argv);
    } else {
        throw std::runtime_error("Invalid inline function '" + fname + "'");
    }
}
