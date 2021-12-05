#ifndef REPORT_H
#define REPORT_H
#include <string>
#include <iostream>

enum Report_State{
    Report_Not_Start,
    Report_UnderWay,
    Report_Error,
    Report_OK
};

enum Report_Flage{
    File_state,
    Compile_state,

    Max_Flage_num
};

class Report
{
private:
    Report_Flage Current_State;
    uint32_t Error_in_Line[50]={0};
    uint32_t Sum_error = 0;
public:
    Report_State Flages[Max_Flage_num];

public:
    Report();
    void Begin();
    Report_Flage Get_Curren_Flag(){
        return Current_State;
    }
    int Next_Flage();

    void Error_report();
    void Compile_Error_add(uint32_t line_num);
};

#endif // REPORT_H
