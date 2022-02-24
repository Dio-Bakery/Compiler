#include "RISC_V_ISA.h"

// *** R_Type *** begin *** //

QVector <QString> R_Type_ISA_List = {"add", "sub", "sll", "slt", "sltu", "xor", "srl", "sra", "or", "and"};

QVector <QString> R_Type_BitCode_List = {
/*
  Format
  funct7   //Ins
  funct3
*/

    "0000000",  // ADD
    "000",

    "0100000",  // SUB
    "000",

    "0000000",  // SLL
    "001",

    "0000000",  // SLT
    "010",

    "0000000",  // SLTU
    "011",

    "0000000",  // XOR
    "100",

    "0000000",  // SRL
    "101",

    "0100000",  // SRA
    "101",

    "0000000",  // OR
    "110",

    "0000000",  // AND
    "111"
};

// *** R_Type *** end *** //



// *** I_Type *** begin *** //

QVector <QString> I_Type_ISA_List = {"lb", "lh", "lw", "lbu", "lhu",
                                    "addi", "slti", "sltiu", "xori", "ori", "andi",
                                    "slli", "srli", "srai"};

QVector <QString> I_Type_BitCode_List = {
/*
  Format
  funct3   //Ins    //index
*/
    "000",  //LB    //0
    "001",  //LH
    "010",  //LW
    "100",  //LBU
    "101",  //LHU   //4

    "000",  //ADDI  //5
    "010",  //SLTI
    "011",  //SLTIU
    "100",  //XORI
    "110",  //ORI
    "111",   //ANDI  //10

    "001",  //SLLI   //11
    "101",  //SRLI
    "101"   //SRAI   //13
};

// *** I_Type *** end *** //


// *** S_Type *** begin *** //

QVector <QString> S_Type_ISA_List = {"sb", "sh", "sw"};

QVector <QString> S_Type_BitCode_List = {
/*
  Format
  funct3   //Ins    //index
*/
    "000",  //SB
    "001",  //SH
    "010",  //SW
};

// *** S_Type *** end *** //


// *** B_Type *** begin *** //

QVector <QString> B_Type_ISA_List = {"beq", "bne", "blt", "bge", "bltu", "bgeu"};

QVector <QString> B_Type_BitCode_List = {
/*
  Format
  funct3   //Ins
*/
    "000",  //BEQ
    "001",  //BNE
    "100",  //BLT
    "101",  //BGE
    "110",  //BLTU
    "111",  //BGEU
};

// *** B_Type *** end *** //
