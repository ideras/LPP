#include "lpp_interp_ctrl.h"
#include <QFile>

LppInterpCtrl::LppInterpCtrl(const LppConf& lpp_conf)
    : lpp_conf(lpp_conf),
      lppi_proc(this)
{}

LppInterpResult LppInterpCtrl::compileProgram(const QString &prg_name)
{
    if (!QFile::exists(lpp_conf.interp)) {
        return LppInterpResult::InterpNotFound;
    }

    QString cmd = lpp_conf.interp;
    QStringList args;

    args << "--action" << "compile" << prg_name;

    connect(&lppi_proc, qOverload<int, QProcess::ExitStatus>(&QProcess::finished),
            this, &LppInterpCtrl::onCompileProgramFinished);

    lppi_proc.setReadChannel(QProcess::StandardError);
    lppi_proc.start(cmd, args);

    if (!lppi_proc.waitForStarted(3000)) {
        lppi_proc.close();

        return LppInterpResult::CannotStartInterp;
    }

    return LppInterpResult::Success;
}

void LppInterpCtrl::onCompileProgramFinished(int exit_code)
{
    last_error.clear();
    if (exit_code != 0) {
        last_error = lppi_proc.readAllStandardError().trimmed();
    }

    disconnect(&lppi_proc, qOverload<int, QProcess::ExitStatus>(&QProcess::finished),
                this, &LppInterpCtrl::onCompileProgramFinished);

    emit finished(0);
}
