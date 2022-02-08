/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_SelectFile;
    QPushButton *pushButton_Compile;
    QPushButton *pushButton_toRamFile;
    QLineEdit *RamFile;
    QLineEdit *File_to_Compile;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(618, 428);
        QFont font;
        font.setPointSize(9);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton_SelectFile = new QPushButton(centralwidget);
        pushButton_SelectFile->setObjectName(QString::fromUtf8("pushButton_SelectFile"));
        pushButton_SelectFile->setGeometry(QRect(130, 160, 80, 20));
        pushButton_Compile = new QPushButton(centralwidget);
        pushButton_Compile->setObjectName(QString::fromUtf8("pushButton_Compile"));
        pushButton_Compile->setGeometry(QRect(400, 160, 80, 20));
        pushButton_toRamFile = new QPushButton(centralwidget);
        pushButton_toRamFile->setObjectName(QString::fromUtf8("pushButton_toRamFile"));
        pushButton_toRamFile->setGeometry(QRect(260, 280, 121, 20));
        RamFile = new QLineEdit(centralwidget);
        RamFile->setObjectName(QString::fromUtf8("RamFile"));
        RamFile->setGeometry(QRect(70, 230, 471, 20));
        File_to_Compile = new QLineEdit(centralwidget);
        File_to_Compile->setObjectName(QString::fromUtf8("File_to_Compile"));
        File_to_Compile->setGeometry(QRect(60, 90, 471, 20));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 90, 54, 12));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 230, 54, 12));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 618, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_SelectFile->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        pushButton_Compile->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\257\221", nullptr));
        pushButton_toRamFile->setText(QCoreApplication::translate("MainWindow", "\350\275\254\346\215\242\345\210\260RamFile", nullptr));
        RamFile->setText(QCoreApplication::translate("MainWindow", "D:\\QuartusProject\\RISC-V\\AssemblyCode\\RamFile.mif", nullptr));
        File_to_Compile->setText(QCoreApplication::translate("MainWindow", "D:/QuartusProject/RISC-V/AssemblyCode/Test_ISAfile.s", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\272\220\346\226\207\344\273\266\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "RamFile:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
