#ifndef H_STT_EVENT
#define H_STT_EVENT

#include <TNamed.h>
#include <TClonesArray.h>
#include "SttHit.h"

class SttEvent : public TNamed {
public:

	TClonesArray* tdc_hits; 
	int totalNTDCHits;
	
	SttEvent();
	virtual ~SttEvent() { Clear(); }

	void Clear(void);

	SttHit* AddHit(int channel);

	ClassDef(SttEvent, 1)
};

#endif
