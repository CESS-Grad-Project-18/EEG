#if !(((COM_SW_MAJOR_VERSION == 5) && (COM_SW_MINOR_VERSION == 5)) )
#error Com: Configuration file expected BSW module version to be 5.5.*
#endif

#ifndef COM_PBCFG_H
#define COM_PBCFG_H

#include "Com_Types.h"
extern const Com_ConfigType ComConfiguration;

/* PDU Group ID */
#define COM_DEFAULT_IPDU_GROUP  0

#define COM_IPDU_GROUP_PduGroup1                        0

/* COM IPDU ID */
#define COM_ID_TxMsgTime                        0
#define COM_ID_RxMsgAbsInfo                     1
 


/* General Signal (Group) ID */
#define COM_SID_SystemTime 0
#define COM_SID_VehicleSpeed                     1
#define COM_SID_TachoSpeed                       2
#define COM_SID_Led1Sts                          3
#define COM_SID_Led2Sts                          4
#define COM_SID_Led3Sts                          5


/* Group Signal ID */
#define COM_GSID_year                             0
#define COM_GSID_month                            1
#define COM_GSID_day                              2
#define COM_GSID_hour                             3
#define COM_GSID_minute                           4
#define COM_GSID_second                           5


#endif /* COM_PBCFG_H */    
    