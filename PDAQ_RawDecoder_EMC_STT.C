#include <fstream>
#include <TH1F.h>
#include <TF1.h>
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include <string>
#include <cmath>
#include <iostream>
#include <cstdlib>

#include "SttEvent.h"
#include "SttDetector.h"

#ifdef __MAKECINT__
#pragma link C++ class vector<UInt_t>+;
#pragma link C++ class vector<Int_t>+;
#pragma link C++ class vector<UShort_t>+;
#pragma link C++ class vector<UChar_t>+;
#pragma link C++ class SttEvent+;
#pragma link C++ class SttHit+;
#endif

//===================================================================
// Histograms
TH1F *h_EMC_ADC_channels_hits;


TH1F* h_stt_tdc_event_sizes;
TH1F* h_stt_tdc_channels;
TH1F* h_stt_tdc_leadTimes;

TH1F* h_stt_emc_pulser_timeDiff;

//
static const int emc_h_energy_size = 50;
TH1F *h_EMC_RawEnergy[emc_h_energy_size];
//
//===================================================================
// Constants
const int emc_Header_system_id = 0x5555;
const int stt_Header_system_id = 0xabcd; //0xFBBB;
std::map<UInt_t, int> stt_channel_offsets;

//
//===================================================================
// Event structure
UShort_t Header_status;
UInt_t SB_number;
//
//-------------------------------------------------------------------
// EMC
std::vector<UInt_t> emc_Cluster_local_time;
std::vector<UShort_t> emc_Cluster_diameter;
std::vector<UShort_t> emc_Cluster_2x;
std::vector<UShort_t> emc_Cluster_2y;
std::vector<UShort_t> emc_Cluster_N_hits;
//
std::vector<UInt_t> emc_Hits_local_time;
std::vector<UChar_t> emc_Hits_status;
std::vector<UShort_t> emc_Hits_ADC_channel;
std::vector<UShort_t> emc_Hits_Energy;
//
//-------------------------------------------------------------------
//STT

std::vector<UInt_t> stt_tdc_event_sizes;
std::vector<SttEvent> stt_tdc_hits;


SttDetector stt_det;


//===================================================================
// Zero event
void pd_Zero_Event(){
    // EMC
    emc_Cluster_local_time.clear();
    emc_Cluster_diameter.clear();
    emc_Cluster_2x.clear();
    emc_Cluster_2y.clear();
    emc_Cluster_N_hits.clear();
    //
    emc_Hits_local_time.clear();
    emc_Hits_status.clear();
    emc_Hits_ADC_channel.clear();
    emc_Hits_Energy.clear();
    //emc_Hits_cluster_index.clear();
    // STT 
    stt_tdc_event_sizes.clear();
    stt_tdc_hits.clear();
}
//
int emc_vector_reserve_size=0;
void pd_Reserve_Event(int Nsize){
    // EMC
    emc_vector_reserve_size = Nsize;
    emc_Cluster_local_time.reserve(Nsize);
    emc_Cluster_diameter.reserve(Nsize);
    emc_Cluster_2x.reserve(Nsize);
    emc_Cluster_2y.reserve(Nsize);
    emc_Cluster_N_hits.reserve(Nsize);
    //
    emc_Hits_local_time.reserve(Nsize);
    emc_Hits_status.reserve(Nsize);
    emc_Hits_ADC_channel.reserve(Nsize);
    emc_Hits_Energy.reserve(Nsize);
    // STT
    stt_tdc_event_sizes.reserve(Nsize);
    stt_tdc_hits.reserve(Nsize);
}


//===================================================================
#define MAKE_HST_IND(hstname,bins,minx,maxx,ind,tstr){\
    std::string tmpstr; \
    tmpstr = #hstname; \
    tmpstr += "_%2i"; \
    if(hstname[ind]) hstname[ind]->Reset(); \
    else { \
	sprintf(tstr,tmpstr.c_str(),i+1); \
	hstname[ind]=new TH1F(tstr,tstr,bins,minx,maxx); \
    } \
}
#define MAKE_HST2_IND(hstname,binsX,minx,maxx,binsY,miny,maxy,ind,tstr){\
    std::string tmpstr; \
    tmpstr = #hstname; \
    tmpstr += "_%2i"; \
    if(hstname[ind]) hstname[ind]->Reset(); \
    else { \
	sprintf(tsrt,tmpstr.c_str(),i+1); \
	hstname[ind]=new TH2F(tsrt,tsrt,binsX,minx,maxx,binsY,miny,maxy); \
    } \
}
#define MAKE_HST(hstname,bins,minx,maxx){\
    if(hstname) hstname->Reset(); \
    else \
	hstname=new TH1F(#hstname,#hstname,bins,minx,maxx); \
}
#define MAKE_HST2(hstname,bins,minx,maxx,binsy,miny,maxy){\
    if(hstname) hstname->Reset(); \
    else \
	hstname=new TH2F(#hstname,#hstname,bins,minx,maxx,binsy,miny,maxy); \
}

//===================================================================
void pd_init_hst(){
    char tstr[200];
    //
    MAKE_HST(h_EMC_ADC_channels_hits,60000,0,60000);
    
	for(int i=0;i<emc_h_energy_size;i++)
		MAKE_HST_IND(h_EMC_RawEnergy,6000,0,60000,i,tstr);


	MAKE_HST(h_stt_tdc_event_sizes, 100, 0, 100);

	MAKE_HST(h_stt_tdc_channels, 350, 0, 350);

	MAKE_HST(h_stt_tdc_leadTimes, 40000, 0, 40000);

	MAKE_HST(h_stt_emc_pulser_timeDiff, 5000, 0, 500);
}
#undef MAKE_HST
#undef MAKE_HST2
#undef MAKE_HST_IND
#undef MAKE_HST2_IND

//===================================================================
// Event processor
void pd_Event_Processor(){
    for(UInt_t h=0;h<emc_Hits_ADC_channel.size();h++){
	h_EMC_ADC_channels_hits->Fill(emc_Hits_ADC_channel[h]);
	if(emc_Hits_ADC_channel[h]<emc_h_energy_size)
	    h_EMC_RawEnergy[emc_Hits_ADC_channel[h]]->Fill(emc_Hits_Energy[h]);
    }
    //
    //Event printout
    /*printf("----------\n");
    hi = 0;
    for(UInt_t cl=0;cl<emc_Cluster_N_hits.size();cl++){
	printf("Cluster #%i: hits %i\n",cl,emc_Cluster_N_hits[cl]);
	printf("  Hits (Ch):");
	for(int h=hi;h<hi+emc_Cluster_N_hits[cl];h++)
	    printf(" %i;",emc_Hits_ADC_channel[h]);
	printf("\n");
	hi += cl,emc_Cluster_N_hits[cl];
    }*/
}

//===================================================================
// Reading and decoding input file
void PDAQ_RawDecoder_EMC_STT(char *in_file_name,char *out_file_name=0){
    pd_init_hst();
    //---------------------------------------------------------------
    // Open input file
    std::ifstream in_file(in_file_name);
    if(!in_file){
	std::cerr << "Can not open input file!\n";
	return;
	//std::exit(1);
    }
    //---------------------------------------------------------------


	SttEvent* stt_event = new SttEvent();

    // Open output file
    bool use_tree_output = false;
    TFile *ofile;
    TTree *tree;
    if(out_file_name){
	use_tree_output = true;
	//
	ofile = new TFile(out_file_name,"recreate");
	tree = new TTree("PDAQ_Events","PDAQ_Events");
	//.......................
	// Header variables
	tree->Branch("Header_status",&Header_status,"Header_status/s");
	tree->Branch("SB_number",&SB_number,"SB_number/i");
	//
	// EMC data
	tree->Branch("emc_Cluster_local_time",&emc_Cluster_local_time);
	tree->Branch("emc_Cluster_diameter",&emc_Cluster_diameter);
	tree->Branch("emc_Cluster_2x",&emc_Cluster_2x);
	tree->Branch("emc_Cluster_2y",&emc_Cluster_2y);
	tree->Branch("emc_Cluster_N_hits",&emc_Cluster_N_hits);
	//
	tree->Branch("emc_Hits_local_time",&emc_Hits_local_time);
	tree->Branch("emc_Hits_status",&emc_Hits_status);
	tree->Branch("emc_Hits_ADC_channel",&emc_Hits_ADC_channel);
	tree->Branch("emc_Hits_Energy",&emc_Hits_Energy);
	//.......................
	// STT data
	tree->Branch("stt_events", "SttEvent", &stt_event, 64000, 2);
	tree->Branch("stt_tdc_event_sizes", &stt_tdc_event_sizes);
    }
    //---------------------------------------------------------------
    UInt_t data4;
    Int_t Data_size;
    int n_bytes;
    UInt_t Event_SB_number=0;
    Int_t Header_system_id;
    Int_t t_Header_status;
    Int_t t_Header_system_id;
    UInt_t t_SB_number;

    Double_t doubleCntr =0;
    Double_t doubleCntr1 =0;

	// initialize stt data

	stt_channel_offsets[0xe100] = 0 * 49;
	stt_channel_offsets[0xe101] = 1 * 49;
	stt_channel_offsets[0xe102] = 2 * 49;
	stt_channel_offsets[0xe200] = 3 * 49;
	stt_channel_offsets[0xe201] = 4 * 49;
	stt_channel_offsets[0xe202] = 5 * 49;
	stt_channel_offsets[0xe203] = 6 * 49;


    //
    bool new_event=false;

double emc_pulser_time = 0;
    //
//cout<<endl;
    UInt_t N_events=0;
    while(!in_file.eof()){
	n_bytes = 0;	
	//
	// Word 1
	in_file.read((char*)&data4,4);
	n_bytes += 4;
	// Might be header of a new event
	if(data4 == 0xFAFAFAFA){ // new event
	    new_event = true;
	    in_file.read((char*)&data4,4);
	}
	UInt_t W1 = data4;
	Data_size = data4 & 0xffff;
	//
	// Word 2 should be 0xAAAAAAAA
	in_file.read((char*)&data4,4);
	n_bytes += 4;
	bool no_format_error = true;
	if(data4 != 0xAAAAAAAA){
	    no_format_error = false;
	    std::cerr << "Wrong header: ";
	    printf("NE %i; W1 %x; W2 %x\n",new_event,W1,data4);
	    while(data4 != 0xAAAAAAAA  && !in_file.eof()){
		in_file.read((char*)&data4,4);
		//printf("D: %x\n",data4);
		if(data4 != 0xAAAAAAAA) Data_size = data4 & 0xffff;
	    }
	}
	//
	// Word 3
	in_file.read((char*)&data4,4);
	n_bytes += 4;
	t_Header_system_id = data4 & 0xffff;
	t_Header_status = data4 >> 16;
	//
	// Word 4
	in_file.read((char*)&data4,4);
	n_bytes += 4;
	t_SB_number = data4;


	//
	//--------------------------------------------------------------
	// Event building
	if(t_SB_number > Event_SB_number){ // new event
	    N_events++;


	    if(new_event && no_format_error){
		//----------------------------
		// Rounding off previous event
		pd_Event_Processor();
		if(use_tree_output) {
			tree->Fill();

			stt_event->Clear();

//printf("------\n");
		}
	    } else if(!new_event){std::cerr << "! Not complete event!\n";}
	    new_event = false;
	    

//if(N_events == 40) return;

if (N_events % 10000 == 0) printf("%d\n", N_events);


	    //----------------------------
	    // Start new event
	    Event_SB_number = t_SB_number;
	    pd_Zero_Event();



			//emc_pulser_time = 0;
			//printf("New event\n");

	} else if(t_SB_number < Event_SB_number){ // Error!
	    std::cerr << "! Wrong order of SB_number: " << Event_SB_number << " " << t_SB_number << std::endl;
	    Event_SB_number = t_SB_number;
	    pd_Zero_Event();
	}
	//
	//
	SB_number = t_SB_number;
	Header_system_id = t_Header_system_id;
	Header_status = t_Header_status;

	//
	//--------------------------------------------------------------
	// EMC data processing
	if(Header_system_id == emc_Header_system_id){
	    // Cluster data
	    if(emc_vector_reserve_size < Data_size/8-2)
	        pd_Reserve_Event(Data_size/8-2);
	    while(n_bytes < Data_size){
	        // Header, w1
	        in_file.read((char*)&data4,4);
	        n_bytes += 4;
	        emc_Cluster_local_time.push_back(data4 >> 8); 

//printf("cluster time %f\n", (data4 >> 8) * (12.5 / 2048));
//emc_pulser_time = ((data4 >> 8) * (12.5 / 2048));

	        emc_Cluster_diameter.push_back(data4 & 0xff);
	        // Header, w2
	        in_file.read((char*)&data4,4);
	        n_bytes += 4;
	        emc_Cluster_N_hits.push_back(data4 & 0x3ff);
	        emc_Cluster_2x.push_back((data4 >> 10) & 0x3ff); 
	        emc_Cluster_2y.push_back((data4 >> 20) & 0x3ff);
		UInt_t emc_N_clusters = emc_Cluster_2y.size()-1;
	        emc_Cluster_2y[emc_N_clusters] = (emc_Cluster_2y[emc_N_clusters] << 3) || (data4 >> 30);
	        //
	        //--------
	        // Hits
	        if(emc_Cluster_N_hits[emc_N_clusters] * 8 + n_bytes <= Data_size)
	            for(Int_t h_index=0;h_index< emc_Cluster_N_hits[emc_N_clusters];h_index++){
		        //emc_Hits_cluster_index.push_back(emc_N_clusters);
		        // Hit, w1
		        in_file.read((char*)&data4,4);
		        n_bytes += 4;
		        emc_Hits_local_time.push_back(data4 >> 8);
		        emc_Hits_status.push_back(data4 & 0xff);
		        // Hit, w2
		        in_file.read((char*)&data4,4);
		        n_bytes += 4;
			emc_Hits_ADC_channel.push_back(data4 >> 16);
		        emc_Hits_Energy.push_back(data4 & 0xffff);
		    }
		else std::cerr << "Wrong packet length !!!" << std::endl;
	    }
	} else if(Header_system_id == stt_Header_system_id){ // STT data processing

		int stt_words_ctr = 0;

		bool find_tdc = false;
		bool find_size = false;
		bool find_hits = false;

		int tdc_id = 0;
		int tdc_size = 0;		
		int current_size = 0;

		UInt_t channel_nr = 0;
		UInt_t edge = 0;
		UInt_t fine = 0;
		UInt_t coarse = 0;
		UInt_t epoch = 0;

		double refTime = 0;

		double lastRise = 0;


		double x_offset = 13.105;
		double y2_offset = 71.705;
		double y4_offset = 55.305;
		double mod_width = 8.08;
		double ss = 0.505;

		UInt_t sub[2048];

	    	while(n_bytes < Data_size){
			
			// Header, w1
			in_file.read((char*)&data4,4);
			n_bytes += 4;

			if (stt_words_ctr > 1) {
				sub[stt_words_ctr] = 
					((data4 & 0xff) << 24) | 
					(((data4 >> 8) & 0xff) << 16) | 
					(((data4 >> 16) & 0xff) << 8) | 
					(((data4 >> 24) & 0xff));
			}

			++stt_words_ctr;

	    	}

		// process the buffered data

		// reverse the words order
		for(int i = 0; i < stt_words_ctr; i += 2) {
			UInt_t t = sub[i];
			sub[i] = sub[i + 1];
			sub[i + 1] = t;
		}

		// fix the 16b word shift
		for(int i = 0; i < stt_words_ctr; ++i) {
			sub[i] = (sub[i] & 0xffff0000) | (sub[i + 1] & 0xffff);
		}


		// now go through words as it supposed to be
		for(int i = 6; i < stt_words_ctr; ++i) { // skip the first headers, fixed size

			//printf("0x%08x\n", sub[i]);

			if (find_tdc == false) {
				tdc_id = sub[i] & 0xffff;
				find_tdc = true;

				//printf("Got TDC %x offset %d\n", tdc_id, stt_channel_offsets[tdc_id]);

				current_size = 0;

				tdc_size = (sub[i] >> 16) & 0xffff;
				find_size = true;

				//printf("Got TDC size %x\n", tdc_size);

				stt_tdc_event_sizes.push_back(tdc_size);
				h_stt_tdc_event_sizes->Fill(tdc_size);

				lastRise = 0;
			}
			else if (find_hits == false) {

				if (stt_channel_offsets.find(tdc_id) != stt_channel_offsets.end()) { // decode only registered TDCs

					if (((sub[i] >> 28) & 0xf) == 0x8) {  // hit marker

						channel_nr = ((sub[i] >> 22) & 0x7f);
						edge = ((sub[i] >> 11) & 0x1);
						fine = ((sub[i] >> 12) & 0x3ff);
						coarse = (sub[i] & 0x7ff);
	
						h_stt_tdc_channels->Fill(channel_nr);

						double time = (double) ((((unsigned)epoch) << 11) * 5.0);
						time += ( (coarse * 5.) - (fine / 100.0) );

						if (channel_nr == 0) { // ref time
							refTime = time;


							SttHit* a = stt_event->AddHit(channel_nr + stt_channel_offsets[tdc_id]);
							a->leadTime = time;
							a->trailTime = 0;
							a->isRef = true;

							//printf("Ref R: %f on channel %d\n", a->leadTime, channel_nr + stt_channel_offsets[tdc_id]);
						}	
						else {
							if (edge == 1) {  // rising edge
								h_stt_tdc_leadTimes->Fill(time - refTime);

								lastRise = refTime - time;

								//printf("rel rising %f sb: %f on channel %d\n", (time - refTime), 38400 + (time - refTime), channel_nr + stt_channel_offsets[tdc_id]);

								//h_stt_emc_pulser_timeDiff->Fill(38400 + (time - refTime) - emc_pulser_time);
							}
							else {  // falling edge

								if (lastRise != 0) { // only in case there was a rising to pair
							

							//cout<<channel_nr + stt_channel_offsets[tdc_id]<<"\t"<<sizeof(stt_event)<<endl;

							bool doubleHit = false;

							for ( Int_t ui=0; ui<stt_event->totalNTDCHits; ui++)
							{
								if ( ((SttHit*)stt_event->tdc_hits->ConstructedAt(ui))->channel == channel_nr + stt_channel_offsets[tdc_id]) {
									if ( ((SttHit*)stt_event->tdc_hits->ConstructedAt(ui))->leadTime == lastRise) {
										//cout<<"Double hit :"<<endl;
										doubleHit = true;
										doubleCntr++;
									}
								}
								
								doubleCntr1++;
							}

//cout << " THE TDC_HITS   :" <<stt_event->tdc_hits->ConstructedAt()<<endl;
									//cout<<channel_nr+stt_channel_offsets[tdc_id]<<endl;
				if (doubleHit == false) 
				{
									SttHit* a = stt_event->AddHit(channel_nr + stt_channel_offsets[tdc_id]);
									a->leadTime = lastRise;
									a->trailTime = refTime - time;
									a->tot = a->leadTime - a->trailTime;
									a->isRef = false;

									detLoc l = stt_det.GetDetectorLocFromTDCChannel(channel_nr + stt_channel_offsets[tdc_id]);

									a->layer = l.layer;
									a->module = l.module;
									a->fee = l.fee;
									a->fee_channel = l.channel_no;
									a->cell = (32 * (l.module -1)) + (16 * (l.fee -1)) + (16-(l.channel_no-1));

									//cout << a->cell << endl;

										if (a->layer ==1){
											a->x = x_offset + ((a->module-1) * mod_width) + (a->fee * mod_width) - a->fee_channel*ss;
											a->y = 0;

												if (a->fee_channel%2==0){
													a->z = 1.01;
												}

												else {
													  a->z = 0;
												}

										}


										else if ( a->layer ==2){
											a->y = y2_offset + ((a->module-1) * mod_width) + (a->fee * mod_width) - a->fee_channel*ss;
											a->x = 0;

											if (a->fee_channel%2==0){
												a->z = 12.0;
											}

											else {
												  a->z = 13.01;
											}

										}


										else if (a->layer ==3){
											a->x = x_offset + ((a->module-1) * mod_width) + (a->fee * mod_width) - a->fee_channel*ss;
											a->y = 0;

												if (a->fee_channel%2==0){
													a->z = 28.51;
												}

												else {
													  a->z = 27.5;
												}
										}

										else if ( a->layer ==4){
											a->y = y4_offset + ((a->module-1) * mod_width) + (a->fee * mod_width) - a->fee_channel*ss;
											a->x = 0;

											if (a->fee_channel%2==0){
												a->z = 39.59;
											}

											else {
												  a->z = 40.61;
											}

										}

					//printf("hit R: %f F: %f on channel %d\n", a->leadTime, a->trailTime, channel_nr + stt_channel_offsets[tdc_id]);
					//printf("det_loc: %d %d %d %d \n", l.layer, l.module, l.fee, l.channel_no);

								}
							}
						}

					}
				}

					else if (((sub[i] >> 28) & 0xf) == 0x6) {  // epoch counter
						epoch = sub[i] & 0xffffff;

					}
				}

				if (current_size == tdc_size - 1) {
					find_tdc = false;
					find_size = false;
					find_hits = false;
				}

				++current_size;
			}
		}


	} 
	else 
	{ 
	// skip data
	    while(n_bytes < Data_size)
	    {
	        // Header, w1
	        in_file.read((char*)&data4,4);
	        n_bytes += 4;
	    }
	}

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    }

	 cout<<"Repeated hits :"<<doubleCntr<<"/"<<doubleCntr1<<endl;

    in_file.close();
    if(use_tree_output){ printf("writing file\n");
	tree->Write();
	ofile->Close();
    }
    std::cout << "Total number of processed events: " << N_events << std::endl;
}
