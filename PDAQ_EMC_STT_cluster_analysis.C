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

//#include <TLinearFitter.h>
//#include <TF1.h>

#include "TRandom.h"
#include "SttHit.h"

#include "SttEvent.h"

//===================================================================

const int Max_N_Channels = 1000;
const double time_to_ns = 12.5 / 2048;

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
TH1F* h_EMC_ADC_channels_hits;
TH1F* h_EMC_multiplicity_cl;
TH1F* h_EMC_multiplicity_SB;
//
static const int emc_h_energy_size = 50;
TH1F* h_EMC_RawTime[emc_h_energy_size];
TH1F* h_EMC_RawEnergy[emc_h_energy_size];
TH1F* h_EMC_RawEnergy_CrCoinc[emc_h_energy_size];
TH1F* h_EMC_dT_Cgated;
//
const int emc_matrix_size = 9;
TH1F* h_EMC_EnergyC[emc_matrix_size];
TH1F* h_EMC_EnergyC_track[emc_matrix_size];

//


TH1F* h_STT_layers;
TH1F* h_STT_channelsWithoutRef;
TH1F* h_STT_tot;

TH1F* h_STT_channels_4layers;
TH1F* h_STT_layerhits;
TH1F* h_STT_layerMult;
TH1F* h_STT_leadTimeDiff;
TH2F* h_STT_TOTvsCh;


TH1F* h_STT_EMC_cosmic;
TH1F* h_STT_EMC_timeDiff;
TH2F* h_STT_EMC_L1L2;
TH2F* h_STT_EMC_L3L4;
TH1F* h_STT_EMC_td1;
TH1F* h_STT_EMC_td2;
TH1F* h_STT_EMC_td3;
TH1F* h_STT_EMC_td4;


TH1F* h_STT_EMC_d1;
TH1F* h_STT_EMC_d2;
TH1F* h_STT_EMC_d3;
TH1F* h_STT_EMC_d4;
TH1F* h_STT_EMC_d5;
TH1F* h_STT_EMC_d6;
TH1F* h_STT_EMC_d7;
TH1F* h_STT_EMC_d8;

TH1F* h_EMC_trueMultiplicity;
TH1F* h_STT_EMC_trueMultiplicity;

TH1F* h_EMC_clusters_per_SB;

TH1F* h_emc_cosmic;
TH1F* h_stt_cosmic;

TH1F* h_EMC_EnergyCut_track[emc_matrix_size];
TH1F* h_EMC_EnergyCut2_track[emc_matrix_size];

TH1F* h_EMC_sumEnergyCut_track;
TH1F* h_EMC_sumEnergyCut2_track;
TH1F* h_STT_EMC_crystmult;
TH1F* h_STT_layerhitsmult;
TH1F* h_STT_counts;

int counterofdt;
int driftTimeCounter2;
int counter2 = 0;


//===================================================================


bool f_sttHitCompareLeadTime(SttHit* a, SttHit* b)
{
    return (a->leadTime < b->leadTime);
}


// init histograms
void pd_init_hst()
{
    char tstr[200];
    //
    MAKE_HST(h_EMC_ADC_channels_hits, 60000, 0, 60000);
    for (int i = 0; i < emc_h_energy_size; i++)
    {
        MAKE_HST_IND(h_EMC_RawTime, 200, -20, 20, i, tstr);
        MAKE_HST_IND(h_EMC_RawEnergy, 6000, 0, 60000, i, tstr);
        MAKE_HST_IND(h_EMC_RawEnergy_CrCoinc, 6000, 0, 60000, i, tstr);
    }
    for (int i = 0; i < emc_matrix_size; i++)
    {
        MAKE_HST_IND(h_EMC_EnergyC, 6000, 0, 60000, i, tstr);
        MAKE_HST_IND(h_EMC_EnergyC_track, 6000, 0, 60000, i, tstr);
        MAKE_HST_IND(h_EMC_EnergyCut_track, 6000, 0, 60000, i, tstr);
        MAKE_HST_IND(h_EMC_EnergyCut2_track, 6000, 0, 60000, i, tstr);
    }

    MAKE_HST(h_EMC_sumEnergyCut_track, 6000, 0, 6000);
    MAKE_HST(h_EMC_sumEnergyCut2_track, 6000, 0, 6000);


    //
    MAKE_HST(h_EMC_dT_Cgated, 1000, -50, 50);
    MAKE_HST(h_EMC_multiplicity_cl, 50, 0, 50);
    MAKE_HST(h_EMC_multiplicity_SB, 50, 0, 50);


    MAKE_HST(h_STT_layers, 10, 0, 10);
    MAKE_HST(h_STT_channelsWithoutRef, 350, 0, 350);
    MAKE_HST(h_STT_tot, 500, 0, 500);
    MAKE_HST(h_STT_channels_4layers, 500, 0, 500);
    MAKE_HST(h_STT_layerhits, 10, 0, 10);
    MAKE_HST(h_STT_layerMult, 17, 0, 17);
    MAKE_HST(h_STT_leadTimeDiff, 500, 0, 500);
    MAKE_HST2(h_STT_TOTvsCh, 300, 0, 300, 500, 0, 500);

    MAKE_HST(h_EMC_clusters_per_SB, 10, 0, 10);

    MAKE_HST2(h_STT_EMC_L1L2, 65, 0, 65, 65, 0, 65);
    MAKE_HST2(h_STT_EMC_L3L4, 65, 0, 65, 65, 0, 65);


    MAKE_HST(h_STT_EMC_cosmic, 5, 0, 5);
    MAKE_HST(h_STT_EMC_timeDiff, 250, 200, 450);
    MAKE_HST(h_STT_EMC_td1, 1000, 0, 1000);
    MAKE_HST(h_STT_EMC_td2, 1000, 0, 1000)
    MAKE_HST(h_STT_EMC_td3, 1000, 0, 1000)
    MAKE_HST(h_STT_EMC_td4, 1000, 0, 1000)

    MAKE_HST(h_STT_EMC_d1, 1000, 0, 1000);
    MAKE_HST(h_STT_EMC_d2, 1000, 0, 1000);
    MAKE_HST(h_STT_EMC_d3, 1000, 0, 1000);
    MAKE_HST(h_STT_EMC_d4, 1000, 0, 1000);
    MAKE_HST(h_STT_EMC_d5, 1000, 0, 1000);
    MAKE_HST(h_STT_EMC_d6, 1000, 0, 1000);
    MAKE_HST(h_STT_EMC_d7, 1000, 0, 1000);
    MAKE_HST(h_STT_EMC_d8, 1000, 0, 1000);

    MAKE_HST(h_EMC_trueMultiplicity, 50, 0, 50);
    MAKE_HST(h_STT_EMC_trueMultiplicity, 50, 0, 50);

    MAKE_HST(h_emc_cosmic, 5, 0, 5);
    MAKE_HST(h_stt_cosmic, 5, 0, 5);
    MAKE_HST(h_STT_EMC_crystmult, 100, 0, 100);
    MAKE_HST(h_STT_layerhitsmult, 10, 0, 10);
    MAKE_HST(h_STT_counts, 10, 0, 10);
}

#undef MAKE_HST
#undef MAKE_HST2
#undef MAKE_HST_IND
#undef MAKE_HST2_IND

//===================================================================
void PDAQ_EMC_STT_cluster_analysis(char* intree, int maxEvents = 100000)
{

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
    std::vector<UInt_t>* emc_Cluster_local_time = 0;
    std::vector<UShort_t>* emc_Cluster_diameter = 0;
    std::vector<UShort_t>* emc_Cluster_2x = 0;
    std::vector<UShort_t>* emc_Cluster_2y = 0;
    std::vector<UShort_t>* emc_Cluster_N_hits = 0;
    //
    std::vector<UInt_t>* emc_Hits_local_time = 0;
    std::vector<UChar_t>* emc_Hits_status = 0;
    std::vector<UShort_t>* emc_Hits_ADC_channel = 0;
    std::vector<UShort_t>* emc_Hits_Energy = 0;
    //
    //-------------------------------------------------------------------
    // STT

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
    tree->SetBranchAddress("Header_status", &Header_status);
    tree->SetBranchAddress("SB_number", &SB_number);
    //
    // EMC data
    tree->SetBranchAddress("emc_Cluster_local_time", &emc_Cluster_local_time);
    tree->SetBranchAddress("emc_Cluster_diameter", &emc_Cluster_diameter);
    tree->SetBranchAddress("emc_Cluster_2x", &emc_Cluster_2x);
    tree->SetBranchAddress("emc_Cluster_2y", &emc_Cluster_2y);
    tree->SetBranchAddress("emc_Cluster_N_hits", &emc_Cluster_N_hits);
    //
    tree->SetBranchAddress("emc_Hits_local_time", &emc_Hits_local_time);
    tree->SetBranchAddress("emc_Hits_status", &emc_Hits_status);
    tree->SetBranchAddress("emc_Hits_ADC_channel", &emc_Hits_ADC_channel);
    tree->SetBranchAddress("emc_Hits_Energy", &emc_Hits_Energy);
    //.......................
    // STT data
    printf("Connecting stt branch: %d\n", tree->SetBranchAddress("stt_events", &stt_events));
    //===================================================================
    // Constants
    const int emc_adc_chan_ofset = 16;
    //
    float emc_EC_cosm_gates[2 * emc_matrix_size];
    // ch 1
    emc_EC_cosm_gates[0] = 800 / 4;
    emc_EC_cosm_gates[1] = 1800;
    // ch 2
    emc_EC_cosm_gates[2] = 500 / 4;
    emc_EC_cosm_gates[3] = 900;
    // ch 3
    emc_EC_cosm_gates[4] = 450 / 4;
    emc_EC_cosm_gates[5] = 1000;
    // ch 4
    emc_EC_cosm_gates[6] = 350 / 4;
    emc_EC_cosm_gates[7] = 700;
    // ch 5
    emc_EC_cosm_gates[8] = 450 / 4;
    emc_EC_cosm_gates[9] = 800;
    // ch 6
    emc_EC_cosm_gates[10] = 500 / 4;
    emc_EC_cosm_gates[11] = 1000;
    // ch 7
    emc_EC_cosm_gates[12] = 450 / 4;
    emc_EC_cosm_gates[13] = 1000;
    // ch 8
    emc_EC_cosm_gates[14] = 350 / 4;
    emc_EC_cosm_gates[15] = 800;
    // ch 9
    emc_EC_cosm_gates[16] = 500 / 4;
    emc_EC_cosm_gates[17] = 1000;

    /*// ch 1
  emc_EC_cosm_gates[0] = 800;
  emc_EC_cosm_gates[1] = 1800;
  // ch 2
  emc_EC_cosm_gates[2] = 500;
  emc_EC_cosm_gates[3] = 900;
  // ch 3
  emc_EC_cosm_gates[4] = 450;
  emc_EC_cosm_gates[5] = 1000;
  // ch 4
  emc_EC_cosm_gates[6] = 350;
  emc_EC_cosm_gates[7] = 700;
  // ch 5
  emc_EC_cosm_gates[8] = 450;
  emc_EC_cosm_gates[9] = 800;
  // ch 6
  emc_EC_cosm_gates[10] = 500;
  emc_EC_cosm_gates[11] = 1000;
  // ch 7
  emc_EC_cosm_gates[12] = 450;
  emc_EC_cosm_gates[13] = 1000;
  // ch 8
  emc_EC_cosm_gates[14] = 350;
  emc_EC_cosm_gates[15] = 800;
  // ch 9
  emc_EC_cosm_gates[16] = 500;
  emc_EC_cosm_gates[17] = 1000;*/
    //
    //===================================================================
    // Main loop
    //
    // EMC calibrated event
    float emc_energy_C[emc_matrix_size];
    double emc_time_C[emc_matrix_size];
    int emc_N_hits[emc_matrix_size];
    int emc_N_trig[emc_matrix_size];
    //---------
    //
    TRandom rnd;
    Int_t nentries = (Int_t)tree->GetEntries();
    std::cout << nentries << "\n";


     ofstream file3;
     file3.open("Cross_check.txt");

    std::vector<double> vec_o_test;
    std::vector<double> vec_o_test1;

    std::vector<double> vec_test;
    std::vector<double> vec_roundoff;
    std::vector<double> vec_occurance;
    std::vector<double> vec_pos_DT;
    std::vector<double> vec_cumsum;
    std::vector<double> vec_drift_radius;


    std::vector<double> vec_x;
    std::vector<double> vec_y;
    std::vector<double> vec_z;
    std::vector<double> vec_layer;
    std::vector<double> vec_module;
    std::vector<double> vec_fee;
    std::vector<double> vec_fee_ch;
    std::vector<double> vec_tdc_ch;






    TFile* ftree = new TFile("Drift_Radius.root", "RECREATE");
    TTree* DR_Tree = new TTree("DR_Tree", "DR_Tree");

    DR_Tree->Branch("Vec_o_test", &vec_o_test);
    DR_Tree->Branch("vec_layer", &vec_layer);
    DR_Tree->Branch("vec_x", &vec_x);
    DR_Tree->Branch("vec_y", &vec_y);
    DR_Tree->Branch("vec_z", &vec_z);
    DR_Tree->Branch("vec_module", &vec_module);
    DR_Tree->Branch("vec_fee", &vec_fee);
    DR_Tree->Branch("vec_fee_ch", &vec_fee_ch);
    DR_Tree->Branch("vec_tdc_ch", &vec_tdc_ch);/*
/*
    DR_Tree->Branch("Drift_Time_STT_EMC", vec_roundoff);
    DR_Tree->Branch("Drift_Time_STT_EMC", &vec_test);
    DR_Tree->Branch("Drift_Time_STT_EMC", &vec_cumsum);
    DR_Tree->Branch("Drift_Time_STT_EMC", &vec_occurance);
    DR_Tree->Branch("Drift_Time_STT_EMC", &vec_drift_radius);*/


    for (Int_t e = 0; e < nentries; e++)
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

        bool emcCosmic = false;
        bool sttCosmic = false;
        std::vector<SttHit*> vec_filterLeadTime;
        std::vector<SttHit*> vecvec;

        std::vector<SttHit*> vec_L1;
        std::vector<SttHit*> vec_L2;
        std::vector<SttHit*> vec_L3;
        std::vector<SttHit*> vec_L4;
        std::vector<SttHit*> vec_L5;

        double emcTime = 0;
        double a;
        double b;
        double a_err;
        double b_err;

        SttHit* hitOnLayer[4][500];
        int hitMultOnLayer[4];
        int layerCounterr = 0;
        for (int i = 0; i < 4; i++)
        {
            hitMultOnLayer[i] = 0;
        }

        for (int i = 0; i < stt_events->totalNTDCHits; i++)
        {


            SttHit* hit  = (SttHit*)stt_events->tdc_hits->ConstructedAt(i); // retrieve particular hit

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

                for (int c = 0; c < 4; c++)
                {
                    if (hitMultOnLayer[c] > 0)
                        layerCounterr++;
                }
                if (layerCounterr == 4)
                {

                    h_STT_layerMult->Fill(hit->layer);
                }
            }

            hitsInEvent++;
        } // end of loop over hits

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


            // printf("Superburst with 4 layers and %d %d %d %d hits\n", hitMultOnLayer[0],
            // hitMultOnLayer[1], hitMultOnLayer[2], hitMultOnLayer[3]);

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

            std::sort(vec_leadTime.begin(), vec_leadTime.end(), f_sttHitCompareLeadTime);

            // for (int f = 0 ; f < vec_leadTime.size(); f++) {
            //    cout << "leadtime :" << f << " " << vec_leadTime.at(f)->leadTime << endl;
            //}


            vec_filterLeadTime.clear();

            // find the cluster of 8 hits within a time window
            // for ( int b=0; b< vec_leadTime.size()-1; b++){

            // if (vec_leadTime[b]->layer < vec_leadTime[b+1]->layer){


            if (vec_leadTime.size() > 7)
            {
                h_STT_counts->Fill(2);

                for (int v = 0; v < vec_leadTime.size() - 2; v++)
                { // iterate over collected and sorted hits
                    vec_filterLeadTime.clear();
                    filtercnt = 1;

                    SttHit* h = vec_leadTime.at(v);
                    vec_filterLeadTime.push_back(h);


                    for (int vv = v + 1; vv < vec_leadTime.size() - 1; vv++)
                    { // check each vs each if they fit into the window

                        if (fabs(vec_leadTime[v]->leadTime - vec_leadTime[vv]->leadTime) < fil_max)

                        {
                            SttHit* hh = vec_leadTime.at(vv);
                            vec_filterLeadTime.push_back(hh);
                            filtercnt++;
                            h_STT_leadTimeDiff->Fill(
                                fabs(vec_leadTime[v]->leadTime - vec_leadTime[vv]->leadTime));
                        }
                        else
                        { // in case the hit is outside the window break and start next iteration
                            // with the next hit
                            break;
                        }
                    }

                    if (filtercnt == 8)
                    { // in case we already have at least 8 hits within window, break and continue
                        // processing
                        break;
                    }
                }
            }
            //  }
            //}

            //  in case we have at least 8 hits within timewindow go with tracking
            if (filtercnt >7)
            {

                /*printf("Found a potential track:\n");
                   for( int j = 0; j < vec_filterLeadTime.size(); j++){
                   cout << "filterleadtime :" << j << " " << vec_filterLeadTime.at(j)->leadTime <<
                   "\t (x:" << vec_filterLeadTime.at(j)-> x << "\ty:" << vec_filterLeadTime.at(j)->
                   y << "\tz:" << vec_filterLeadTime.at(j)-> z << ")\t l" <<
                   vec_filterLeadTime.at(j)->layer<<"m"<<vec_filterLeadTime.at(j)->module<<"
                   f"<<vec_filterLeadTime.at(j)->fee<<" c"<<vec_filterLeadTime.at(j)->fee_channel <<
                   endl;
                   } */

                sttCosmic = true;

                // lf->Eval();


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

                    // h_STT_TOTvsCh->Fill((32 * vec_filterLeadTime[y]->module-1) + ( 16 *
                    // (vec_filterLeadTime[y]->fee -1)) +
                    // (vec_filterLeadTime[y]->fee_channel),vec_filterLeadTime[y]->tot);
                    h_STT_TOTvsCh->Fill(vec_filterLeadTime[y]->channel, vec_filterLeadTime[y]->tot);

                    /* a =lf->GetParameter(1);
                     b =lf->GetParameter(0);
                     a_err =lf->GetParError(1);
                     b_err =lf->GetParError(0);
                  */
                }
            }


        } // end of if with 4 layers


        // EMC Processing

        //===================================================================
        // general histograms
        h_EMC_multiplicity_SB->Fill(emc_Hits_ADC_channel->size());
        const int ref_time_ch = 1; // time reference for the LP event
        int ref_time_ind = -1;
        for (UInt_t h = 0; h < emc_Hits_ADC_channel->size(); h++)
        {
            h_EMC_ADC_channels_hits->Fill(emc_Hits_ADC_channel->at(h));
            if (emc_Hits_ADC_channel->at(h) < emc_h_energy_size)
                h_EMC_RawEnergy[emc_Hits_ADC_channel->at(h)]->Fill(emc_Hits_Energy->at(h));
            if (emc_Hits_ADC_channel->at(h) == ref_time_ch)
                ref_time_ind = h;
        }
        //

        h_EMC_clusters_per_SB->Fill(emc_Cluster_N_hits->size());


        UInt_t hi = 0;
        for (UInt_t cl = 0; cl < emc_Cluster_N_hits->size(); cl++)
        {
            if (emc_Cluster_N_hits->at(cl) > 1
                && hi + emc_Cluster_N_hits->at(cl) < emc_Hits_ADC_channel->size())
            {
                for (UInt_t h = hi; h < hi + emc_Cluster_N_hits->at(cl); h++)
                {
                    h_EMC_RawEnergy_CrCoinc[emc_Hits_ADC_channel->at(h)]->Fill(
                        emc_Hits_Energy->at(h));
                }
            }
            hi += emc_Cluster_N_hits->at(cl);
        }
        //===================================================================
        // timing histograms
        if (emc_Hits_ADC_channel->size() == emc_matrix_size * 2 && ref_time_ind > -1)
        {
            double ref_time = time_to_ns * emc_Hits_local_time->at(ref_time_ind);
            for (UInt_t h = 0; h < emc_Hits_ADC_channel->size(); h++)
                h_EMC_RawTime[emc_Hits_ADC_channel->at(h)]->Fill(
                    time_to_ns * emc_Hits_local_time->at(h) - ref_time);
        }

        //===================================================================
        // Making calibrated event
        // loop over slusters
        int ev_prn = 0;
        hi = 0;


        int true_multiplicity = 0;

        for (UInt_t cl = 0; cl < emc_Cluster_N_hits->size(); cl++)
        {

            h_EMC_multiplicity_cl->Fill(emc_Cluster_N_hits->size());
            // zero calibrated event
            for (int i = 0; i < emc_matrix_size; i++)
            {
                emc_energy_C[i] = 0;
                emc_time_C[i] = 0;
                emc_N_hits[i] = 0;
            }
            // loop over hits in cluster
            if (hi + emc_Cluster_N_hits->at(cl) <= emc_Hits_ADC_channel->size())
            {
                for (UInt_t h = hi; h < hi + emc_Cluster_N_hits->at(cl); h++)
                {
                    int ch = emc_Hits_ADC_channel->at(h) / 2;
                    if (ch >= emc_adc_chan_ofset)
                        ch -= emc_adc_chan_ofset;
                    //
                    emc_energy_C[ch] += emc_Hits_Energy->at(h) + rnd.Uniform(1);
                    emc_time_C[ch] += time_to_ns * emc_Hits_local_time->at(h);
                    emc_N_hits[ch] += 1;
                }

                true_multiplicity = 0;
                for (int i = 0; i < emc_matrix_size; i++)
                    if (emc_N_hits[i] > 1)
                    {
                        emc_energy_C[i] /= emc_N_hits[i];
                        emc_time_C[i] /= emc_N_hits[i];
                        h_EMC_EnergyC[i]->Fill(emc_energy_C[i]);
                        true_multiplicity++;

                        /*if(i==0 && emc_energy_C[i] > 800 &&  emc_energy_C[i] < 2000){
                           printf("-----\n");
                           for(int j=0;j<emc_matrix_size;j++) if(emc_N_hits[j]>1)
                           printf("# %i(%f);",j,emc_energy_C[j]/emc_N_hits[j]);
                           printf("\n");
                           } */
                    }

                    else
                    {
                        emc_energy_C[i] = 0;
                        emc_time_C[i] = 0.0;
                    }


                h_EMC_trueMultiplicity->Fill(true_multiplicity);

                emcCosmic = false;

                if (true_multiplicity > 1)
                { // cosmick track or LP event

                    // condition where EMC registered a cosmic track


                    for (int i = 0; i < emc_matrix_size; i++)
                    {

                        if (emc_energy_C[i] > 1)
                        {

                            h_EMC_EnergyC_track[i]->Fill(emc_energy_C[i]);

                            if (emc_energy_C[i] > emc_EC_cosm_gates[i * 2]
                                && emc_energy_C[i] < emc_EC_cosm_gates[i * 2 + 1])
                            {

                                for (int j = i + 1; j < emc_matrix_size; j++)
                                {

                                    if (emc_energy_C[i] > 1
                                        && emc_energy_C[j] > emc_EC_cosm_gates[j * 2]
                                        && emc_energy_C[j] < emc_EC_cosm_gates[j * 2 + 1])
                                    {
                                        h_EMC_dT_Cgated->Fill(emc_time_C[i] - emc_time_C[j]);

                                        emcTime = (emc_time_C[i] + emc_time_C[j]) / 2.0;


                                        // combine EMC with STT
                                        emcCosmic = true;
                                    }
                                }
                            }
                        }
                    }
                    // Check for the time difference in Ch 1 and 4
                    // if(emc_energy_C[0]>800 && emc_energy_C[0]<1800 && emc_energy_C[3]>350 &&
                    // emc_energy_C[3]<700)
                    // h_EMC_dT_Cgated->Fill(emc_time_C[0]-emc_time_C[3]);
                }
            }
            else
                printf("Error: # of cluster mismatch!\n");
            //
            hi += emc_Cluster_N_hits->at(cl);

            // STT + EMC Processing


            if (sttCosmic == true && emcCosmic == true)
            {
                printf("Cosmic found in both subsystems in event nr:%d\n", e);

                h_STT_EMC_cosmic->Fill(1);
                h_STT_counts->Fill(4);


                double meanTime = 0;
                int crystalMult = 0;
                double delT = 0;
                int dl1 = 220;
                int dl2 = 450;


                vec_L5.clear();

                h_STT_EMC_trueMultiplicity->Fill(true_multiplicity);


                for (int q = 0; q < vec_filterLeadTime.size(); q++)
                {

                    SttHit* u = vec_filterLeadTime.at(q);

                    vec_L5.push_back(u);

                    //}
                }


                // cut on STT_EMC time difference

                for (int w = 0; w < vec_L5.size(); w++)


                // Layer wise drift time : STT-EMC
                {
                    if (vec_L5[w]->layer == 1)
                    {
                        h_STT_EMC_td1->Fill((38400 - vec_L5[w]->leadTime) - emcTime);
                    }
                    else if (vec_L5[w]->layer == 2)
                    {
                        h_STT_EMC_td2->Fill((38400 - vec_L5[w]->leadTime) - emcTime);
                    }
                    else if (vec_L5[w]->layer == 3)
                    {
                        h_STT_EMC_td3->Fill((38400 - vec_L5[w]->leadTime) - emcTime);
                    }
                    else if (vec_L5[w]->layer == 4)
                    {
                        h_STT_EMC_td4->Fill((38400 - vec_L5[w]->leadTime) - emcTime);
                    }

                    // drift time : STT-EMC


                    h_STT_EMC_timeDiff->Fill((38400 - vec_L5[w]->leadTime) - emcTime);

                    meanTime += vec_L5.at(w)->leadTime;


                    // sleep(100);


                    if (((38400 - vec_L5[w]->leadTime) - emcTime) >= dl1
                        && ((8400 - vec_L5[w]->leadTime) - emcTime) <= dl2)
                    {



                        delT = (38400 - vec_L5[w]->leadTime) - emcTime;

                         file3 << delT << "\t" <<vec_L5[w]->layer << "\t"<< vec_L5[w]->x <<
                         "\t"<<vec_L5[w]->y << "\t"<<vec_L5[w]-> z << "\t"<<vec_L5[w]->module <<
                         "\t"<<vec_L5[w]->fee << "\t"<<vec_L5[w]->fee_channel << endl;

                        counterofdt++;

                        vec_o_test.push_back(delT);
                        vec_o_test1.push_back(delT);

                        vec_x.push_back(vec_L5[w]->x);
                        vec_y.push_back(vec_L5[w]->y);
                        vec_z.push_back(vec_L5[w]->z);
                        vec_layer.push_back(vec_L5[w]->layer);
                        vec_module.push_back(vec_L5[w]->module);
                        vec_fee.push_back(vec_L5[w]->fee);
                        vec_fee_ch.push_back(vec_L5[w]->fee_channel);
                        vec_tdc_ch.push_back(vec_L5[w]->channel);



                        // EMC Energy after the energy cut

                        if (true_multiplicity > 1)
                        {
                            for (int i = 0; i < emc_matrix_size; i++)
                            {

                                if (emc_energy_C[i] > 1)
                                {

                                    h_EMC_EnergyCut_track[i]->Fill(emc_energy_C[i]);
                                    h_EMC_sumEnergyCut_track->Fill(emc_energy_C[i]);
                                }
                            }
                        }

                    }


                    if (vec_L5[w]->layer == 1 && vec_L5[w]->fee_channel % 2 == 0)
                    {

                        h_STT_EMC_d2->Fill((38400 - vec_L5[w]->leadTime) - emcTime);
                    }

                    else if (vec_L5[w]->layer == 1 && vec_L5[w]->fee_channel % 2 != 0)
                    {

                        h_STT_EMC_d1->Fill((38400 - vec_L5[w]->leadTime) - emcTime);
                    }

                    if (vec_L5[w]->layer == 2 && vec_L5[w]->fee_channel % 2 == 0)
                    {

                        h_STT_EMC_d4->Fill((38400 - vec_L5[w]->leadTime) - emcTime);
                    }

                    else if (vec_L5[w]->layer == 2 && vec_L5[w]->fee_channel % 2 != 0)
                    {
                        h_STT_EMC_d3->Fill((38400 - vec_L5[w]->leadTime) - emcTime);
                    }

                    if (vec_L5[w]->layer == 3 && vec_L5[w]->fee_channel % 2 == 0)
                    {

                        h_STT_EMC_d6->Fill((38400 - vec_L5[w]->leadTime) - emcTime);
                    }

                    else if (vec_L5[w]->layer == 3 && vec_L5[w]->fee_channel % 2 != 0)
                    {
                        h_STT_EMC_d5->Fill((38400 - vec_L5[w]->leadTime) - emcTime);
                    }

                    if (vec_L5[w]->layer == 4 && vec_L5[w]->fee_channel % 2 == 0)
                    {

                        h_STT_EMC_d8->Fill((38400 - vec_L5[w]->leadTime) - emcTime);
                    }

                    else if (vec_L5[w]->layer == 4 && vec_L5[w]->fee_channel % 2 != 0)
                    {
                        h_STT_EMC_d7->Fill((38400 - vec_L5[w]->leadTime) - emcTime);
                    }


                    // printf("%f\n", (38400 - vec_L5[w]->leadTime) - emcTime);
                    // cout << "w: " << vec_L5[w]->leadTime
                    //    << "time:" << (38400 - vec_L5[w]->leadTime) - emcTime << endl;
                }
                            	DR_Tree->Fill();


        	vec_o_test.clear();
        	vec_x.clear();
        	        	vec_y.clear();
        	vec_z.clear();
        	        	vec_layer.clear();
        	vec_module.clear();
        	        	vec_fee.clear();
        	vec_fee_ch.clear();


                // cout << "delT :" << delT << endl;

                meanTime /= vec_L5.size();

                if (((38400 - meanTime) - emcTime) > 220 && ((38400 - meanTime) - emcTime) < 450)
                {
                    if (true_multiplicity > 1)
                    {
                        for (int i = 0; i < emc_matrix_size; i++)
                        {

                            if (emc_energy_C[i] > 1)
                            {
                                h_STT_EMC_crystmult->Fill(i);
                                h_EMC_EnergyCut2_track[i]->Fill(emc_energy_C[i]);
                                h_EMC_sumEnergyCut2_track->Fill(emc_energy_C[i]);
                            }
                        }
                    }
                }
            }

            else
            {
                h_STT_EMC_cosmic->Fill(0);
            }


            for (int m = 0; m < vec_L1.size(); m++)
            {

                for (int n = 0; n < vec_L2.size(); n++)
                {

                    h_STT_EMC_L1L2->Fill((32 * (vec_L1[m]->module - 1))
                            + (16 * (vec_L1[m]->fee - 1)) + (vec_L1[m]->fee_channel),
                        (32 * (vec_L2[n]->module - 1)) + (16 * (vec_L2[n]->fee - 1))
                            + (vec_L2[n]->fee_channel));
                }
            }


            for (int o = 0; o < vec_L3.size(); o++)
            {

                for (int p = 0; p < vec_L4.size(); p++)
                {

                    h_STT_EMC_L3L4->Fill((32 * (vec_L3[o]->module - 1))
                            + (16 * (vec_L3[o]->fee - 1)) + (vec_L3[0]->fee_channel),
                        (32 * (vec_L4[p]->module - 1)) + (16 * (vec_L4[p]->fee - 1))
                            + (vec_L4[p]->fee_channel));
                }
            }


            //===================================================================
            //
            // Event printout
            /*if(ev_prn){
               printf("---------- %i\n",emc_Hits_ADC_channel->size());
               hi = 0;
               for(UInt_t h=0;h<emc_Hits_ADC_channel->size();h++){
               printf("%i(t%.1f);
               ",emc_Hits_ADC_channel->at(h),(float)emc_Hits_local_time->at(h)/2048);
               }
               std::cout << "\n";
               for(UInt_t cl=0;cl<emc_Cluster_N_hits->size();cl++){
               printf("Cluster #%i: hits %i\n",cl,emc_Cluster_N_hits->at(cl));
               printf("  Hits (Ch):");
               for(UInt_t h=hi;h<hi+emc_Cluster_N_hits->at(cl);h++)
               printf("
               %i(E%x,s%x);",emc_Hits_ADC_channel->at(h),emc_Hits_Energy->at(h),emc_Hits_status->at(h));
               printf("\n");
               hi += emc_Cluster_N_hits->at(cl);
               }
               } */

        } // end of the loop over clusters

        if (emcCosmic == true && sttCosmic == true)
            
            

        if (emcCosmic == true)
            h_STT_counts->Fill(3);


        if (sttCosmic == true)
            h_stt_cosmic->Fill(1);





    } // end of event loop.//////////////////////////////////////////////

            file3.close();
    //--------
cout<<"Number of drifttimes :  "<<counterofdt<<endl;


    // Drift Radius ////////////////////////////////////////////////////


    int d = 0;
    int sum = 0;

//Only under 450ns.

    for (int r = 0; r < vec_o_test1.size(); r++)
    {
        if (vec_o_test1[r] <= 450)
        {
            vec_test.push_back(vec_o_test1[r]);
                        driftTimeCounter2++;

        }
    }

//Sort the vector.

    std::sort(vec_test.begin(), vec_test.end());

    /*for (int z = 0; z < vec_test.size(); z++)
    {
        //   file2 << vec_test[z] << endl;
        // cout << vec_test[z]<<endl;
        if (vec_test[z] <= 450.000)
        {
        }
    }*/
    cout << "counttts:  " << driftTimeCounter2 << endl;


// Ignore the decimals of the drifttimes.

    for (int t = 0; t < vec_test.size(); t++)
    {
        // cout << seeme[t] << endl;
        int x = (vec_test[t] * 100) / 100;
        vec_roundoff.push_back(x);
    }


// Calculate the occurances of each drift time.

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

    int max_dr = driftTimeCounter2;
    int dt_range = vec_cumsum.size();

    double a1[dt_range];
    double b1[dt_range];
    double C = 0;
    double R = 0.505;
    double drift_radius = 0;

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

	TGraph* gDriftRadius = new TGraph(dt_range, a1, b1);
	gDriftRadius->SetName("PDAQ_DR");

	gDriftRadius->Write();
    DR_Tree->Write();

}
