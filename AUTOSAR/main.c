#include <stdio.h>
#include "COM/Com.h"
#include "PduR/PduR.h"
#include "CanIf/CanIf.h"
#include "Can/Can.h"
#include "COM/Com_PBCfg.h"
#include "CanIf/CanIf_PBCfg.h"
#include "PduR/PduR_PBCfg.h"

const uint8 Data[] = {0x03};
int main() {
    Com_Init(&ComConfiguration);
    if(E_OK == Com_SendSignal(COM_SIGNAL_ID_EMOTIONSIGNAL, Data)){
        printf("Com_SendSignal successful \n");
    }
    PduR_Init(&PduR_Config);
    CanIf_Init(&CanIf_Config);
    const PduInfoType d = {
            .SduLength = ComConfiguration.ComIPdu[COM_SIGNAL_ID_EMOTIONSIGNAL].ComIPduSize,
            .SduDataPtr = ComConfiguration.ComIPdu[COM_SIGNAL_ID_EMOTIONSIGNAL].ComIPduDataPtr,
    };
    if(E_OK == PduR_ComTransmit(COM_PDU_ID_EMOTIONPDU, &d)){
        printf("PduR_ComTransmit successful \n");
    }
    printf("Hello, World!\n");
    return 0;
}