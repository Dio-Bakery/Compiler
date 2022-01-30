#ifndef RISC_V_ISA_H
#define RISC_V_ISA_H
#include <QVector>
#include <QString>

enum Ins_Type{
    Type_R,
    Type_I,
    Type_S,
    Type_B,
    NO_Type
};

// *** R_Type *** begin *** //

#define R_type_opcode "0110011" //R type define

enum Type_R_Ins{
    R_funct7,
    R_rs2,
    R_rs1,
    R_funct3,
    R_rd,
    R_opcode,
    Type_R_Ins_MAX
};

// *** R_Type *** end *** //

// *** I_Type *** begin *** //

#define I_type_opcode_1 "0000011" //I type define
#define I_type_opcode_2 "0010011" //I type define

enum Type_I_Ins{
    I_imm11_0,
    I_rs1,
    I_funct3,
    I_rd,
    I_opcode,
    Type_I_Ins_MAX
};

// *** I_Type *** end *** //

// *** S_Type *** begin *** //

#define S_type_opcode "0100011" //S type define

enum Type_S_Ins{
    S_imm11_5,
    S_rs2,
    S_rs1,
    S_funct3,
    S_imm4_0,
    S_opcode,
    Type_S_Ins_MAX
};

// *** S_Type *** end *** //


#endif // RISC_V_ISA_H
