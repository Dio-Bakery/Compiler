#include "RISC_V_ISA.h"

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
