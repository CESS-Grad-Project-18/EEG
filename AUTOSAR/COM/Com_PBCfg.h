#ifndef COM_PBCFG_H
#define COM_PBCFG_H

#include "Com.h"
extern const Com_ConfigType ComConfiguration;

/* PDU Group ID */
#define COM_DEFAULT_IPDU_GROUP  0

#define COM_IPDU_GROUP_PduGroup1                        0

/* COM IPDU ID */
#define COM_ID_TxMsgTemp                        0
#define COM_ID_RxMsgAbsInfo                     1
 


/* General Signal (Group) ID */
#define COM_SID_ACTemp                            0
#define COM_SID_MotorSpeed                        1
#define COM_SID_MotorTemp                         2
#define COM_SID_Led1Stat                          3
#define COM_SID_Led2Stat                          4
#define COM_SID_Led3Stat                          5


#endif /* COM_PBCFG_H */    
    