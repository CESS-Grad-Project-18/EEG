#include <stdlib.h>
#include <string.h>
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "PduR.h"
#include "PduR_Com.h"
#include "PduR_Dcm.h"
#include "PduR_CanIf.h"
#include "PduR_CanTp.h"
#include "PduR_Ipdum.h"

/*      void Det_ReportError(ModuleId, ApiId, ErrorId) */

/* The state of the PDU router. */
PduR_StateType PduRState = PDUR_UNINIT;


#if PDUR_ZERO_COST_OPERATION == STD_OFF



const PduR_PBConfigType * PduRConfig;


/* Initializes the PDU Router. */
void PduR_Init (const PduR_PBConfigType* ConfigPtr) {

	/* Make sure the PDU Router is uninitialized. If not,  raise an error. */
	if (PduRState != PDUR_UNINIT) {
		// Raise error and return.
		Det_ReportError(MODULE_ID_PDUR, PDUR_INSTANCE_ID, 0x00, PDUR_E_INVALID_REQUEST);
	} else if (ConfigPtr == NULL) {
		Det_ReportError(MODULE_ID_PDUR, PDUR_INSTANCE_ID, 0x00, PDUR_E_CONFIG_PTR_INVALID);
	}else if(ERROR) { /* Read error condition */
		PduRConfig = ConfigPtr;
		PduRState = PDUR_REDUCED;
		Dem_ReportErrorStatus(PDUR_E_INIT_FAILED, otherParam); /* TODO: Implement or not */
	}
	} else {
		PduRConfig = ConfigPtr;
		PduRState = PDUR_ONLINE;
	}

}


#if PDUR_VERSION_INFO_API == STD_ON
void PduR_GetVersionInfo (Std_VersionInfoType* versionInfo){
	versionInfo->moduleID = (uint16)MODULE_ID_PDUR;
	versionInfo->vendorID = (uint16)1;

	/* TODO: Vendor version numbers check */
}
#endif

uint32 PduR_GetConfigurationId (void) {
	return PduRConfig->PduRConfigurationId;
}
#endif