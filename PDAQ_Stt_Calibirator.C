#include <fstream>
#include <TH1F.h>
#include <TF1.h>
#include <TLinearFitter.h>
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include <string>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <TGraph.h>
#include <math.h>
#include <cstdlib>
#include <TLinearFitter.h>

#include "panda_subsystem.h"
#include "panda_subsystem_stt.h"
#include "panda_subsystem_sb.h"
#include "panda_stt_cal.h"
#include "SttDetector.h"


#include "TRandom.h"
#include "SttRawHit.h"
#include "SttHit.h"
#include "SttEvent.h"
#include "Stt_Cal_Event.h"

#pragma link C++ class SttRawHit+;
#pragma link C++ class SttHit+;
#pragma link C++ class SttEvent+;
#pragma link C++ class Stt_Cal_Event+;

#pragma link C++ class PandaSubsystem+;
#pragma link C++ class PandaSubsystemSTT+;
#pragma link C++ class PandaSubsystemSB+;
#pragma link C++ class PandaSttCal+;

                           
using namespace std;


bool f_sttHitCompareLeadTime(SttHit* a, SttHit* b)
{
    return (a->leadTime < b->leadTime);
}


Bool_t PDAQ_Stt_Calibirator(void)
{

PandaSubsystemSTT* STT = 0;
//PandaSubsystemSTT* raw_stt = new PandaSubsystemSTT();
//PandaSubsystemSTT* stt = new PandaSubsystemSTT();


PandaSttCal* CAL = new PandaSttCal();

Stt_Cal_Event* stt_event = &(CAL->stt_cal);
//SttEvent* raw_event = &(stt->stt_raw);



SttDetector stt_det;


    TFile file("PDAQ_Stt.root", "READ");
    TTree* tree = (TTree*)file.Get("PDAQ_EMC_STT_cluster_analysis");
    if (!tree) {
        std::cerr << "Tree doesn't exists" << std::endl;
        return 1;
    }

    tree->Print();
    cout<<"tree loading: "<<tree->SetBranchAddress("STT", &STT)<<endl;


 Double_t repeat =0;
 Double_t All_repeat =0;
 int good_counter =0;


	Int_t nentries = (Int_t)tree->GetEntries();
    std::cout << nentries << "\n";
	

///MOVE OUT////////////
        double x_offset = 13.105;
        double y2_offset = 71.705;
        double y4_offset = 55.305;
        double z_offset = 0;
        double z2_offset = 12;
        double z3_offset = 27.5;
        double z4_offset = 40.6;

        double mod_width = 8.08;
        double straw_diameter = 0.505;
        double straws_per_fee = 16;


     TFile* Ttree = new TFile("PDAQ_Stt.root", "UPDATE");
     TTree* PDAQ_EMC_STT_cluster_analysis = new TTree("PDAQ_EMC_STT_cluster_analysis", "PDAQ_EMC_STT_cluster_analysis");
    
    PDAQ_EMC_STT_cluster_analysis->Branch("STT_CAL", "PandaSttCal", &CAL, 64000, 99);
    //PDAQ_EMC_STT_cluster_analysis->Branch("STT_RAW", "PandaSubsystemSTT", &STT, 64000, 99);

    Long_t global_cnt = 0;

     for (Long_t e = 0; e < nentries; e++)
    {
    	tree->GetEntry(e);

        int hitsInEvent = 0;

        //bool emcCosmic = false;
        bool sttCosmic = false;
        std::vector<SttHit*> vec_filterLeadTime;

        std::vector<SttHit*> vec_L1;
        std::vector<SttHit*> vec_L2;
        std::vector<SttHit*> vec_L3;
        std::vector<SttHit*> vec_L4;

        if (e % 10000 == 0)
        {
            printf("%d\n", e);
        }

            PDAQ_EMC_STT_cluster_analysis->Fill();
            stt_event->CalClear();


        for (int i = 0; i < STT->stt_raw.totalNTDCHits; i++)
        {
            SttRawHit* hit  = (SttRawHit*)STT->stt_raw.tdc_hits->ConstructedAt(i); // retrieve particular hit
            
            SttHit* cal_hit = stt_event->AddCalHit(hit->channel);
                      
            cal_hit->channel = hit->channel;
            cal_hit->leadTime = hit->leadTime;
            cal_hit->trailTime = hit->trailTime;
            cal_hit->tot = hit->tot;
            cal_hit->isRef = hit->isRef;

if (hit->tot > 0)
{
 good_counter++;
 }

            detLoc l = stt_det.GetDetectorLocFromTDCChannel(hit->channel);
       
            cal_hit->layer = l.layer;
            cal_hit->module = l.module;
            cal_hit->fee = l.fee;
            cal_hit->fee_channel = l.channel_no;
            cal_hit->cell = ((2*straws_per_fee) * (l.module -1)) + (straws_per_fee * (l.fee -1)) + (straws_per_fee-(l.channel_no-1));

            vec_filterLeadTime.clear();
            vec_filterLeadTime.push_back(cal_hit);


                    if (cal_hit->layer ==1){
                     cal_hit->x = x_offset + (((cal_hit->module)-1) * mod_width) + ((cal_hit->fee) * mod_width) - ((cal_hit->fee_channel)*straw_diameter);
                     cal_hit->y = 0;

                         if ((cal_hit->fee_channel)%2==0){
                             cal_hit->z = (2*(straw_diameter))+z_offset;
                         }

                         else {
                               cal_hit->z = z_offset;
                         }

                    }


                    else if (cal_hit->layer ==2){
                     cal_hit->y = y2_offset + (((cal_hit->module)-1) * mod_width) + ((cal_hit->fee) * mod_width) - ((cal_hit->fee_channel)*straw_diameter);
                     cal_hit->x = 0;

                     if ((cal_hit->fee_channel)%2==0){
                         cal_hit->z = z2_offset;
                     }

                     else {
                           cal_hit->z = (2*(straw_diameter))+z2_offset;
                     }

                    }


                    else if (cal_hit->layer ==3){
                     cal_hit->x = x_offset + (((cal_hit->module)-1) * mod_width) + ((cal_hit->fee) * mod_width) - ((cal_hit->fee_channel)*straw_diameter);
                     cal_hit->y = 0;

                         if ((cal_hit->fee_channel)%2==0){
                             cal_hit->z = (2*(straw_diameter))+z3_offset;
                         }

                         else {
                               cal_hit->z = z3_offset;
                         }
                    }

                    else if (cal_hit->layer ==4){
                     cal_hit->y = y4_offset + (((cal_hit->module)-1) * mod_width) + ((cal_hit->fee) * mod_width) - ((cal_hit->fee_channel)*straw_diameter);
                     cal_hit->x = 0;

                     if ((cal_hit->fee_channel)%2==0){
                         cal_hit->z = z4_offset;
                     }

                     else {
                           cal_hit->z = (2*(straw_diameter))+z4_offset;
                     }

                    }

            }

    }// over events

 
    PDAQ_EMC_STT_cluster_analysis->Write();
    cout << "Repeated entries  :"<< repeat<<"/"<<All_repeat<<endl;  
    cout << "Good Hits : "<<good_counter<<endl;
    // if (fp)
    //     fclose(fp);


return 0;
}

