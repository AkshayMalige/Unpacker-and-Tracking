#include <fstream>
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

#include "SttHit.h"
#include "SttEvent.h"
// #include "cluster.h"
                          
#include "panda_subsystem.h"
#include "panda_subsystem_stt.h"
#include "panda_subsystem_sb.h"
#include "panda_stt_cal.h"
#include "panda_stt_track.h"
#include "panda_stt_driftradius.h"


#pragma link C++ class SttHit+;
#pragma link C++ class SttEvent+;

#pragma link C++ class PandaSubsystem+;
#pragma link C++ class PandaSubsystemSTT+;
#pragma link C++ class PandaSubsystemSB+;
#pragma link C++ class PandaSttCal+;
#pragma link C++ class PandaSttTrack+;
#pragma link C++ class PandaSttDrift+;



using namespace std;



Bool_t PDAQ_DriftRadius(void)
{




PandaSubsystemSTT* STT_RAW = new PandaSubsystemSTT();
PandaSttCal* STT_CAL = new PandaSttCal();
PandaSttTrack* STT_TRACKS = new PandaSttTrack();
PandaSttDrift* STT_DRIFT = new PandaSttDrift();

    std::vector<Int_t> vec_dr_channel;
    std::vector<Int_t> vec_dr_correction;
    Int_t ar_dr_channel[296];
    Int_t ar_dr_correction[296];


    TFile file("stage3.root", "READ");
    TTree* tree = (TTree*)file.Get("PDAQ_EMC_STT_cluster_analysis");
    if (!tree) {
        std::cerr << "Tree doesn't exists" << std::endl;
        return 1;
    }
    tree->Print();



    tree->SetBranchAddress("STT_TRACKS", &STT_TRACKS);


    TFile* Ttree = new TFile("stage4.root", "RECREATE");
     TTree* PDAQ_EMC_STT_cluster_analysis =  new TTree("PDAQ_EMC_STT_cluster_analysis", "PDAQ_EMC_STT_cluster_analysis");


    PDAQ_EMC_STT_cluster_analysis->Branch("STT_RAW", "PandaSubsystemSTT", &STT_RAW, 64000, 99);
    PDAQ_EMC_STT_cluster_analysis->Branch("STT_CAL", "PandaSttCal", &STT_CAL, 64000, 99);
    PDAQ_EMC_STT_cluster_analysis->Branch("STT_TRACKS", "PandaSttTrack", &STT_TRACKS, 64000, 99);
    PDAQ_EMC_STT_cluster_analysis->Branch("STT_FINAL", "PandaSttDrift", &STT_DRIFT, 64000, 99);



    Int_t iev = (Int_t)tree->GetEntries();
    cout << "number of entries in tree:" << iev << endl << endl;

    for (Int_t i = 0; i < iev; i++) 
    {
        tree->GetEntry(i);
        cout << endl
             << endl;

        if (i%10000 ==0)
        {
            cout << "entry no. " << i << endl;
        }

        for (int n = 0; n < STT_TRACKS->stt_track_can.totalNTDCHits; n++)
        {

            SttHit* track_can  = (SttHit*)STT_TRACKS->stt_track_can.tdc_hits->ConstructedAt(n); // retrieve particular hit

            // vec_stthits.push_back(cal_hit);
            // vec_Allhits.push_back(cal_hit);

        }

    }



    for ( Int_t ef=0; ef< vec_All_tracks.size(); ef++)
    {
        Int_t FrontEnd = ((4*(vec_All_tracks[ef]->layer - 1))+(2*(vec_All_tracks[ef]->module)-1)+((vec_All_tracks[ef]->fee)-1));
        h_Straw_DriftTime->Fill(vec_All_tracks[ef]->channel,vec_All_tracks[ef]->drifttime);
        h_Fee_DriftTime->Fill(FrontEnd,vec_All_tracks[ef]->drifttime);
        h_Fee[FrontEnd]->Fill(vec_All_tracks[ef]->drifttime);
        h_FrontNO->Fill(FrontEnd);
      }


for ( Int_t sqq=0; sqq< vec_All_tracks.size(); sqq++)
 {
   if ((4*(vec_All_tracks[sq]->layer - 1))+(2*(vec_All_tracks[sq]->module)-1)+((vec_All_tracks[sq]->fee)-1) == ch)
    {
        h_Front->Fill(vec_All_tracks[sq]->drifttime);
        cout<<"FRONT END INDEX "<<ch<<"\t"<<(4*(vec_All_tracks[sq]->layer - 1))+(2*(vec_All_tracks[sq]->module)-1)+((vec_All_tracks[sq]->fee)-1)<<endl;
     }

}


for (Int_t ch = 1; ch<2; ch++)
{
     for ( Int_t sq=0; sq< vec_All_tracks.size(); sq++)
     {
         if (vec_All_tracks[sq]->layer==1 && vec_All_tracks[sq]->module && vec_All_tracks[sq]->fee==1)
         {cout<< " channel check  : "<<vec_All_tracks[sq]->layer<<"\t"<<vec_All_tracks[sq]->module<<"\t"<<vec_All_tracks[sq]->fee<<"\t"<<vec_All_tracks[sq]->cell<<"\t"<<vec_All_tracks[sq]->channel<<"\t"<<(4*(vec_All_tracks[sq]->layer - 1))+(2*(vec_All_tracks[sq]->module)-1)+((vec_All_tracks[sq]->fee)-1)<<endl;
        }
        if ((4*(vec_All_tracks[sq]->layer - 1))+(2*(vec_All_tracks[sq]->module)-1)+((vec_All_tracks[sq]->fee)-1) == ch)
        {
            h_Front->Fill(vec_All_tracks[sq]->drifttime);
            cout<<ch<<"\t"<<(4*(vec_All_tracks[sq]->layer - 1))+(2*(vec_All_tracks[sq]->module)-1)+((vec_All_tracks[sq]->fee)-1)<<endl;
         }
         //else cout<<"FRONT END INDEX MISMATCH   "<<ch<<"\t"<<(4*(vec_All_tracks[sq]->layer - 1))+(2*(vec_All_tracks[sq]->module)-1)+((vec_All_tracks[sq]->fee)-1)<<endl;

    }

    Int_t maximum = h_Front->GetBinContent(h_Front->GetMaximumBin());
    Int_t y_th = maximum/10;
    Int_t gbinx = 100 + h_Front->FindFirstBinAbove(y_th,1);
    cout<<"FrontEnd : "<<ch<<"| Y max : "<<maximum<<"|  threshold : "<<y_th<<"|  bin@th :"<<gbinx<<endl;
    h_Front->Reset();

    vec_dr_channel.push_back(ch);
    vec_dr_correction.push_back(gbinx);
 }

 cout<<"check "<<vec_dr_channel.size()<<"\t"<<vec_dr_correction.size()<<endl;
for (Int_t c=0; c<16; c++)
{
 ar_dr_channel[c] = vec_dr_channel[c];
 ar_dr_correction[c] = vec_dr_correction[c];
 }

TGraph* dr_correction = new TGraph(vec_dr_channel.size(), ar_dr_channel, ar_dr_correction);
dr_correction->SetName("dr_correction");
dr_correction->Write();
h_straw_mean_straw->Write();
/////////////////////////////////////////////////////////END of Drift Time calliberation////////////////////////////////////////////////

std::vector< vector<Double_t> > vec_Fee_drift_time;

for (Int_t ao=1; ao< 17; ao++)
{
     std::vector<Double_t>vec_inFee_drift_time;
     vec_inFee_drift_time.clear();

    for (Int_t ae=0; ae< vec_All_tracks.size(); ae++)
    {
        Int_t FeNo =  ((4*(vec_All_tracks[ae]->layer - 1))+(2*(vec_All_tracks[ae]->module)-1)+((vec_All_tracks[ae]->fee)-1));
        if (FeNo == ao)
        {
            vec_inFee_drift_time.push_back(vec_All_tracks[ae]->drifttime);

         }

     }

     vec_Fee_drift_time.push_back(vec_inFee_drift_time);
}

for (Int_t ij=0; ij<vec_Fee_drift_time.size(); ij++)
        {
            Int_t driftTimeCounter2=0;

            Double_t min_DT = vec_Fee_drift_time.at(ij).at(0);
            for (Int_t rr = 0; rr < vec_Fee_drift_time.at(ij).size(); rr++)
            {
                if (vec_Fee_drift_time.at(ij).at(rr) < min_DT)
                    min_DT=vec_Fee_drift_time.at(ij).at(rr);
            }
            cout<<"Minimum : "<<"\t"<<vec_Fee_drift_time.size()<<"\t"<<ij<<"\t"<<vec_Fee_drift_time.at(ij).size()<<endl;
               
            for (Int_t r = 0; r < vec_Fee_drift_time.at(ij).size(); r++)
            {
                vec_test.push_back(vec_Fee_drift_time.at(ij).at(r)-min_DT);
                driftTimeCounter2++;
            }

//Sort the vector

            std::sort(vec_test.begin(), vec_test.end());
            cout << "counttts:  " << driftTimeCounter2 << endl;

            // Ignore the decimals of the drifttimes.

            for (int t = 0; t < vec_test.size(); t++)
            {
                // cout << seeme[t] << endl;
                int x = (vec_test[t] * 100) / 100;
                vec_roundoff.push_back(x);
            }
        //     // Calculate the occurances of each drift time.

            for (int j = 0; j < vec_test.size(); j++)
            {
                // cout << vec1[j] << endl;
                int occ_count = 1;
                int limit = (vec_test.size() - 1);

                while (j < limit && vec_roundoff[j] == vec_roundoff[j + 1])
                {
                    occ_count++;
                    j++;
                }
                vec_occurance.push_back(occ_count);
                vec_pos_DT.push_back(vec_roundoff[j]);
                // cout<< vec_roundoff[j] << "\t" << occ_count <<  endl;
            }

        // Calculate the cummulative sum (integral) of the occurances.

            for (int m = 0; m < vec_occurance.size(); m++)
            {
                int sum = 0;

                for (int k = 0; k < m + 1; k++)
                {
                    sum += vec_occurance[k];
                }

                vec_cumsum.push_back(sum);
            }

         //Calculate the drift radius.

            Int_t max_dr = driftTimeCounter2;
            Int_t dt_range = vec_cumsum.size();

            Double_t a1[dt_range];
            Double_t b1[dt_range];
            Double_t C = 0;
            Double_t R = 0.505;
            Double_t drift_radius = 0;

            C = max_dr / R;


            for (int e = 0; e < dt_range; e++)
            {
                drift_radius = vec_cumsum[e] / C;
                vec_drift_radius.push_back(drift_radius);
            }

            for (int l = 0; l < vec_pos_DT.size(); l++)
            {
                cout << "Drift Time: "<< vec_pos_DT[l] << "\t" << vec_drift_radius[l] << endl;
                a1[l] = vec_pos_DT[l];
                b1[l] = vec_drift_radius[l];
            }

                char buff[200];
                sprintf(buff, "fee_drift_%d", ij);    
                TGraph* gDriftRadius = new TGraph(dt_range, a1, b1);
                gDriftRadius->SetName(buff);
                gDriftRadius->SetTitle(buff);
                gDriftRadius->Write();
                
                vec_test.clear();
                vec_roundoff.clear();
                vec_occurance.clear();
                vec_pos_DT.clear();
                vec_cumsum.clear();
                vec_drift_radius.clear();
         }

    return 0;
}
