#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->is_Compile_OK = 0;
    //this->setStyleSheet("QWidget{font-size:20px}");  // 设置所有的字体为统一像素
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_SelectFile_clicked()
{
    QString FilePath = QFileDialog::getOpenFileName(this, "打开文件", "D:\\temp\\");
    ui->File_to_Compile->setText(FilePath);
}


void MainWindow::on_pushButton_Compile_clicked()
{
    QString FilePath  = ui->File_to_Compile->text();
    this->is_Compile_OK = RISC_V_Compile(FilePath);

    if(this->is_Compile_OK)
        QMessageBox::about(this, tr("Compiled"), tr("Compiled OK"));
    else
        QMessageBox::about(this, tr("Compiled"), tr("Error！"));
}


void MainWindow::on_pushButton_toRamFile_clicked()
{
    if(this->is_Compile_OK)
    {

        // Compiled File
        QString Compiled_FilePath  = ui->File_to_Compile->text().replace(".s",".o");
        QFile Compiled_File(Compiled_FilePath);
        Compiled_File.open(QIODevice::ReadOnly);

        // Ram File
        QString RamFile_FilePath  =  ui->RamFile->text();
        QFile RamFile_File(RamFile_FilePath);
        RamFile_File.open(QIODevice::WriteOnly);


        RamFile_File.write("-- Copyright (C) 2018  Intel Corporation. All rights reserved.\n");
        RamFile_File.write("-- Your use of Intel Corporation's design tools, logic functions\n");
        RamFile_File.write("-- and other software and tools, and its AMPP partner logic\n");
        RamFile_File.write("-- functions, and any output files from any of the foregoing\n");
        RamFile_File.write("-- (including device programming or simulation files), and any\n");
        RamFile_File.write("-- associated documentation or information are expressly subject\n");
        RamFile_File.write("-- to the terms and conditions of the Intel Program License\n");
        RamFile_File.write("-- Subscription Agreement, the Intel Quartus Prime License Agreement,\n");
        RamFile_File.write("-- the Intel FPGA IP License Agreement, or other applicable license\n");
        RamFile_File.write("-- agreement, including, without limitation, that your use is for\n");
        RamFile_File.write("-- the sole purpose of programming logic devices manufactured by\n");
        RamFile_File.write("-- Intel and sold by Intel or its authorized distributors.  Please\n");
        RamFile_File.write("-- refer to the applicable agreement for further details.\n");
        RamFile_File.write("\n");
        RamFile_File.write("-- Quartus Prime generated Memory Initialization File (.mif)\n");
        RamFile_File.write("\n");
        RamFile_File.write("WIDTH=32;\n");
        RamFile_File.write("DEPTH=2048;\n");
        RamFile_File.write("\n");
        RamFile_File.write("ADDRESS_RADIX=UNS;\n");
        RamFile_File.write("DATA_RADIX=BIN;\n");
        RamFile_File.write("\n");
        RamFile_File.write("CONTENT BEGIN\n");

        uint32_t Code_index = 0;
        while (!Compiled_File.atEnd())
        {
            QByteArray line = Compiled_File.readLine();
            QString str(line);

            RamFile_File.write("\t");
            RamFile_File.write(QString().number(Code_index).toUtf8());
            RamFile_File.write("     :   ");

            RamFile_File.write(str.remove("\n").toUtf8());

            RamFile_File.write(";");
            RamFile_File.write("\n");
            Code_index++;
        }

        RamFile_File.write("\t");
        RamFile_File.write("[");
        RamFile_File.write(QString().number(Code_index).toUtf8());
        RamFile_File.write("..2047]  :   00000000000000000000000000000000;\n");
        RamFile_File.write("END;\n");

        RamFile_File.close();
        Compiled_File.close();

        QMessageBox::about(this, tr("Exchange"), tr("Change to RamFile success."));
    }
    else
        QMessageBox::about(this, tr("Exchange"), tr("Change to RamFile faild! Please compile first"));
}

