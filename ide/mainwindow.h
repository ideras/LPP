#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "lpp_conf.h"
#include "lpp_interp_ctrl.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class LPPHighlighter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const LppConf& lpp_conf, QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool saveProgramIfModified();
    void reportErrorMessage(LppInterpResult lires);

private slots:
    void on_actionNuevoPrg_triggered();
    void on_actionAbrir_triggered();
    void on_actionGuardar_triggered();
    void onProgramFinished(int action);
    void onModificationChanged(bool);
    void on_actionDetenerPrg_triggered();
    void on_actionEjecutarPrg_triggered();
    void on_actionCompilarPrg_triggered();
    void on_actionSalir_triggered();

private:
    Ui::MainWindow *ui;
    LPPHighlighter *highlighter;
    QString last_dir;
    QString prg_filepath;
    LppConf lpp_conf;
    LppInterpCtrl lppi_ctrl;
};
#endif // MAINWINDOW_H
