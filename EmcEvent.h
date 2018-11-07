#ifndef H_EMC_EVENT
#define H_EMC_EVENT

#include <TNamed.h>
#include <TClonesArray.h>
#include "EmcHit.h"

class EmcEvent : public TNamed {
public:

	TClonesArray* adc_hits; 
	TClonesArray* adc_parms; 

	int totalNTDCHits;
	int totalNADCHits;
	
	EmcEvent();
	virtual ~EmcEvent() { Clear(); } 

	void Clear(void);

	EmcHit* AddHit();

	EmcHit* AddParm();

	ClassDef(EmcEvent, 1)
};

#endif
