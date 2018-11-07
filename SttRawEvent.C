#include "SttRawEvent.h"

ClassImp(SttRawEvent)

SttRawEvent::SttRawEvent() {
	tdc_hits = new TClonesArray("SttRawHit", 1000);
	//tdc_events = new TClonesArray("SttRawHit", 1000);
	//tdc_raw = new TClonesArray("SttRawHit", 1000);



	totalNTDCHits = 0;
	totalNTDCEvents = 0;
	//rawNTDCEvents =0;


}

SttRawHit* SttRawEvent::AddHit(int channel) {
	TClonesArray& thits = *tdc_hits;
	SttRawHit* hit = new (thits[totalNTDCHits++]) SttRawHit();
	hit->SetChannel(channel);

	return hit;
}

// SttRawHit* SttRawEvent::event_size(int stt_tdc_event_sizes) {
// 	TClonesArray& tevents = *tdc_events;
// 	SttRawHit* event = new (tevents[totalNTDCEvents++]) SttRawHit();

// 	return event;
// }

// SttRawHit* SttEvent::AddRawHit(int channel) {
// 	TClonesArray& trawevents = *tdc_raw;
// 	SttRawHit* raw_hit = new (trawevents[rawNTDCEvents++]) SttRawHit();
// 	raw_hit->SetChannel(channel);

// 	return trawevents;
// }

void SttRawEvent::Clear(void) {
	tdc_hits->Clear("C");
	//tdc_events->Clear("C");
	//tdc_raw->Clear("C");

//	delete tdc_hits;
//	tdc_hits = new TClonesArray("SttHit", 1000);

	totalNTDCHits = 0;
	totalNTDCEvents = 0;
	//rawNTDCEvents = 0;


}


