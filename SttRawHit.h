#ifndef H_STT_RAW_HIT
#define H_STT_RAW_HIT

#include <TNamed.h>
//#include <SttHit.h>


class SttRawHit : public TNamed {
public:
	int channel;
	int stt_tdc_event_sizes;
	double leadTime;
	double trailTime;
	double tot;



	bool isRef;

	SttRawHit();

	virtual ~SttRawHit() { }

	void SetChannel(int c) { channel = c; } 


	ClassDef(SttRawHit, 1)

};
#endif


