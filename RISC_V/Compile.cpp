#include "Compile.h"
using namespace std;

extern QVector <QString> R_Type_ISA_List;

extern QVector <QString> R_Type_BitCode_List;


static Ins_Type Ins_Type(QString Instruction)
{   // Yes : return the Type
    // No : return 0

    QString Ins = Instruction.toLower();

    if(R_Type_ISA_List.contains(Ins))
        return Type_R;

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

    while (Rx.size()<3) {
    Rx.prepend('0');
    }
}

static QVector <QString> Decode_Type_R(QString Line)
{
    QVector <QString>Bit_Code (Type_R_Ins_MAX);
    Bit_Code[Opcode] = R_type_opcode;

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

    Bit_Code[R_rs1] = Tmp.at(1);;
    Bit_Code[R_rs2] = Tmp.at(2);;

    Registor_Bit(Bit_Code[R_rd]);
    Registor_Bit(Bit_Code[R_rs1]);
    Registor_Bit(Bit_Code[R_rs2]);


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
    case Type_S:
    case Type_B:
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

    QStringList Result_Code;
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
                Result_Code.append(BitCode);
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
       for(int i = 0;i<Result_Code.size();i++)
       {
          Compiled_file.write(Result_Code.at(i).toUtf8());
          Compiled_file.write("\n");
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



