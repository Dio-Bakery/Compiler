#ifndef RISC_V_ISA_H
#define RISC_V_ISA_H
#include <QVector>
#include <QString>

#define R_type_opcode "0110011" //R type define

enum Ins_Type{
    Type_R,
    Type_I,
    Type_S,
    Type_B,
    NO_Type
};

enum Type_R_Ins{
    R_funct7,
    R_rs2,
    R_rs1,
    R_funct3,
    R_rd,
    Opcode,
    Type_R_Ins_MAX
};

#endif // RISC_V_ISA_H
