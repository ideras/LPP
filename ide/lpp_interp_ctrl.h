#ifndef LPPINTERPCTRL_H
#define LPPINTERPCTRL_H

#include <qglobal.h>

#ifdef Q_OS_WIN
#include <windows.h>
#include <thread>
#endif

#include <QString>
#include <QProcess>
#include "lpp_conf.h"

enum class LppInterpResult
{ Success, TerminalNotFound, CannotStartInterp };

class LppInterpCtrl: public QObject
{
    Q_OBJECT

public:
    LppInterpCtrl(const LppConf& lpp_conf);
    ~LppInterpCtrl();

    LppInterpResult execProgram(const QString& prg_name);
    LppInterpResult compileProgram(const QString& prg_name);
    void killProcess();

    QString lastError() const
    { return last_error; }

#ifdef Q_OS_WIN
private:
    void waitForProcess();
#else
private slots:
    void onExecProgramFinished(int exit_code);
#endif

private slots:
    void onCompileProgramFinished(int exit_code);

signals:
    void finished(int action);

private:
    const LppConf& lpp_conf;
    QProcess lppi_proc;
    QString last_error;

#ifdef Q_OS_WIN
    HANDLE h_process;
    HANDLE h_thread;
    std::thread waiter_thread;
#else

#endif
};

#endif // LPPINTERPCTRL_H
