#include <qt_windows.h>
#include <QDir>
#include <thread>
#include "lpp_interp_ctrl.h"

LppInterpCtrl::~LppInterpCtrl()
{
    if (waiter_thread.joinable()) {
        waiter_thread.join();
    }
}

LppInterpResult LppInterpCtrl::execProgram(const QString& prg_name)
{
    if (waiter_thread.joinable()) {
        waiter_thread.join();
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    QString exe = QDir::toNativeSeparators(lpp_conf.interp);
    QString program = QDir::toNativeSeparators(prg_name);

    QString cmd = QStringLiteral("\"%1\" --pause --action run \"%2\"")
                      .arg(exe, program);

    qDebug() << "Running:" << cmd;

    std::wstring cmdLine = cmd.toStdWString();

    BOOL success = CreateProcess(
        NULL,
        cmdLine.data(),
        NULL,
        NULL,
        FALSE,
        NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi
        );

    if (!success) {
        DWORD err = GetLastError();
        qDebug() << "CreateProcess failed, error:" << err;
        return LppInterpResult::CannotStartInterp;
    }

    h_process = pi.hProcess;
    h_thread  = pi.hThread;

    waiter_thread = std::thread([this]() { this->waitForProcess(); });

    return LppInterpResult::Success;
}


void LppInterpCtrl::killProcess()
{
    TerminateProcess(h_process, 99);

    if (waiter_thread.joinable()) {
        waiter_thread.join();
    }
}

void LppInterpCtrl::waitForProcess()
{
    WaitForSingleObject(h_process, INFINITE);    
    CloseHandle(h_thread);
    CloseHandle(h_process);

    emit finished(1);
}

