#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setStyleSheet("QWidget{font-size:20px}");  // 设置所有的字体为统一像素
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_SelectFile_clicked()
{
    QString FilePath = QFileDialog::getOpenFileName(this, "打开文件", "D:\\temp\\");
    ui->File_to_compile->setText(FilePath);
}


void MainWindow::on_pushButton_Compile_clicked()
{
    QString FilePath  = ui->File_to_compile->toPlainText();
    bool is_Compile_OK = RISC_V_Compile(FilePath);

    if(is_Compile_OK)
        QMessageBox::about(this, tr("Comiled"), tr("Comiled OK"));
    else
        QMessageBox::about(this, tr("Comiled"), tr("Error！"));
}

