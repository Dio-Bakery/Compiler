#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QString>
#include <QFileDialog>
#include "RISC_V/Compile.h"
#include <QMessageBox>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_SelectFile_clicked();

    void on_pushButton_Compile_clicked();

    void on_pushButton_toRamFile_clicked();

private:
    Ui::MainWindow *ui;

private:
    bool is_Compile_OK;
};
#endif // MAINWINDOW_H
