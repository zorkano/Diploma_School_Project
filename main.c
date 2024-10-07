#include "display.h"

int main(void){
    system("chcp 65001");

    int state = 1;
    while(1){
    switch (state)
    {
    case 0:
        state = Start();
        break;
    case 1:
        state = Log_In_Menu();
        break;
    default:
        break;
    }
    }
    return 0;
}