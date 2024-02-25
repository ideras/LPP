#include <iostream>
#include <QApplication>
#include <QSettings>
#include <QFile>
#include "mainwindow.h"
#include "lpp_conf.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString app_path = app.applicationDirPath();

    QString conf_filepath = app_path + "/lpp.ini";
    QFile conf_file(conf_filepath);

    LppConf lpp_conf;
    if (conf_file.exists()) {
        QSettings settings(conf_file.fileName(), QSettings::IniFormat);

        lpp_conf.terminal = settings.value("Terminal", "").toString().trimmed();
        QString term_args = settings.value("TerminalArgs", "").toString().trimmed();
        lpp_conf.interp = settings.value("LppInterp", "").toString().trimmed();

        if (!term_args.isEmpty()) {
            lpp_conf.parserTerminalArgs(term_args);
        }
    }
    if (lpp_conf.terminal.isEmpty()) {
        if (!lpp_conf.findTerminal()) {
            std::cerr << "No se pudo encontrar un simulador de terminal.\n"
                         "Por favor instale uno y especifiquelo en el archivo lpp.ini";
            return 1;
        }
    }
    if (lpp_conf.interp.isEmpty()) {
        lpp_conf.interp = app_path + "/lpp_interp";
    }

    MainWindow mw(lpp_conf);

    mw.show();
    return app.exec();
}
