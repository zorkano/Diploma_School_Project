#include "display.h"

int main(void){
    system("chcp 65001");
    int state = START_UI;
    int wrongPass;

    while(1){
        switch (state)
        {
        case START_UI:
            wrongPass = 0;
            Start(&state);
            break;
        case LOG_IN_UI:
            Log_In_Menu(&state);
            if(2 == wrongPass){
                state = START_UI;
            }else if(START_UI == state){
                wrongPass++;
                state = LOG_IN_UI;
            }
            break;
        case DEV_INFO_UI:
            Developer_Info_Menu(&state);
            break;
        case OPTIONS_UI:
            
            break;
        default:
            break;
        }
    }
    return 0;
}