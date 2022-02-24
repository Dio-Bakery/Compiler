#include "Compile.h"
using namespace std;

extern QVector <QString> R_Type_ISA_List;
extern QVector <QString> R_Type_BitCode_List;

extern QVector <QString> I_Type_ISA_List;
extern QVector <QString> I_Type_BitCode_List;

extern QVector <QString> S_Type_ISA_List;
extern QVector <QString> S_Type_BitCode_List;

extern QVector <QString> B_Type_ISA_List;
extern QVector <QString> B_Type_BitCode_List;

static Ins_Type Ins_Type(QString Instruction)
{   // Yes : return the Type
    // No : return 0

    QString Ins = Instruction.toLower();

    if(R_Type_ISA_List.contains(Ins))
        return Type_R;

    if(I_Type_ISA_List.contains(Ins))
        return Type_I;

    if(S_Type_ISA_List.contains(Ins))
        return Type_S;

    if(B_Type_ISA_List.contains(Ins))
        return Type_B;
    return NO_Type;
}

static void Registor_Bit(QString & Rx)
{
    if(Rx.contains('x',Qt::CaseInsensitive))
    {
        Rx.remove(QChar('x'), Qt::CaseInsensitive);
    }

    if(Rx.contains('r',Qt::CaseInsensitive))
    {
        Rx.remove(QChar('r'), Qt::CaseInsensitive);
    }
    Rx = QString::number(Rx.toUInt(),2);

    while (Rx.size()<5) {
    Rx.prepend('0');
    }
}

static QVector <QString> Decode_Type_R(QString Line)
{
    QVector <QString>Bit_Code (Type_R_Ins_MAX);
    Bit_Code[R_opcode] = R_type_opcode;

    QString Instruction = Line.section(' ',0,0).toLower();

    int Index = 0;
    for(Index =0 ;Index < R_Type_ISA_List.size();Index++)
    {
        if(R_Type_ISA_List.at(Index)==Instruction)
            break;
    }

    Bit_Code[R_funct7] = R_Type_BitCode_List[Index*2];
    Bit_Code[R_funct3] = R_Type_BitCode_List[Index*2 + 1];

    QStringList Tmp;
    Tmp = Line.split(',');

    Bit_Code[R_rd] = Tmp.at(0).section(' ',1);

    Bit_Code[R_rs1] = Tmp.at(1);
    Bit_Code[R_rs2] = Tmp.at(2);



    Registor_Bit(Bit_Code[R_rd]);
    Registor_Bit(Bit_Code[R_rs1]);
    Registor_Bit(Bit_Code[R_rs2]);


    return Bit_Code;
}

static QString Imm_complement(QString signed_binary, uint32_t resulu_width)
{
    if(signed_binary.startsWith("-"))  // 取反
    {
        signed_binary.remove("-");
        while (signed_binary.size() < resulu_width) {
        signed_binary.prepend('0');
        }

        for(int i = 0;i<signed_binary.size();i++)
        {
            if(signed_binary.at(i)== '0')
                signed_binary[i]='1';
            else
            if(signed_binary.at(i)== '1')
                signed_binary[i]='0';
        }

        signed_binary = QString::number(signed_binary.toInt(nullptr,2) + 1,2);   // 加 1

    }
    else
    {
        while (signed_binary.size() < resulu_width) {
        signed_binary.prepend('0');
        }
    }

  return signed_binary;
}

static QVector <QString> Decode_Type_I(QString Line)
{
    QVector <QString>Bit_Code (Type_I_Ins_MAX);


    QString Instruction = Line.section(' ',0,0).toLower();

    int Index = 0;

    for(Index =0 ;Index < I_Type_ISA_List.size();Index++)
    {
        if(I_Type_ISA_List.at(Index)==Instruction)
            break;
    }

    Bit_Code[I_funct3] = I_Type_BitCode_List[Index];

    if(Index>=0 && Index<=4){
        Bit_Code[I_opcode] = I_type_opcode_1;

        QStringList Tmp;
        Tmp = Line.split(',');

        Bit_Code[I_rd] = Tmp.at(0).section(' ',1);

        Bit_Code[I_imm11_0] = Tmp.at(1).section('(',0,0).remove(" ");

        Bit_Code[I_rs1] = Tmp.at(1).section('(',1).section(")",0,0).remove(" ");

        Registor_Bit(Bit_Code[I_rd]);
        Registor_Bit(Bit_Code[I_rs1]);


        Bit_Code[I_imm11_0] = QString::number(Bit_Code[I_imm11_0].toInt(),2);
        Bit_Code[I_imm11_0] = Imm_complement(Bit_Code[I_imm11_0],12);
    }
    else
    if(Index>=5 && Index<=13)
    {
        Bit_Code[I_opcode] = I_type_opcode_2;

        QStringList Tmp;
        Tmp = Line.split(',');

        Bit_Code[I_rd] = Tmp.at(0).section(' ',1);

        Bit_Code[I_rs1] = Tmp.at(1);

        Bit_Code[I_imm11_0] = Tmp.at(2);



        Registor_Bit(Bit_Code[I_rd]);
        Registor_Bit(Bit_Code[I_rs1]);

        if(Index>=5 && Index<=10)
        {
            Bit_Code[I_imm11_0] = QString::number(Bit_Code[I_imm11_0].toInt(),2);
            Bit_Code[I_imm11_0] = Imm_complement(Bit_Code[I_imm11_0],12);
        }
        else
        if(Index>=11 && Index<=13)
        {
            Bit_Code[I_imm11_0] = QString::number(Bit_Code[I_imm11_0].toUInt(),2);
            Bit_Code[I_imm11_0] = Imm_complement(Bit_Code[I_imm11_0],5);
            while (Bit_Code[I_imm11_0].size() < 12) {
            Bit_Code[I_imm11_0].prepend('0');
            }
/*
            QByteArray byte = Bit_Code[I_imm11_0].toUtf8();
            char* str1 = byte.data();
            cout << str1 <<endl;
*/
            if(Instruction == "srai")
                Bit_Code[I_imm11_0][10] = '1';
        }
    }


    return Bit_Code;
}

static QVector <QString> Decode_Type_S(QString Line)
{


    QVector <QString>Bit_Code (Type_S_Ins_MAX);
    Bit_Code[S_opcode] = S_type_opcode;

    QString Instruction = Line.section(' ',0,0).toLower();

    int Index = 0;

    for(Index =0 ;Index < S_Type_ISA_List.size();Index++)
    {
        if(S_Type_ISA_List.at(Index)==Instruction)
            break;
    }

    Bit_Code[S_funct3] = S_Type_BitCode_List[Index];

    QStringList Tmp;
    Tmp = Line.split(',');

    Bit_Code[S_rs2] = Tmp.at(0).section(' ',1);

    QString S_imm11_0 = Tmp.at(1).section('(',0,0).remove(" ");
/*
    QByteArray byte = S_imm11_0.toUtf8();
    char* str1 = byte.data();
    cout << str1 <<endl;
*/
    Bit_Code[S_rs1] = Tmp.at(1).section('(',1).section(")",0,0).remove(" ");

    Registor_Bit(Bit_Code[S_rs2]);
    Registor_Bit(Bit_Code[S_rs1]);


    S_imm11_0 = QString::number(S_imm11_0.toInt(),2);
    S_imm11_0 = Imm_complement(S_imm11_0,12);

    Bit_Code[S_imm11_5] = S_imm11_0.left(7);
    Bit_Code[S_imm4_0]  = S_imm11_0.right(5);

    return Bit_Code;
}

static QVector <QString> Decode_Type_B(QString Line)
{

    QVector <QString>Bit_Code (Type_B_Ins_MAX);
    Bit_Code[B_opcode] = B_type_opcode;

    QString Instruction = Line.section(' ',0,0).toLower();

    int Index = 0;

    for(Index =0 ;Index < B_Type_ISA_List.size();Index++)
    {
        if(B_Type_ISA_List.at(Index)==Instruction)
            break;
    }

    Bit_Code[B_funct3] = B_Type_BitCode_List[Index];

    QStringList Tmp;
    Tmp = Line.split(',');

    Bit_Code[B_rs1] = Tmp.at(0).section(' ',1);
    Bit_Code[B_rs2] = QString(Tmp.at(1)).remove(" ");

    QString B_imm12_1 = QString(Tmp.at(2)).remove(" ");
/*

*/



    Registor_Bit(Bit_Code[B_rs1]);
    Registor_Bit(Bit_Code[B_rs2]);


    B_imm12_1 = QString::number(B_imm12_1.toInt() / 2,2);
    B_imm12_1 = Imm_complement(B_imm12_1,12);

    Bit_Code[B_imm12__10_5] = B_imm12_1.mid(0,1) + B_imm12_1.mid(2,6);
    Bit_Code[B_imm4_1__11]  = B_imm12_1.mid(8,4) + B_imm12_1.mid(1,1);

    return Bit_Code;
}

static QString RISC_V_Compile_line(QString Line)
{
    QString Result_BitCode = NULL;

    Line.remove(QChar('\n'));
    Line.remove(QChar('\r'));

    Line.replace(QRegularExpression("[\\s]+"), " ");

    QString Instruction = Line.section(' ',0,0);
    enum Ins_Type Instruction_Type = Ins_Type(Instruction);

    if( Instruction_Type == NO_Type)
    {
        Result_BitCode = NULL;
        return Result_BitCode;
    }


    QVector <QString> Bit_Code;
    switch(Instruction_Type)
    {
    case Type_R:
        Bit_Code = Decode_Type_R(Line);
        break;
    case Type_I:
        Bit_Code = Decode_Type_I(Line);
        break;
    case Type_S:
        Bit_Code = Decode_Type_S(Line);
        break;
    case Type_B:
        Bit_Code = Decode_Type_B(Line);
    default:
        break;
    }


    QStringList Bis_List(Bit_Code);
    Result_BitCode = Bis_List.join("");

    QByteArray byte = Result_BitCode.toUtf8();
    char* str1 = byte.data();
    cout << str1 <<endl;

    return Result_BitCode;
}



int RISC_V_Compile(QString FilePath)
{
    int ret = Compile_Success;
    Report report;

    report.Begin();

    //文件对象
    QFile file(FilePath);

    if(FilePath.isEmpty() == false){


            //打开文件
            bool isOK = file.open(QIODevice::ReadOnly);
            if(isOK == false)
                report.Flages[File_state] = Report_Error;
        }
    else
        report.Flages[File_state] = Report_Error;

    QStringList Result_Code_List;
    if(report.Next_Flage()<=0){   // 开始编译

        QByteArray array;
        uint32_t line_num = 1;

        while (file.atEnd() == false)
        {
              //读一行
              array =  file.readLine();
              QString Line(array);

              QString BitCode = RISC_V_Compile_line(Line);
              if(BitCode.isNull())
              {
                  report.Compile_Error_add(line_num);
                  report.Flages[Compile_state] = Report_Error;
              }
              else
              {
                Result_Code_List.append(BitCode);
              }

            line_num += 1;
        }
    }
    else
    {
        report.Error_report();
    }


    if(report.Next_Flage()<=0){  // 写回
       QString Compiled_FilePath = FilePath.replace(".s",".o");
       QFile Compiled_file(Compiled_FilePath);
       Compiled_file.open(QIODevice::WriteOnly);
       uint32_t Content_Index = 0;
       for(int i = 0;i<Result_Code_List.size();i++)
       {
          Compiled_file.write(Result_Code_List.at(i).toUtf8());
          Compiled_file.write("\n");
          Content_Index++;
       }

    }
    else
    {
        report.Error_report();
    }


    if(report.Next_Flage() != -1)
        ret = Compile_False;

    file.close();

    return ret;
}



