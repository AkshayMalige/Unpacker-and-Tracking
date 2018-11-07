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

#include "TRandom.h"
#include "SttHit.h"
#include "SttEvent.h"
// #include "Cluster_Tree.h"

//===================================================================

//===================================================================
#define MAKE_HST_IND(hstname, bins, minx, maxx, ind, tstr)                                         \
    {                                                                                              \
        std::string tmpstr;                                                                        \
        tmpstr = #hstname;                                                                         \
        tmpstr += "_%2i";                                                                          \
        if (hstname[ind])                                                                          \
            hstname[ind]->Reset();                                                                 \
        else                                                                                       \
        {                                                                                          \
            sprintf(tstr, tmpstr.c_str(), i + 1);                                                  \
            hstname[ind] = new TH1F(tstr, tstr, bins, minx, maxx);                                 \
        }                                                                                          \
    \
}
#define MAKE_HST2_IND(hstname, binsX, minx, maxx, binsY, miny, maxy, ind, tstr)                    \
    {                                                                                              \
        std::string tmpstr;                                                                        \
        tmpstr = #hstname;                                                                         \
        tmpstr += "_%2i";                                                                          \
        if (hstname[ind])                                                                          \
            hstname[ind]->Reset();                                                                 \
        else                                                                                       \
        {                                                                                          \
            sprintf(tstr, tmpstr.c_str(), i + 1);                                                  \
            hstname[ind] = new TH2F(tstr, tstr, binsX, minx, maxx, binsY, miny, maxy);             \
        }                                                                                          \
    \
}
#define MAKE_HST(hstname, bins, minx, maxx)                                                        \
    {                                                                                              \
        if (hstname)                                                                               \
            hstname->Reset();                                                                      \
        else                                                                                       \
            hstname = new TH1F(#hstname, #hstname, bins, minx, maxx);                              \
    \
}
#define MAKE_HST2(hstname, bins, minx, maxx, binsy, miny, maxy)                                    \
    {                                                                                              \
        if (hstname)                                                                               \
            hstname->Reset();                                                                      \
        else                                                                                       \
            hstname = new TH2F(#hstname, #hstname, bins, minx, maxx, binsy, miny, maxy);           \
    \
}

//===================================================================
// Define histograms
// TH1F* h_EMC_ADC_channels_hits;
// TH1F* h_EMC_multiplicity_cl;
// TH1F* h_EMC_multiplicity_SB;
//
// static const int emc_h_energy_size = 50;
// TH1F* h_EMC_RawTime[emc_h_energy_size];
// TH1F* h_EMC_RawEnergy[emc_h_energy_size];
// TH1F* h_EMC_RawEnergy_CrCoinc[emc_h_energy_size];
// TH1F* h_EMC_dT_Cgated;
//
// const int emc_matrix_size = 9;
// TH1F* h_EMC_EnergyC[emc_matrix_size];
// TH1F* h_EMC_EnergyC_track[emc_matrix_size];

TH1F* h_STT_layers;
TH1F* h_STT_channelsWithoutRef;
TH1F* h_STT_tot;

TH1F* h_STT_channels_4layers;
TH1F* h_STT_layerhits;
TH1F* h_STT_layerMult;
TH1F* h_STT_leadTimeDiff;
TH2F* h_STT_TOTvsCh;
//TH1F* h_STT_EMC_cosmic;
//TH1F* h_EMC_trueMultiplicity;
//TH1F* h_STT_EMC_trueMultiplicity;
//TH1F* h_EMC_clusters_per_SB;

//TH1F* h_emc_cosmic;
TH1F* h_stt_cosmic;

//TH1F* h_EMC_EnergyCut_track[emc_matrix_size];
//TH1F* h_EMC_EnergyCut2_track[emc_matrix_size];

//TH1F* h_EMC_sumEnergyCut_track;
//TH1F* h_EMC_sumEnergyCut2_track;
//TH1F* h_STT_EMC_crystmult;
TH1F* h_STT_layerhitsmult;
TH1F* h_STT_counts;

//TH1F* h_straw_mean_EMC;
TH1F* h_straw_mean_straw;

TH2F* h_Fee_DriftTime;

int counterofdt;
int counter2 = 0;
Double_t repeat =0;
Double_t All_repeat =0;



//===================================================================
bool f_sttHitCompareLeadTime(SttHit* a, SttHit* b)
{
    return (a->leadTime < b->leadTime);
}

// init histograms
void pd_init_hst()
{
    // char tstr[200];
    // //
    // MAKE_HST(h_EMC_ADC_channels_hits, 60000, 0, 60000);
    // for (int i = 0; i < emc_h_energy_size; i++)
    // {
    //     MAKE_HST_IND(h_EMC_RawTime, 200, -20, 20, i, tstr);
    //     MAKE_HST_IND(h_EMC_RawEnergy, 6000, 0, 60000, i, tstr);
    //     MAKE_HST_IND(h_EMC_RawEnergy_CrCoinc, 6000, 0, 60000, i, tstr);
    // }
    // for (int i = 0; i < emc_matrix_size; i++)
    // {
    //     MAKE_HST_IND(h_EMC_EnergyC, 6000, 0, 60000, i, tstr);
    //     MAKE_HST_IND(h_EMC_EnergyC_track, 6000, 0, 60000, i, tstr);
    //     MAKE_HST_IND(h_EMC_EnergyCut_track, 6000, 0, 60000, i, tstr);
    //     MAKE_HST_IND(h_EMC_EnergyCut2_track, 6000, 0, 60000, i, tstr);
    // }

    // MAKE_HST(h_EMC_sumEnergyCut_track, 6000, 0, 6000);
    // MAKE_HST(h_EMC_sumEnergyCut2_track, 6000, 0, 6000);


    //
    // MAKE_HST(h_EMC_dT_Cgated, 1000, -50, 50);
    // MAKE_HST(h_EMC_multiplicity_cl, 50, 0, 50);
    // MAKE_HST(h_EMC_multiplicity_SB, 50, 0, 50);


    MAKE_HST(h_STT_layers, 10, 0, 10);
    MAKE_HST(h_STT_channelsWithoutRef, 350, 0, 350);
    MAKE_HST(h_STT_tot, 500, 0, 500);
    MAKE_HST(h_STT_channels_4layers, 500, 0, 500);
    MAKE_HST(h_STT_layerhits, 10, 0, 10);
    MAKE_HST(h_STT_layerMult, 17, 0, 17);
    MAKE_HST(h_STT_leadTimeDiff, 500, 0, 500);
    MAKE_HST2(h_STT_TOTvsCh, 300, 0, 300, 500, 0, 500);

    //MAKE_HST(h_EMC_clusters_per_SB, 10, 0, 10);
    //MAKE_HST(h_STT_EMC_cosmic, 5, 0, 5);
    //MAKE_HST(h_EMC_trueMultiplicity, 50, 0, 50);
    //MAKE_HST(h_STT_EMC_trueMultiplicity, 50, 0, 50);

    //MAKE_HST(h_emc_cosmic, 5, 0, 5);
    MAKE_HST(h_stt_cosmic, 5, 0, 5);
    //MAKE_HST(h_STT_EMC_crystmult, 100, 0, 100);
    MAKE_HST(h_STT_layerhitsmult, 10, 0, 10);
    MAKE_HST(h_STT_counts, 10, 0, 10);

    h_STT_channels_4layers->GetXaxis()->SetTitle("Number of Straws");
}

#undef MAKE_HST
#undef MAKE_HST2
#undef MAKE_HST_IND
#undef MAKE_HST2_IND

//===================================================================
void PDAQ_EMC_STT_cluster_analysis(char* intree, int maxEvents = 100000)
{
     FILE * fp = fopen("log_pdaq.txt", "w");
     if (!fp)
        fprintf(stderr, "Log file not open!\n");

    //------
    // Init histograms
    pd_init_hst();
    //===================================================================
    // Event structure
    //
    UShort_t Header_status;
    UInt_t SB_number;
    //-------------------------------------------------------------------
    // EMC
    // std::vector<UInt_t>* emc_Cluster_local_time = 0;
    // std::vector<UShort_t>* emc_Cluster_diameter = 0;
    // std::vector<UShort_t>* emc_Cluster_2x = 0;
    // std::vector<UShort_t>* emc_Cluster_2y = 0;
    // std::vector<UShort_t>* emc_Cluster_N_hits = 0;
    // //
    // std::vector<UInt_t>* emc_Hits_local_time = 0;
    // std::vector<UChar_t>* emc_Hits_status = 0;
    // std::vector<UShort_t>* emc_Hits_ADC_channel = 0;
    // std::vector<UShort_t>* emc_Hits_Energy = 0;

    std::vector<SttHit*> vec_Allhits;

    SttEvent* stt_events = 0;

    //===================================================================
    // Open Input tree
    //
    TFile inFile(intree);
    TTree* tree = (TTree*)inFile.Get("PDAQ_Events");
    if (!tree)
    {
        std::cerr << "Tree PDAQ_Events was not found\n";
        std::exit(1);
    }
    //-------------------------------------------------------------------
    // Header variables
    // tree->SetBranchAddress("Header_status", &Header_status);
    // tree->SetBranchAddress("SB_number", &SB_number);
    // //
    // // EMC data
    // tree->SetBranchAddress("emc_Cluster_local_time", &emc_Cluster_local_time);
    // tree->SetBranchAddress("emc_Cluster_diameter", &emc_Cluster_diameter);
    // tree->SetBranchAddress("emc_Cluster_2x", &emc_Cluster_2x);
    // tree->SetBranchAddress("emc_Cluster_2y", &emc_Cluster_2y);
    // tree->SetBranchAddress("emc_Cluster_N_hits", &emc_Cluster_N_hits);
    // //
    // tree->SetBranchAddress("emc_Hits_local_time", &emc_Hits_local_time);
    // tree->SetBranchAddress("emc_Hits_status", &emc_Hits_status);
    // tree->SetBranchAddress("emc_Hits_ADC_channel", &emc_Hits_ADC_channel);
    // tree->SetBranchAddress("emc_Hits_Energy", &emc_Hits_Energy);
    //.......................
    // STT data
    printf("Connecting stt branch: %d\n", tree->SetBranchAddress("STT", &STT));
    //===================================================================
    // Constants
    // const int emc_adc_chan_ofset = 16;
    // //
    // float emc_EC_cosm_gates[2 * emc_matrix_size];
    // // ch 1
    // emc_EC_cosm_gates[0] = 800 / 4;
    // emc_EC_cosm_gates[1] = 1800;
    // // ch 2
    // emc_EC_cosm_gates[2] = 500 / 4;
    // emc_EC_cosm_gates[3] = 900;
    // // ch 3
    // emc_EC_cosm_gates[4] = 450 / 4;
    // emc_EC_cosm_gates[5] = 1000;
    // // ch 4
    // emc_EC_cosm_gates[6] = 350 / 4;
    // emc_EC_cosm_gates[7] = 700;
    // // ch 5
    // emc_EC_cosm_gates[8] = 450 / 4;
    // emc_EC_cosm_gates[9] = 800;
    // // ch 6
    // emc_EC_cosm_gates[10] = 500 / 4;
    // emc_EC_cosm_gates[11] = 1000;
    // // ch 7
    // emc_EC_cosm_gates[12] = 450 / 4;
    // emc_EC_cosm_gates[13] = 1000;
    // // ch 8
    // emc_EC_cosm_gates[14] = 350 / 4;
    // emc_EC_cosm_gates[15] = 800;
    // // ch 9
    // emc_EC_cosm_gates[16] = 500 / 4;
    // emc_EC_cosm_gates[17] = 1000;

    //===================================================================
    // Main loop
    //
    // EMC calibrated event
    // float emc_energy_C[emc_matrix_size];
    // double emc_time_C[emc_matrix_size];
    // int emc_N_hits[emc_matrix_size];
    // int emc_N_trig[emc_matrix_size];
    //---------
    //
    TRandom rnd;
    Int_t nentries = (Int_t)tree->GetEntries();
    std::cout << nentries << "\n";
  

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

    TFile* Ttree = new TFile("PDAQ_Cal.root", "RECREATE");
    TTree* PDAQ_Cal = new TTree("PDAQ_Cal", "PDAQ_Cal");

    PDAQ_Cal->Branch("vec_Stage_DT", &vec_Stage_DT);
    PDAQ_Cal->Branch("vec_Stage_layer", &vec_Stage_layer);
    PDAQ_Cal->Branch("vec_Stage_x", &vec_Stage_x);
    PDAQ_Cal->Branch("vec_Stage_y", &vec_Stage_y);
    PDAQ_Cal->Branch("vec_Stage_z", &vec_Stage_z);
    PDAQ_Cal->Branch("vec_Stage_module", &vec_Stage_module);
    PDAQ_Cal->Branch("vec_Stage_fee", &vec_Stage_fee);
    PDAQ_Cal->Branch("vec_Stage_fee_ch", &vec_Stage_fee_ch);
    PDAQ_Cal->Branch("vec_Stage_cell", &vec_Stage_cell);
    PDAQ_Cal->Branch("vec_Stage_tdc_ch", &vec_Stage_tdc_ch);
    PDAQ_Cal->Branch("vec_Stage_leadtime", &vec_Stage_leadtime);
    PDAQ_Cal->Branch("vec_Stage_trailtime", &vec_Stage_trailtime);

    Long_t global_cnt = 0;
    for (Long_t e = 0; e < nentries; e++)
    {
        if (e % 10000 == 0)
        {
            printf("%d\n", e);
        }
        if (e == maxEvents)
            break;

        tree->GetEntry(e);

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

//Check for repeated entries of a hit

            for(Int_t je=0; je<vec_leadTime.size()-1;je++)
            {
               // cout << "All entries  :  " <<"\t"<<" Lead Time : "<< vec_leadTime[je]->leadTime<<"\t" << " layer : "<< vec_leadTime[je]->layer<<"\t"<< "module : "<< vec_leadTime[je]->module<<"\t"<< " fee : "<< vec_leadTime[je]->fee<<"\t" << "FEE_Ch : "<< vec_leadTime[je]->fee_channel<<"\t"<<endl;
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

        for (int f =0; f< vec_filterLeadTime.size(); f++)
         {

            char buff[10000];
            if (sttCosmic == true)
                {
                    printf("Cosmic found in both subsystems in event nr:%d\n", e);

                    int local_cnt = 0;
                    // for (int i = 0; i < stt_events->totalNTDCHits; i++)
                    // {
                    //     SttHit* hit  = (SttHit*)stt_events->stt_raw->tdc_hits->ConstructedAt(i); // retrieve particular hit
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

                    vec_Stage_DT.clear();
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

                    for (int q = 0; q < vec_filterLeadTime.size(); q++)
                    {
                        
                        vec_Stage_x.push_back(vec_filterLeadTime.at(q)->x);
                        vec_Stage_y.push_back(vec_filterLeadTime.at(q)->y);
                        vec_Stage_z.push_back(vec_filterLeadTime.at(q)->z);
                        vec_Stage_layer.push_back(vec_filterLeadTime.at(q)->layer);
                        vec_Stage_module.push_back(vec_filterLeadTime.at(q)->module);
                        vec_Stage_fee.push_back(vec_filterLeadTime.at(q)->fee);
                        vec_Stage_fee_ch.push_back(vec_filterLeadTime.at(q)->fee_channel);
                        vec_Stage_tdc_ch.push_back(vec_filterLeadTime.at(q)->channel);
                        vec_Stage_leadtime.push_back(vec_filterLeadTime.at(q)->leadTime);
                        vec_Stage_trailtime.push_back(vec_filterLeadTime.at(q)->trailTime);
                        vec_Stage_cell.push_back(vec_filterLeadTime.at(q)->cell);
                      //  vec_Stage_DT.push_back((38400 - vec_filterLeadTime.at(q)->leadTime) - emcTime);

                    }

                        PDAQ_Cal->Fill();
                }

        } // end of the loop over clusters

        if (sttCosmic == true)
            h_stt_cosmic->Fill(1);

    } // end of event loop.//////////////////////////////////////////////
 
    PDAQ_Cal->Write();
    cout << "Repeated entries  :"<< repeat<<"/"<<All_repeat<<endl;  

    if (fp)
        fclose(fp);
}

void PDAQ_Cal() {}