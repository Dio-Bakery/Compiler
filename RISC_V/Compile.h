#ifndef COMPILE_H
#define COMPILE_H

#include "RISC_V_ISA.h"
#include <QString>
#include<QFile>
#include<iostream>
#include <QRegularExpression>
#include "Class/report.h"

#define Compile_Success 1
#define Compile_False 0

int RISC_V_Compile(QString FilePath);

#endif // COMPILE_H
