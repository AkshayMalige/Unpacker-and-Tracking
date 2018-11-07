#ifndef H_STT_CAL_EVENT
#define H_STT_CAL_EVENT

#include <TNamed.h>
#include <TClonesArray.h>
#include "SttHit.h"
#include "SttRawHit.h"


class Stt_Cal_Event : public TNamed {
public:

	TClonesArray* tdc_cal_hits; 
	int total_cal_NTDCHits;
	
	// TClonesArray* tdc_events; 
	// int totalNTDCEvents;

	// TClonesArray* tdc_raw; 
	// int rawNTDCEvents;
	
	Stt_Cal_Event();
	virtual ~Stt_Cal_Event() { Clear(); }

	void CalClear(void);

	SttHit* AddCalHit(int channel);
	//SttHit* event_size(int stt_tdc_event_sizes);

	//SttRawHit* AddRawHit(int channel);

	// SttRawHit* AddHit(int channel);
	// SttRawHit* event_size(int stt_tdc_event_sizes);

	ClassDef(Stt_Cal_Event, 1)
};

#endif
