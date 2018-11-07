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


#include "TRandom.h"
#include "SttHit.h"
#include "SttEvent.h"
                           
using namespace std;

bool f_sttHitCompareLeadTime(SttHit* a, SttHit* b)
{
    return (a->leadTime < b->leadTime);
}


Bool_t PDAQ_Cal(void)
{

PandaSubsystemSTT* STT = 0;



    TFile file("tst.root", "READ");
    TTree* tree = (TTree*)file.Get("PDAQ_Events");
    if (!tree) {
        std::cerr << "Tree doesn't exists" << std::endl;
        return 1;
    }
    tree->Print();


 TH1F* h_STT_layers = new TH1F("h_STT_layers", "h_STT_layers",  10, 0, 10);
 TH1F* h_STT_channelsWithoutRef = new TH1F("h_STT_channelsWithoutRef", "h_STT_channelsWithoutRef", 350, 0, 350);
 TH1F* h_STT_tot = new TH1F("h_STT_tot", "h_STT_tot", 500, 0, 500);
 TH1F* h_STT_channels_4layers = new TH1F("h_STT_channels_4layers", "h_STT_channels_4layers", 500, 0, 500);
 TH1F* h_STT_layerhits = new TH1F("h_STT_layerhits", "h_STT_layerhits", 10, 0, 10);
 TH1F* h_STT_layerMult = new TH1F("h_STT_layerMult", "h_STT_layerMult", 17, 0, 17);
 TH1F* h_stt_cosmic = new TH1F("h_stt_cosmic", "h_stt_cosmic", 5, 0, 5);
 TH1F* h_STT_layerhitsmult = new TH1F("h_STT_layerhitsmult", "h_STT_layerhitsmult", 10, 0, 10);
 TH1F* h_STT_counts = new TH1F("h_STT_counts", "h_STT_counts", 10, 0, 10);
 TH2F* h_STT_TOTvsCh = new TH2F("h_STT_TOTvsCh", "h_STT_TOTvsCh", 300, 0, 300, 500, 0, 500);

 Double_t repeat =0;
 Double_t All_repeat =0;


	Int_t nentries = (Int_t)tree->GetEntries();
    std::cout << nentries << "\n";
	
	tree->SetBranchAddress("STT", &STT);



    std::vector<Double_t> vec_Stage_DT;
    std::vector<Double_t> vec_Stage_x;
    std::vector<Double_t> vec_Stage_y;
    std::vector<Double_t> vec_Stage_z;
    std::vector<Double_t> vec_Stage_layer;
    std::vector<Double_t> vec_Stage_module;
    std::vector<Double_t> vec_Stage_fee;
    std::vector<Double_t> vec_Stage_cell;
    std::vector<Double_t> vec_Stage_fee_ch;
    std::vector<Double_t> vec_Stage_tdc_ch;
    std::vector<Double_t> vec_Stage_leadtime;
    std::vector<Double_t> vec_Stage_trailtime;

    TFile* Ttree = new TFile("PDAQ_EMC_STT_cluster_analysis.root", "RECREATE");
    TTree* PDAQ_EMC_STT_cluster_analysis = new TTree("PDAQ_EMC_STT_cluster_analysis", "PDAQ_EMC_STT_cluster_analysis");

    //PDAQ_EMC_STT_cluster_analysis->Branch("vec_Stage_DT", &vec_Stage_DT);
    PDAQ_EMC_STT_cluster_analysis->Branch("vec_Stage_layer", &vec_Stage_layer);
    PDAQ_EMC_STT_cluster_analysis->Branch("vec_Stage_x", &vec_Stage_x);
    PDAQ_EMC_STT_cluster_analysis->Branch("vec_Stage_y", &vec_Stage_y);
    PDAQ_EMC_STT_cluster_analysis->Branch("vec_Stage_z", &vec_Stage_z);
    PDAQ_EMC_STT_cluster_analysis->Branch("vec_Stage_module", &vec_Stage_module);
    PDAQ_EMC_STT_cluster_analysis->Branch("vec_Stage_fee", &vec_Stage_fee);
    PDAQ_EMC_STT_cluster_analysis->Branch("vec_Stage_fee_ch", &vec_Stage_fee_ch);
    PDAQ_EMC_STT_cluster_analysis->Branch("vec_Stage_cell", &vec_Stage_cell);
    PDAQ_EMC_STT_cluster_analysis->Branch("vec_Stage_tdc_ch", &vec_Stage_tdc_ch);
    PDAQ_EMC_STT_cluster_analysis->Branch("vec_Stage_leadtime", &vec_Stage_leadtime);
    PDAQ_EMC_STT_cluster_analysis->Branch("vec_Stage_trailtime", &vec_Stage_trailtime);


    Long_t global_cnt = 0;

     for (Long_t e = 0; e < 500000; e++)
    {
    	tree->GetEntry(e);

    	//cout<<STT->stt_raw.totalNTDCHits<<endl;

    	// for (int i = 0; i < STT->stt_raw.totalNTDCHits; i++) {
    	// 	SttHit* hit = (SttHit*)STT->stt_raw.tdc_hits->ConstructedAt(i);
		//cout<<hit->channel<<endl;


        if (e % 10000 == 0)
        {
            printf("%d\n", e);
        }
        // if (e == 18000)
        //     break;

        // STT Pre Processing
        int hitsInEvent = 0;

        //bool emcCosmic = false;
        bool sttCosmic = false;
        std::vector<SttHit*> vec_filterLeadTime;

        std::vector<SttHit*> vec_L1;
        std::vector<SttHit*> vec_L2;
        std::vector<SttHit*> vec_L3;
        std::vector<SttHit*> vec_L4;

        //double emcTime = 0;
        double a;
        double b;
        double a_err;
        double b_err;

        bool emcres = false;

        SttHit* hitOnLayer[4][500];
        memset(hitOnLayer, 0, 4*500*sizeof(SttHit*));
        int hitMultOnLayer[4];
        int layerCounterr = 0;
        for (int i = 0; i < 4; i++)
        {
            hitMultOnLayer[i] = 0;
        }

        for (int i = 0; i < STT->stt_raw.totalNTDCHits; i++)
        {
            SttHit* hit  = (SttHit*)STT->stt_raw.tdc_hits->ConstructedAt(i); // retrieve particular hit

            int tdc_num = hit->channel / 49;
            // hit on reference channel
            if (hit->isRef == true)
            {
            }
            // hit on normal channel
            else
            {
                h_STT_channelsWithoutRef->Fill(hit->channel);
                h_STT_tot->Fill(hit->tot);
                h_STT_layers->Fill(hit->layer);
                h_STT_counts->Fill(0);

                if (hit->layer == 0)
                {
                    printf("ERROR: hit->layer %d %d %d\n", hit->layer, hit->channel, hit->fee);
                    continue;
                }

                hitOnLayer[hit->layer - 1][hitMultOnLayer[hit->layer - 1]] = hit;

                hitMultOnLayer[hit->layer - 1]++;
            }

            hitsInEvent++;
        } // end of loop over hits

        bool good_layers = true;
        for (int c = 0; c < 4; c++)
        {
            if (hitMultOnLayer[c] != 1)
            {
                 good_layers = false;
                 break;
            }
        }
        if(good_layers)
            h_STT_layerMult->Fill(1);
        else
            h_STT_layerMult->Fill(0);

        // find the number of layers hit
        int layerCounter = 0;

        for (int i = 0; i < 4; i++)
        {
            if (hitMultOnLayer[i] > 0)
                layerCounter++;
        }
        h_STT_layerhits->Fill(layerCounter);

       // condition where all 4 layers were hit
        if (layerCounter == 4)
        {
            h_STT_channels_4layers->Fill(
                hitMultOnLayer[0] + hitMultOnLayer[1] + hitMultOnLayer[2] + hitMultOnLayer[3]);
            h_STT_counts->Fill(1);

            double leadTimesOfHits[2000];
            std::vector<SttHit*> vec_leadTime;
            std::vector<double> sumT;
            int hitsCtr = 0;
            int filtercnt = 0;
            int fil_max = 300;
            int s = 8;
            double ldiff = 0;

            for (int l = 0; l < 4; l++)
            {
                for (int h = 0; h < hitMultOnLayer[l]; h++)

                {
                    vec_leadTime.push_back(hitOnLayer[l][h]);

                    hitsCtr++;

                    if (hitMultOnLayer[l] > 1)
                    {
                        h_STT_layerhitsmult->Fill(h);
                    }
                }
            }

// //Check for repeated entries of a hit

            for(Int_t je=0; je<vec_leadTime.size()-1;je++)
            {
                //cout << "All entries  :  " <<"\t"<<" Lead Time : "<< vec_leadTime[je]->leadTime<<"\t" << " layer : "<< vec_leadTime[je]->layer<<"\t"<< "module : "<< vec_leadTime[je]->module<<"\t"<< " fee : "<< vec_leadTime[je]->fee<<"\t" << "FEE_Ch : "<< vec_leadTime[je]->fee_channel<<"\t"<<endl;
                if ((vec_leadTime[je+1]->leadTime) == (vec_leadTime[je]->leadTime) && (vec_leadTime[je+1]->channel == vec_leadTime[je]->channel))
                {
                    repeat++;
                    printf("{ LT,l,m,c,cf=%d,%d,%2d,%2d}{ LT1,l1,m1,c1,cf1=%d,%d,%2d,%2d}", vec_leadTime[je]->layer,vec_leadTime[je]->module,vec_leadTime[je]->fee,vec_leadTime[je]->fee_channel,vec_leadTime[je+1]->layer,vec_leadTime[je+1]->module,vec_leadTime[je+1]->fee,vec_leadTime[je+1]->fee_channel);
                    cout<<vec_leadTime[je]->leadTime<<" "<<vec_leadTime[je]->tot<<"\t"<<vec_leadTime[je+1]->leadTime<<" "<<vec_leadTime[je]->tot<<endl;    
                 }
                 All_repeat++;
             }

            std::sort(vec_leadTime.begin(), vec_leadTime.end(), f_sttHitCompareLeadTime);
            vec_filterLeadTime.clear();

            if (vec_leadTime.size() > 7)
            {
                h_STT_counts->Fill(2);

                for (int v = 0; v < vec_leadTime.size(); v++)
                { // iterate over collected and sorted hits
                    vec_filterLeadTime.clear();
                    filtercnt = 1;

                    SttHit* h = vec_leadTime.at(v);
                    vec_filterLeadTime.push_back(h);


                    for (int vv = 0; vv < vec_leadTime.size(); vv++)
                    { // check each vs each if they fit into the window
                        if (vv == v)    continue;
                        if ((fabs(vec_leadTime[v]->leadTime - vec_leadTime[vv]->leadTime) < fil_max) )

                        {
                            SttHit* hh = vec_leadTime.at(vv);
                            vec_filterLeadTime.push_back(hh);
                            filtercnt++;
                        }
                        else
                        { // in case the hit is outside the window break and start next iteration
                            // with the next hit
                            break;
                            vec_filterLeadTime.clear();

                        }
                    }
                }
            }

            //  in case we have at least 8 hits within timewindow go with tracking
            if (vec_filterLeadTime.size() > 4)
            {

                sttCosmic = true;

                for (int y = 0; y < vec_filterLeadTime.size(); y++)
                {

                    if (vec_filterLeadTime[y]->layer == 1)
                    {
                        vec_L1.push_back(vec_filterLeadTime.at(y));
                    }


                    else if (vec_filterLeadTime[y]->layer == 2)
                    {
                        vec_L2.push_back(vec_filterLeadTime.at(y));
                    }


                    else if (vec_filterLeadTime[y]->layer == 3)
                    {
                        vec_L3.push_back(vec_filterLeadTime.at(y));
                    }


                    else if (vec_filterLeadTime[y]->layer == 4)
                    {
                        vec_L4.push_back(vec_filterLeadTime.at(y));
                    }

                    h_STT_TOTvsCh->Fill(vec_filterLeadTime[y]->channel, vec_filterLeadTime[y]->tot);
                }
            }

         } // end of if with 4 layers

	               // vec_Stage_DT.clear();
	                vec_Stage_x.clear();
	                vec_Stage_y.clear();
	                vec_Stage_z.clear();
	                vec_Stage_layer.clear();
	                vec_Stage_module.clear();
	                vec_Stage_fee.clear();
	                vec_Stage_fee_ch.clear();
	                vec_Stage_cell.clear();
	                vec_Stage_tdc_ch.clear();
	                vec_Stage_leadtime.clear();
	                vec_Stage_trailtime.clear();


        for (int f =0; f< vec_filterLeadTime.size(); f++)
         {

            char buff[10000];
            if (sttCosmic == true)
                {
                //printf("Cosmic found in both subsystems in event nr:%d\n", e);

                int local_cnt = 0;
                // for (int i = 0; i < stt_events->totalNTDCHits; i++)
                // {
                //    // SttHit* hit  = (SttHit*)stt_events->stt_raw->tdc_hits->ConstructedAt(i); // retrieve particular hit
                //     if (hit->isRef) continue;

                //     sprintf(buff, "[%d / %d]  cell,l,m,c,cf=%d,%d,%d,%2d,%2d    x,y,z=%.3f,%.3f,%.3f  lt=%f   dt=%f\n",
                //        global_cnt, local_cnt,
                //        hit->cell, hit->layer, hit->module, hit->channel, hit->fee_channel,
                //        hit->x, hit->y, hit->z,
                //        hit->leadTime, hit->drifttime);
                //     printf(buff);
                //     fprintf(fp, buff);
                //     ++local_cnt;
                // }
                // ++global_cnt;


	                h_STT_counts->Fill(4);

	                double meanTime = 0;
	                int crystalMult = 0;
	                double delT = 0;
	                int dl1 = 220;
	                int dl2 = 450;



	                // for (int q = 0; q < vec_filterLeadTime.size(); q++)
	                // {
	                    //cout << "module "<< vec_filterLeadTime.at(f)->layer<<endl;
	                    vec_Stage_x.push_back(vec_filterLeadTime.at(f)->x);
	                    vec_Stage_y.push_back(vec_filterLeadTime.at(f)->y);
	                    vec_Stage_z.push_back(vec_filterLeadTime.at(f)->z);
	                    vec_Stage_layer.push_back(vec_filterLeadTime.at(f)->layer);
	                    vec_Stage_module.push_back(vec_filterLeadTime.at(f)->module);
	                    vec_Stage_fee.push_back(vec_filterLeadTime.at(f)->fee);
	                    vec_Stage_fee_ch.push_back(vec_filterLeadTime.at(f)->fee_channel);
	                    vec_Stage_tdc_ch.push_back(vec_filterLeadTime.at(f)->channel);
	                    vec_Stage_leadtime.push_back(vec_filterLeadTime.at(f)->leadTime);
	                    vec_Stage_trailtime.push_back(vec_filterLeadTime.at(f)->trailTime);
	                    vec_Stage_cell.push_back(vec_filterLeadTime.at(f)->cell);
	                   // vec_Stage_DT.push_back(0);

	                //}

                }

        } // end of the loop over clusters
        
           PDAQ_EMC_STT_cluster_analysis->Fill();

        if (sttCosmic == true)
            h_stt_cosmic->Fill(1);


    	//}//over hits
    }// over events

	  h_STT_layers->Write();
	  h_STT_channelsWithoutRef->Write(); 
	  h_STT_tot->Write();
	  h_STT_channels_4layers->Write();
	  h_STT_layerhits->Write(); 
	  h_STT_layerMult->Write(); 
	  h_stt_cosmic->Write();
	  h_STT_layerhitsmult->Write();
	  h_STT_counts->Write();
	  h_STT_TOTvsCh->Write();

 
    PDAQ_EMC_STT_cluster_analysis->Write();
    cout << "Repeated entries  :"<< repeat<<"/"<<All_repeat<<endl;  

    // if (fp)
    //     fclose(fp);


return 0;
}

