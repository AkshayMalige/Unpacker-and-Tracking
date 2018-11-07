#ifndef __PANDA_STT_DRIFTRADIUS_H__
#define __PANDA_STT_DRIFTRADIUS_H__

#include "panda_subsystem.h"
#include "SttEvent.h"
#include "string.h"

class PandaSttDrift : public PandaSubsystem {

    public:
    	
    SttEvent stt_drift_radius;
    //SttEvent stt_drift_radius;
    
    PandaSttDrift();
    ~PandaSttDrift();

	ClassDef(PandaSttDrift, 1)
};

#endif


