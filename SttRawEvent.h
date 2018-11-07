#ifndef H_STT_RAW_EVENT
#define H_STT_RAW_EVENT

#include <TNamed.h>
#include <TClonesArray.h>
#include "SttHit.h"
//#include "SttRawHit.h"


class SttRawEvent : public SttHit {
public:

	TClonesArray* tdc_hits; 
	int totalNTDCHits;
	
	TClonesArray* tdc_events; 
	int totalNTDCEvents;

	// TClonesArray* tdc_raw; 
	// int rawNTDCEvents;
	
	SttRawEvent();
	virtual ~SttRawEvent() { Clear(); }

	void Clear(void);

	SttRawHit* AddHit(int channel);
	SttRawHit* event_size(int stt_tdc_event_sizes);

	//SttRawHit* AddRawHit(int channel);

	// SttRawHit* AddHit(int channel);
	// SttRawHit* event_size(int stt_tdc_event_sizes);

	ClassDef(SttRawEvent, 1)
};

#endif
