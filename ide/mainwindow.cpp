#include <QDebug>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include "mainwindow.h"
#include "lpp_highlighter.h"
#include "lpp_conf.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(const LppConf& lpp_conf, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      lpp_conf(lpp_conf),
      lppi_ctrl(lpp_conf)
{
    ui->setupUi(this);
    ui->edtSourceCode->setTabStopDistance(ui->edtSourceCode->fontMetrics().horizontalAdvance(' ')*4);
    highlighter = new LPPHighlighter(ui->edtSourceCode->document());
    last_dir = QDir::homePath();

    connect(&lppi_ctrl, &LppInterpCtrl::finished, this, &MainWindow::onProgramFinished);
    //connect(&lppi, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), this, &MainWindow::onProgramFinished);
    connect(ui->edtSourceCode, &QPlainTextEdit::modificationChanged, this, &MainWindow::onModificationChanged);

    QFont fixed_font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fixed_font.setStyleHint(QFont::TypeWriter);
    fixed_font.setPointSize(14);

    ui->edtSourceCode->setFont(fixed_font);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::saveProgramIfModified()
{
    if (ui->edtSourceCode->document()->isModified()) {
        int res = QMessageBox::question(this, "Confirmacion", "El programa actual no ha sido guardado.<br/>"
                                                              "\u00bfDesea guardarlo antes de continuar?");

        if (res == QMessageBox::Yes) {
            on_actionGuardar_triggered();

            if (ui->edtSourceCode->document()->isModified()) {
                return false;
            }
        }
    }
    return true;
}

void MainWindow::reportErrorMessage(LppInterpResult lires)
{
    switch (lires) {
        case LppInterpResult::TerminalNotFound: {
            QMessageBox::critical(this, "Error", "El comando para ejecutar la terminal no existe.<br/>"
                                                 "Por favor especifique el comando en el archivo lpp.ini");
            break;
        }
        case LppInterpResult::CannotStartInterp: {
            QMessageBox::critical(this, "Error", "No se pudo iniciar el interprete de LPP");
            break;
        }
        default:
            break;
    }
}

void MainWindow::on_actionSalir_triggered()
{
    if (!saveProgramIfModified()) {
        return;
    }

    qApp->quit();
}

void MainWindow::on_actionNuevoPrg_triggered()
{
    if (!saveProgramIfModified()) {
        return;
    }
    ui->statusbar->clearMessage();
    prg_filepath.clear();
    ui->edtSourceCode->document()->clear();
}

void MainWindow::on_actionAbrir_triggered()
{
    if (!saveProgramIfModified()) {
        return;
    }

    QString filepath = QFileDialog::getOpenFileName(
        this,
        "Seleccione un programa",
        last_dir,
        "Programas de LPP (*.lpp);;Todos los archivos (*)");

    if (!filepath.isEmpty()) {
        QFile file(filepath);

        if (file.open(QFile::ReadOnly | QFile::Text)) {
            prg_filepath = filepath;
            last_dir = QFileInfo(prg_filepath).dir().absolutePath();
            ui->edtSourceCode->setPlainText(file.readAll());

            ui->edtSourceCode->document()->setModified(false);
        } else {
            QMessageBox::critical(this, "Error", "No se pudo abrir el archivo de programa");
        }
    }
}

void MainWindow::on_actionGuardar_triggered()
{
    if (!ui->edtSourceCode->document()->isModified()) {
        return;
    }

    if (prg_filepath.isEmpty()) {
        prg_filepath = QFileDialog::getSaveFileName(
            this,
            "Seleccione un archivo para guardar el programa ...",
            last_dir,
            "Programas de LPP (*.lpp);;Todos los archivos (*)");
    }

    if (!prg_filepath.isEmpty()) {
        QFile file(prg_filepath);

        if (file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
            file.write(ui->edtSourceCode->toPlainText().toUtf8());

            ui->edtSourceCode->document()->setModified(false);
        } else {
            QMessageBox::critical(this, "Error", "No se pudo guardar el programa");
        }
    }
}

void MainWindow::onProgramFinished(int action)
{
    ui->actionEjecutarPrg->setEnabled(true);
    ui->actionCompilarPrg->setEnabled(true);
    ui->actionDetenerPrg->setEnabled(false);

    if (action == 0) {
        if (!lppi_ctrl.lastError().isEmpty()) {
            QRegularExpression lre("^Linea[ ]+([0-9]+):");
            QString last_err = lppi_ctrl.lastError();
            QRegularExpressionMatch match = lre.match(last_err);
            if (match.hasMatch()) {
                int line_number = match.captured(1).toInt();
                ui->edtSourceCode->gotoLine(line_number);
            }
            QMessageBox::critical(this, "Error", lppi_ctrl.lastError());
        } else {
            QMessageBox::information(this, "Info", "El programa compila con \u00e9xito");
        }
    }
}

void MainWindow::onModificationChanged(bool change)
{
    if (change) {
        statusBar()->showMessage("**" + prg_filepath);
    } else {
        statusBar()->showMessage(prg_filepath);
    }
}

void MainWindow::on_actionDetenerPrg_triggered()
{
    lppi_ctrl.killProcess();
}

void MainWindow::on_actionEjecutarPrg_triggered()
{
    if (ui->edtSourceCode->document()->isModified() || prg_filepath.isEmpty()) {
        QMessageBox::critical(this, "Error", "Debe guardar el programa actual antes de ejecutarlo");
        return;
    }

    ui->actionEjecutarPrg->setEnabled(false);
    ui->actionCompilarPrg->setEnabled(false);
    ui->actionDetenerPrg->setEnabled(true);

    LppInterpResult lires = lppi_ctrl.execProgram(prg_filepath);
    if (lires == LppInterpResult::Success) {
        return;
    }

    ui->actionEjecutarPrg->setEnabled(true);
    ui->actionCompilarPrg->setEnabled(true);
    ui->actionDetenerPrg->setEnabled(false);

    reportErrorMessage(lires);
}

void MainWindow::on_actionCompilarPrg_triggered()
{
    if (ui->edtSourceCode->document()->isModified() || prg_filepath.isEmpty()) {
        QMessageBox::critical(this, "Error", "Debe guardar el programa actual antes de ejecutarlo");
        return;
    }

    ui->actionEjecutarPrg->setEnabled(false);
    ui->actionCompilarPrg->setEnabled(false);
    ui->actionDetenerPrg->setEnabled(true);

    LppInterpResult lires = lppi_ctrl.compileProgram(prg_filepath);
    if (lires == LppInterpResult::Success) {
        return;
    }

    ui->actionEjecutarPrg->setEnabled(true);
    ui->actionCompilarPrg->setEnabled(true);
    ui->actionDetenerPrg->setEnabled(false);

    reportErrorMessage(lires);
}

