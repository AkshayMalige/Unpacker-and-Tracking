#ifndef __PANDA_SUBSYSTEM_H__
#define __PANDA_SUBSYSTEM_H__

#include "TNamed.h"
#include "string.h"

class PandaSubsystem : public TNamed {

    public:

    string subsystem_name;

    PandaSubsystem();
    ~PandaSubsystem();

	ClassDef(PandaSubsystem, 1)
};

#endif