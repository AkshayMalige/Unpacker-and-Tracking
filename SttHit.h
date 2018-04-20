#ifndef H_STT_HIT
#define H_STT_HIT

#include <TNamed.h>


class SttHit : public TNamed {
public:
	int channel;
	double leadTime;
	double trailTime;
	double tot;
		double drifttime;

	short layer;
	short module;
	short fee;
	short fee_channel;

	double x;
	double y;
	double z;

	bool isRef;

	SttHit();

	virtual ~SttHit() { }

	void SetChannel(int c) { channel = c; } 


	ClassDef(SttHit, 1)

};



#endif
