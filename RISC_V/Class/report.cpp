#include "report.h"
using namespace std;

Report::Report()
{
    for(int i =0;i<Max_Flage_num;i++)
    {
        Flages[i] = Report_Not_Start;
    }
}

void Report::Begin(){
    Current_State = File_state; // 开始先对文件进行操作
    Flages[File_state] = Report_UnderWay;

}

int Report::Next_Flage(){
    // return > 0    error flage
    // return <= 0   reutrn success
    // return == 0   last flage return success
    // return == -1  end of the report

    if(Current_State == Max_Flage_num)
        return -1; // end of the report

    if(Flages[Current_State] == Report_Error)
    {
        return (int)Current_State; // 返回当前错误的Flags
    }
    else
    if(Flages[Current_State] == Report_UnderWay)
    {
        Flages[Current_State] = Report_OK;

        switch (Current_State) {
        case File_state: Current_State = Compile_state;
            break;
        case Compile_state: Current_State = Max_Flage_num;
            break;
        default:
            break;
        }
    Flages[Current_State] = Report_UnderWay;
    }


    if(Compile_state != Max_Flage_num)
    {
        return 0;  // return success
    }
    else
        return -1; // end of the compile
}

void Report:: Compile_Error_add(uint32_t line_num)
{
    Sum_error += 1;
    Error_in_Line[Sum_error] = line_num;
}

void Report::Error_report(){
    string err("Compile Error in ");
    switch (Current_State) {
    case File_state:
        err += "File open!";
            break;
    case Compile_state:
        err += "Compile!";
            break;
    default:
        break;
    }
    cout << err <<endl;

    if(Sum_error>0)
    {
        for(uint32_t i = 1;i <= Sum_error; i++)
        {
            cout << "error" << i << "in" <<Error_in_Line[i] <<"line!"<<endl;
        }
    }

}
