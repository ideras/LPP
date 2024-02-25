#ifndef LPP_CONF_H
#define LPP_CONF_H

#include <QString>
#include <QStringList>

struct LppConf
{
    void parserTerminalArgs(const QString& args);
    bool findTerminal();

    QString terminal;
    QString interp;
    QStringList term_arg_list;
};

#endif // LPP_CONF_H
