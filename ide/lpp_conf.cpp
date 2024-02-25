#include <qglobal.h>
#include <QFile>
#include "lpp_conf.h"

void LppConf::parserTerminalArgs(const QString& args)
{
    term_arg_list = args.split(' ');
    /*for (int i = 0; i < term_arg_list.size(); i++) {
        if (term_arg_list[i].contains("${LPP_INTERP}")) {
            term_arg_list[i].replace("${LPP_INTERP}", interp);
        }
    }*/
}

bool LppConf::findTerminal()
{
#ifdef Q_OS_UNIX
    static QString terms[] = {
        QStringLiteral("/usr/bin/konsole"),
        QStringLiteral("/usr/bin/gnome-terminal"),
        QStringLiteral("/usr/bin/xterm"),
    };

    static QString term_args[] = {
        QStringLiteral("--geometry 910x660+10+10 -e"),
        QLatin1String(""), // TODO: Set gnome-terminal arguments
        QStringLiteral("-geometry 90x30 -fa 'Monospace' -fs 14 -e"),
    };
    static constexpr int TERM_COUNT = sizeof(terms)/sizeof(terms[0]);

    for (int i = 0; i < TERM_COUNT; i++) {
        QFile ft(terms[i]);

        if (ft.exists()) {
            terminal = ft.fileName();
            term_arg_list = term_args[i].split(' ');
            return true;
        }
    }

    return false;
#else
    return true;
#endif
}
