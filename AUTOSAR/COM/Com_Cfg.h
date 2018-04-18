#ifndef COM_CFG_H
#define COM_CFG_H

/* TODO: Revise numbers */
#define COM_INIT_ID 1
#define COM_DEINIT_ID -1
#define COM_SENDSIGNAL_ID 2
#define COM_RXINDICATION_ID 3
#define COM_TXCONFIRMATION_ID 4
#define COM_MAX_BUFFER_SIZE						150

#define COM_MAX_N_IPDUS							20
#define COM_MAX_N_SIGNALS						40

#define COM_E_INVALID_FILTER_CONFIGURATION		101
#define COM_E_INITIALIZATION_FAILED				102
#define COM_E_INVALID_SIGNAL_CONFIGURATION		103
#define COM_INVALID_PDU_ID						104
#define COM_INVALID_SIGNAL_ID					109

#define COM_E_TOO_MANY_IPDU						106
#define COM_E_TOO_MANY_SIGNAL					107
#define COM_E_PARAM_POINTER                    108
#define COM_E_UNINIT                            111
#define CPU_ENDIANESS							COM_BIG_ENDIAN

#endif /*COM_CFG_H*/