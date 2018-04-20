#ifndef H_STT_DETECTOR
#define H_STT_DETECTOR

#include <iostream>
#include <map>

using namespace std;

struct detLoc {
  detLoc(){};
  
  detLoc(int p_layer, int p_module, int p_fee, int p_channel_no){
    layer = p_layer;
    module = p_module;
    fee = p_fee;
    channel_no = p_channel_no;
    double x;
  }

  int layer;
  int module;
  int fee;
  int channel_no;
  double x;
};

class SttDetector {
	public:
		map<int, detLoc> detMap;

		SttDetector();

		detLoc GetDetectorLocFromTDCChannel(int channel);

};


#endif
