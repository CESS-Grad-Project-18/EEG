#include <stdio.h>
#include "COM/Com.h"
#include "PduR/PduR.h"
#include "CanIf/CanIf.h"
#include "Can/Can.h"
#include "COM/Com_PBCfg.h"
#include "CanIf/CanIf_PBCfg.h"
const uint8 Data[] = {0xFF};
int main() {
    Com_Init(&ComConfiguration);
    if(E_OK == Com_SendSignal(COM_SIGNAL_ID_EMOTIONSIGNAL, Data)){
        printf("Com_SendSignal successful \n");
    }
    /*PduR_Init();*/
    printf("Hello, World!\n");
    return 0;
}