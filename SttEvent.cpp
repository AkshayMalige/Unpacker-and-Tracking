

#include "SttEvent.h"

ClassImp(SttEvent)

SttEvent::SttEvent() {
	tdc_hits = new TClonesArray("SttHit", 1000);

	totalNTDCHits = 0;
}

SttHit* SttEvent::AddHit(int channel) {
	TClonesArray& thits = *tdc_hits;
	SttHit* hit = new (thits[totalNTDCHits++]) SttHit();
	hit->SetChannel(channel);

	return hit;
}

void SttEvent::Clear(void) {
	delete tdc_hits;
	tdc_hits = new TClonesArray("SttHit", 1000);

	totalNTDCHits = 0;
}


