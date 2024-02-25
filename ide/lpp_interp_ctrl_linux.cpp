#include <QDebug>
#include <QDir>
#include <QFile>
#include "lpp_interp_ctrl.h"

LppInterpCtrl::~LppInterpCtrl()
{}

LppInterpResult LppInterpCtrl::execProgram(const QString &prg_name)
{
    QFile term_file(lpp_conf.terminal);

    if (!term_file.exists()) {
        return LppInterpResult::TerminalNotFound;
    }

    QString cmd = term_file.fileName();
    QStringList args;

    args << lpp_conf.term_arg_list << lpp_conf.interp
        << "--pause" << "--action" << "run" << prg_name;

    connect(&lppi_proc, qOverload<int, QProcess::ExitStatus>(&QProcess::finished),
            this, &LppInterpCtrl::onExecProgramFinished);

    lppi_proc.start(cmd, args);

    if (!lppi_proc.waitForStarted(500)) {
        return LppInterpResult::CannotStartInterp;
    }

    return LppInterpResult::Success;
}

void LppInterpCtrl::killProcess()
{
    lppi_proc.kill();
}

void LppInterpCtrl::onExecProgramFinished(int exit_code)
{
    disconnect(&lppi_proc, qOverload<int, QProcess::ExitStatus>(&QProcess::finished),
                this, &LppInterpCtrl::onExecProgramFinished);

    if (exit_code != 0) {
        qDebug() << lppi_proc.readAllStandardError();
    }
    emit finished(1);
}
