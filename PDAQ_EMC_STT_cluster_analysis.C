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
#include <TF1.h>

#include "TRandom.h"
#include "SttHit.h"
#include "SttEvent.h"
// #include "Cluster_Tree.h"

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

TH2F* h_XvsZ;
TH2F* h_YvsZ;

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


TH1F* h_chiX;
TH1F* h_chiY;
TH1F* h_chiXhi;
TH1F* h_chiYhi;
TH1F* h_chiXlo;
TH1F* h_chiYlo;
TH1F* h_chisumAll;
TH1F* h_chisumLo;

TH1F* h_emcX;
TH1F* h_emcY;

TH1F* h_cell_diff_L1;
TH1F* h_cell_diff_L2;
TH1F* h_cell_diff_L3;
TH1F* h_cell_diff_L4;
TH1F* h_x_diff_L1;
TH1F* h_y_diff_L2;
TH1F* h_x_diff_L3;
TH1F* h_y_diff_L4;


TH1F* h_straw_drift;

//const int fee_size = 17;
//TH1F* h_FEE[16];

TH1F* h_Front;

TH1F* h_Front1;
TH1F* h_Front2;
TH1F* h_Front3;
TH1F* h_Front4;
TH1F* h_Front5;
TH1F* h_Front6;
TH1F* h_Front7;
TH1F* h_Front8;
TH1F* h_Front9;
TH1F* h_Front10;
TH1F* h_Front11;
TH1F* h_Front12;
TH1F* h_Front13;
TH1F* h_Front14;
TH1F* h_Front15;
TH1F* h_Front16;
TH1F* h_Front17;

TH1F* h_straw_mean_EMC;
TH1F* h_straw_mean_straw;

TH2F* h_Straw_DriftTime;
TH2F* h_Fee_DriftTime;


int counterofdt;
int counter2 = 0;
Double_t repeat =0;
Double_t All_repeat =0;



//===================================================================

// class Cluster_Tree
// {

// public :
//         std::vector< std::vector<SttHit*> > vec_LoneTrackC;                   
//         std::vector< std:: vector<SttHit*> >vec_PairTrackC;                   

// };

//Sorting LeadTime

bool f_sttHitCompareLeadTime(SttHit* a, SttHit* b)
{
    return (a->leadTime < b->leadTime);
}
//Sorting Cell number

bool f_sttHitCompareCell(SttHit* c, SttHit* d)
{
    return (c->cell < d->cell);
}

// Cluster finding 
std::vector<std::vector<SttHit*>*>* clusterfinder(std::vector<SttHit*>* vec_flayer)
{
    std::vector<std::vector<SttHit*>*>* vec_Cl = new std::vector<std::vector<SttHit*>*>();
    std::vector<SttHit*>* clusterPointer;

    std::sort(vec_flayer->begin(), vec_flayer->end(), f_sttHitCompareCell);   
            
     if (vec_flayer->size() ==1)
    {
        clusterPointer = new std::vector<SttHit*>();
        clusterPointer->push_back(vec_flayer->at(0));
        vec_Cl->push_back(clusterPointer);
        return vec_Cl;
    }
    else 
    {
        for (Int_t aa=0; aa < vec_flayer->size(); aa++ )
        {
         if (aa < vec_flayer->size()-1)
            {
                 if(fabs(vec_flayer->at(aa)->cell - vec_flayer->at(aa+1)->cell) < 2)
                {
                    clusterPointer = new vector<SttHit*>();
                    clusterPointer->push_back(vec_flayer->at(aa));
                    clusterPointer->push_back(vec_flayer->at(aa+1));
                    vec_Cl->push_back(clusterPointer);                           
                } 
                                else if(aa==0)
                                {
                                    clusterPointer = new vector<SttHit*>();
                                    clusterPointer->push_back(vec_flayer->at(aa));
                                    vec_Cl->push_back(clusterPointer); 
                                }
                                else if(aa > 0)
                                {
                                    if(fabs(vec_flayer->at(aa-1)->cell - vec_flayer->at(aa)->cell) == 1) 
                                    {
                                        continue;
                                    } 
                                    
                                    else
                                   {
                                        clusterPointer = new vector<SttHit*>();
                                        clusterPointer->push_back(vec_flayer->at(aa));
                                        vec_Cl->push_back(clusterPointer); 

                                    }

                                }
            }

            else if (aa == vec_flayer->size()-1)
            {
                 if ((fabs(vec_flayer->at(aa-1)->cell - vec_flayer->at(aa)->cell) > 1))
                        {
                            clusterPointer = new vector<SttHit*>();
                            clusterPointer->push_back(vec_flayer->at(aa));
                            vec_Cl->push_back(clusterPointer);
                        } 
             }
        }
        return vec_Cl;
     }

}


//Function to fill histograms with difference in cell and the coordinates
std::vector<SttHit*>  Diff_Cell_X_Y(std::vector<SttHit*> vec_Diff_layer)
{
    if (vec_Diff_layer.size()>1)
    {
        std::sort(vec_Diff_layer.begin(), vec_Diff_layer.end(), f_sttHitCompareCell);

        for (Int_t as =0; as<vec_Diff_layer.size()-1; as++)
        {
            
            if (vec_Diff_layer[as]->layer == 1)
            {
                Double_t diff =0;
                diff = fabs(vec_Diff_layer[as]->cell - vec_Diff_layer[as+1]->cell);
                h_cell_diff_L1->Fill(diff);
                h_x_diff_L1->Fill(fabs(vec_Diff_layer[as]->x - vec_Diff_layer[as+1]->x));
            }
            else if (vec_Diff_layer[as]->layer == 2)
            {
                Double_t diff =0;
                diff = fabs(vec_Diff_layer[as]->cell - vec_Diff_layer[as+1]->cell);
                h_cell_diff_L2->Fill(diff);
                h_y_diff_L2->Fill(fabs(vec_Diff_layer[as]->y - vec_Diff_layer[as+1]->y));
            }
            else if (vec_Diff_layer[as]->layer == 3)
            {
                Double_t diff =0;
                diff = fabs(vec_Diff_layer[as]->cell - vec_Diff_layer[as+1]->cell);
                h_cell_diff_L3->Fill(diff);
                h_x_diff_L3->Fill(fabs(vec_Diff_layer[as]->x - vec_Diff_layer[as+1]->x));
            }
            else if (vec_Diff_layer[as]->layer == 4)
            {
                Double_t diff =0;
                diff = fabs(vec_Diff_layer[as]->cell - vec_Diff_layer[as+1]->cell);
                h_cell_diff_L4->Fill(diff);
                h_y_diff_L4->Fill(fabs(vec_Diff_layer[as]->y - vec_Diff_layer[as+1]->y));
            }
         }

     } 
    return vec_Diff_layer;

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

    MAKE_HST2(h_XvsZ, 100, -20, 80, 100, -20, 80);
    MAKE_HST2(h_YvsZ, 100, 0, 100, 100, 0, 100);

    MAKE_HST(h_STT_EMC_cosmic, 5, 0, 5);
    MAKE_HST(h_STT_EMC_timeDiff, 600, 100, 700);
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
    MAKE_HST(h_chiX, 100, 0, 50);
    MAKE_HST(h_chiY, 100, 0, 50);
    MAKE_HST(h_chiXhi, 100, 0, 50);
    MAKE_HST(h_chiYhi, 100, 0, 50);
    MAKE_HST(h_chiXlo, 100, 0, 50);
    MAKE_HST(h_chiYlo, 100, 0, 50);
    MAKE_HST(h_chisumAll, 100, 0, 50);
    MAKE_HST(h_chisumLo, 100, 0, 50);
    MAKE_HST(h_emcX, 400, -100, 100);
    MAKE_HST(h_chisumLo, 400, -100, 100);

    MAKE_HST(h_cell_diff_L1, 66, -2, 64);
    MAKE_HST(h_cell_diff_L2, 66, -2, 64);
    MAKE_HST(h_cell_diff_L3, 66, -2, 64);
    MAKE_HST(h_cell_diff_L4, 66, -2, 64);

    MAKE_HST(h_x_diff_L1, 64, 0, 32);
    MAKE_HST(h_y_diff_L2, 64, 0, 32);
    MAKE_HST(h_x_diff_L3, 64, 0, 32);
    MAKE_HST(h_y_diff_L4, 64, 0, 32);


    MAKE_HST(h_straw_drift, 600, 100, 700);

    //    char bbuff[200];
    //     sprintf(bbuff, "h_Front%d", j);
    // for (int j = 0; j < 16; j++)
    // {
 
    //     MAKE_HST(h_Front, 600, 100, 700, j, bbuff);
    // }
    MAKE_HST(h_Front, 600, 100, 700);
    MAKE_HST(h_Front1, 600, 100, 700);
    MAKE_HST(h_Front2, 600, 100, 700);
    MAKE_HST(h_Front3, 600, 100, 700);
    MAKE_HST(h_Front4, 600, 100, 700);
    MAKE_HST(h_Front5, 600, 100, 700);
    MAKE_HST(h_Front6, 600, 100, 700);
    MAKE_HST(h_Front7, 600, 100, 700);
    MAKE_HST(h_Front8, 600, 100, 700);
    MAKE_HST(h_Front9, 600, 100, 700);
    MAKE_HST(h_Front10, 600, 100, 700);
    MAKE_HST(h_Front11, 600, 100, 700);
    MAKE_HST(h_Front12, 600, 100, 700);
    MAKE_HST(h_Front13, 600, 100, 700);
    MAKE_HST(h_Front14, 600, 100, 700);
    MAKE_HST(h_Front15, 600, 100, 700);
    MAKE_HST(h_Front16, 600, 100, 700);
    MAKE_HST(h_Front17, 600, 100, 700);

    MAKE_HST(h_straw_mean_EMC, 6000, -1000, 7000);
    MAKE_HST(h_straw_mean_straw, 6000, -1000, 7000);

    MAKE_HST2(h_Straw_DriftTime, 296, 0, 296, 700, 0, 700);
    MAKE_HST2(h_Fee_DriftTime, 16, 0, 16, 700, 0, 700);

    h_STT_EMC_timeDiff->GetXaxis()->SetTitle("Drift Time [ns]");
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

    std::vector<SttHit*> vec_Allhits;

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


    std::vector<Double_t> vec_o_test;
    std::vector<Double_t> vec_o_test1;

    std::vector<Double_t> vec_test;
    std::vector<Double_t> vec_roundoff;
    std::vector<Double_t> vec_occurance;
    std::vector<Double_t> vec_pos_DT;
    std::vector<Double_t> vec_cumsum;
    std::vector<Double_t> vec_drift_radius;
    std::vector<SttHit*> vec_Track_obj;


    std::vector<Double_t> vec_x;
    std::vector<Double_t> vec_y;
    std::vector<Double_t> vec_z;
    std::vector<Double_t> vec_layer;
    std::vector<Double_t> vec_module;
    std::vector<Double_t> vec_fee;
    std::vector<Double_t> vec_cell;
    std::vector<Double_t> vec_fee_ch;
    std::vector<Double_t> vec_tdc_ch;

    std::vector<Double_t> vec_emcX;
    std::vector<Double_t> vec_emcY;



    TFile* Ttree = new TFile("Drift_Radius_test.root", "RECREATE");
    TTree* DR_Tree = new TTree("DR_Tree", "DR_Tree");

    DR_Tree->Branch("Vec_o_test", &vec_o_test);
    DR_Tree->Branch("vec_layer", &vec_layer);
    DR_Tree->Branch("vec_x", &vec_x);
    DR_Tree->Branch("vec_y", &vec_y);
    DR_Tree->Branch("vec_z", &vec_z);
    DR_Tree->Branch("vec_module", &vec_module);
    DR_Tree->Branch("vec_fee", &vec_fee);
    DR_Tree->Branch("vec_fee_ch", &vec_fee_ch);
    DR_Tree->Branch("vec_cell", &vec_cell);
    DR_Tree->Branch("vec_tdc_ch", &vec_tdc_ch);

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

        bool emcCosmic = false;
        bool sttCosmic = false;
        std::vector<SttHit*> vec_filterLeadTime;
        std::vector<SttHit*> vecvec;

        std::vector<SttHit*> vec_L1;
        std::vector<SttHit*> vec_L2;
        std::vector<SttHit*> vec_L3;
        std::vector<SttHit*> vec_L4;
        std::vector<SttHit*> vec_stthits;

        double emcTime = 0;
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

                   /* if (filtercnt == 8)
                    { // in case we already have at least 8 hits within window, break and continue
                        for (int vv = v + 1; vv < vec_leadTime.size() - 1; vv++)
                            h_STT_leadTimeDiff->Fill(fabs(vec_leadTime[v]->leadTime - vec_leadTime[vv]->leadTime));

                        // processing
                        break;
                    }
                    else
                        vec_filterLeadTime.clear();*/
                }
            }

            //  in case we have at least 8 hits within timewindow go with tracking
            if (vec_filterLeadTime.size() > 4)
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


            char buff[10000];
            if (sttCosmic == true && emcCosmic == true)
            {
                printf("Cosmic found in both subsystems in event nr:%d\n", e);

                int local_cnt = 0;
                for (int i = 0; i < stt_events->totalNTDCHits; i++)
                {
                    SttHit* hit  = (SttHit*)stt_events->tdc_hits->ConstructedAt(i); // retrieve particular hit
                    if (hit->isRef) continue;

                    sprintf(buff, "[%d / %d]  cell,l,m,c,cf=%d,%d,%d,%2d,%2d    x,y,z=%.3f,%.3f,%.3f  lt=%f   dt=%f\n",
                           global_cnt, local_cnt,
                           hit->cell, hit->layer, hit->module, hit->channel, hit->fee_channel,
                           hit->x, hit->y, hit->z,
                           hit->leadTime, hit->drifttime);
                    printf(buff);
                    fprintf(fp, buff);
                    ++local_cnt;
                }
                ++global_cnt;


                h_STT_EMC_cosmic->Fill(1);
                h_STT_counts->Fill(4);


                double meanTime = 0;
                int crystalMult = 0;
                double delT = 0;
                int dl1 = 220;
                int dl2 = 450;

            std::vector<SttHit*> vec_strawfilter;
            std::vector<SttHit*> vec_layer1;
            std::vector<SttHit*> vec_layer2;
            std::vector<SttHit*> vec_layer3;
            std::vector<SttHit*> vec_layer4;


                vec_stthits.clear();

                h_STT_EMC_trueMultiplicity->Fill(true_multiplicity);


                for (int q = 0; q < vec_filterLeadTime.size(); q++)
                {
                    SttHit* u = new SttHit();
                    u->x = vec_filterLeadTime.at(q)->x;
                    u->y = vec_filterLeadTime.at(q)->y;
                    u->z = vec_filterLeadTime.at(q)->z;
                    u->layer = vec_filterLeadTime.at(q)->layer;
                    u->module = vec_filterLeadTime.at(q)->module;
                    u->fee = vec_filterLeadTime.at(q)->fee;
                    u->fee_channel = vec_filterLeadTime.at(q)->fee_channel;
                    u->channel = vec_filterLeadTime.at(q)->channel;
                    u->leadTime = vec_filterLeadTime.at(q)->leadTime;
                    u->trailTime = vec_filterLeadTime.at(q)->trailTime;
                    u->cell = vec_filterLeadTime.at(q)->cell;
                    u->drifttime = ((38400 - vec_filterLeadTime.at(q)->leadTime) - emcTime);
                    
                    vec_stthits.push_back(u);
                    vec_Allhits.push_back(u);
                }


                // cut on STT_EMC time difference

                for (int w = 0; w < vec_stthits.size(); w++)
                // Layer wise drift time : STT-EMC
                {
                    if (vec_stthits[w]->layer == 1)
                    {
                        h_STT_EMC_td1->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);
                        h_XvsZ-> Fill(vec_stthits[w]->x,vec_stthits[w]->z);

                    }
                    else if (vec_stthits[w]->layer == 2)
                    {
                        h_STT_EMC_td2->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);
                        h_YvsZ-> Fill(vec_stthits[w]->y,vec_stthits[w]->z);

                    }
                    else if (vec_stthits[w]->layer == 3)
                    {
                        h_STT_EMC_td3->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);
                        h_XvsZ-> Fill(vec_stthits[w]->x,vec_stthits[w]->z);

                    }
                    else if (vec_stthits[w]->layer == 4)
                    {
                        h_STT_EMC_td4->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);
                        h_YvsZ-> Fill(vec_stthits[w]->y,vec_stthits[w]->z);

                    }

                    // drift time : STT-EMC

                    h_STT_EMC_timeDiff->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);

                    meanTime += vec_stthits.at(w)->leadTime;


                    if (((38400 - vec_stthits[w]->leadTime) - emcTime) >= dl1
                        && ((8400 - vec_stthits[w]->leadTime) - emcTime) <= dl2)
                    {

                           /* cout<<"["<<w<<"]";
                            printf(": cell,l,m,c,cf=%d,%d,%d,%d,%2d,%2d    x,y,z=%.3f,%.3f,%.3f  lt=%f   dt=%f\n",
                           vec_stthits[w]->cell,vec_stthits[w]->layer, vec_stthits[w]->module, vec_stthits[w]->channel, vec_stthits[w]->fee_channel,
                           vec_stthits[w]->x, vec_stthits[w]->y, vec_stthits[w]->z,
                           vec_stthits[w]->leadTime, vec_stthits[w]->drifttime);*/


//can write a function to this


                        if (vec_stthits.size()<30)
                        {
                            if (vec_stthits[w]->layer == 1)
                            {
                                vec_layer1.push_back(vec_stthits[w]);
                            }
                            else if (vec_stthits[w]->layer == 2)
                            {
                                vec_layer2.push_back(vec_stthits[w]);
                            }
                            else if (vec_stthits[w]->layer == 3)
                            {
                                vec_layer3.push_back(vec_stthits[w]);
                            }
                            else if (vec_stthits[w]->layer == 4)
                            {
                                vec_layer4.push_back(vec_stthits[w]);
                            }

                        }

                        // EMC Energy after the energy cut

                        if (true_multiplicity > 1)
                        {
                            for (Int_t i = 0; i < emc_matrix_size; i++)
                            {

                                if (emc_energy_C[i] > 1)
                                {

                                    h_EMC_EnergyCut_track[i]->Fill(emc_energy_C[i]);
                                    h_EMC_sumEnergyCut_track->Fill(emc_energy_C[i]);
                                }
                            }
                        }

                    }


//Plot single later wise drift time

                    if (vec_stthits[w]->layer == 1 && vec_stthits[w]->fee_channel % 2 == 0)
                    {

                        h_STT_EMC_d2->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);
                    }

                    else if (vec_stthits[w]->layer == 1 && vec_stthits[w]->fee_channel % 2 != 0)
                    {

                        h_STT_EMC_d1->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);
                    }

                    if (vec_stthits[w]->layer == 2 && vec_stthits[w]->fee_channel % 2 == 0)
                    {

                        h_STT_EMC_d4->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);
                    }

                    else if (vec_stthits[w]->layer == 2 && vec_stthits[w]->fee_channel % 2 != 0)
                    {
                        h_STT_EMC_d3->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);
                    }

                    if (vec_stthits[w]->layer == 3 && vec_stthits[w]->fee_channel % 2 == 0)
                    {

                        h_STT_EMC_d6->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);
                    }

                    else if (vec_stthits[w]->layer == 3 && vec_stthits[w]->fee_channel % 2 != 0)
                    {
                        h_STT_EMC_d5->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);
                    }

                    if (vec_stthits[w]->layer == 4 && vec_stthits[w]->fee_channel % 2 == 0)
                    {

                        h_STT_EMC_d8->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);
                    }

                    else if (vec_stthits[w]->layer == 4 && vec_stthits[w]->fee_channel % 2 != 0)
                    {
                        h_STT_EMC_d7->Fill((38400 - vec_stthits[w]->leadTime) - emcTime);
                    }


                    // printf("%f\n", (38400 - vec_stthits[w]->leadTime) - emcTime);
                    // cout << "w: " << vec_stthits[w]->leadTime
                    //    << "time:" << (38400 - vec_stthits[w]->leadTime) - emcTime << endl;
                }


Diff_Cell_X_Y(vec_layer1);
Diff_Cell_X_Y(vec_layer2);
Diff_Cell_X_Y(vec_layer3);
Diff_Cell_X_Y(vec_layer4);


/////////////////////////////////////////////////////////////////CLUSTER FILTERING///////////////////////////////////////////////          
            
            std::vector< vector<SttHit*>* >* vec_Cl_L1;
            std::vector< vector<SttHit*>* >* vec_Cl_L2;
            std::vector< vector<SttHit*>* >* vec_Cl_L3;
            std::vector< vector<SttHit*>* >* vec_Cl_L4;

            std::vector<SttHit*> vec_Clusters;

            std::vector<double> vec_Chi2x;
            std::vector<double> vec_Chi2y;


// FILTER TO GET ONLY HITS WITH A PAIR////////////////////////////////////////////////////////////
std::vector<SttHit*> vec_pair_clu;
vec_pair_clu.clear();

if (vec_layer1.size()>1 && vec_layer2.size()>1 && vec_layer3.size()>1 && vec_layer4.size()>1 )
{

        for (Int_t sa=0; sa<vec_layer1.size(); sa++)
        {

            if ( sa < vec_layer1.size()-1)
            {
                if(fabs(vec_layer1[sa]->cell - vec_layer1[sa+1]->cell) == 1)
                vec_pair_clu.push_back(vec_layer1[sa]);

                else if (sa >0)
                {
                    if(fabs(vec_layer1[sa-1]->cell - vec_layer1[sa]->cell) == 1)
                    vec_pair_clu.push_back(vec_layer1[sa]);

                }

            }

            else if (sa == vec_layer1.size()-1)
            {
                if(fabs(vec_layer1[sa-1]->cell - vec_layer1[sa]->cell) == 1)
                vec_pair_clu.push_back(vec_layer1[sa]);

            }

         }
    

        for (Int_t sb=0; sb<vec_layer2.size(); sb++)
        {
            if ( sb < vec_layer2.size()-1)
            {
                if(fabs(vec_layer2[sb]->cell - vec_layer2[sb+1]->cell) == 1)
                vec_pair_clu.push_back(vec_layer2[sb]);

                else if (sb >0)
                {
                    if(fabs(vec_layer2[sb-1]->cell - vec_layer2[sb]->cell) == 1)
                    vec_pair_clu.push_back(vec_layer2[sb]);

                }

            }

            else if (sb == vec_layer2.size()-1)
            {
                if(fabs(vec_layer2[sb-1]->cell - vec_layer2[sb]->cell) == 1)
                vec_pair_clu.push_back(vec_layer2[sb]);

            }

         }
    

        for (Int_t sc=0; sc<vec_layer3.size(); sc++)
        {
            if ( sc < vec_layer3.size()-1)
            {
                if(fabs(vec_layer3[sc]->cell - vec_layer3[sc+1]->cell) == 1)
                vec_pair_clu.push_back(vec_layer3[sc]);

                else if (sc >0)
                {
                    if(fabs(vec_layer3[sc-1]->cell - vec_layer3[sc]->cell) == 1)
                    vec_pair_clu.push_back(vec_layer3[sc]);

                }

            }

            else if (sc == vec_layer3.size()-1)
            {
                if(fabs(vec_layer3[sc-1]->cell - vec_layer3[sc]->cell) == 1)
                vec_pair_clu.push_back(vec_layer3[sc]);

            }

         }
    

        for (Int_t sd=0; sd<vec_layer4.size(); sd++)
        {
            if ( sd < vec_layer4.size()-1)
            {
                if(fabs(vec_layer4[sd]->cell - vec_layer4[sd+1]->cell) == 1)
                vec_pair_clu.push_back(vec_layer4[sd]);

                else if (sd >0)
                {
                    if(fabs(vec_layer4[sd-1]->cell - vec_layer4[sd]->cell) == 1)
                    vec_pair_clu.push_back(vec_layer4[sd]);

                }

            }

            else if (sd == vec_layer4.size()-1)
            {
                if(fabs(vec_layer4[sd-1]->cell - vec_layer4[sd]->cell) == 1)
                vec_pair_clu.push_back(vec_layer4[sd]);

            }

         }    
}
else continue;


    std::vector<SttHit*> vec_pair_layer1;
    std::vector<SttHit*> vec_pair_layer2;
    std::vector<SttHit*> vec_pair_layer3;
    std::vector<SttHit*> vec_pair_layer4;

    vec_pair_layer1.clear();
    vec_pair_layer2.clear();
    vec_pair_layer3.clear();
    vec_pair_layer4.clear();

Int_t LOne = 0;
Int_t LTwo = 0;
Int_t LThree = 0;
Int_t LFour = 0;


for (Int_t q=0; q < vec_pair_clu.size(); q++)
{ 
    cout<<"Pair vector : "<<vec_pair_clu[q]->cell<<"\t"<<((38400 - vec_pair_clu[q]->leadTime) - emcTime)<<"\t"<<emcTime<<endl;

        if (vec_pair_clu[q]->layer == 1)
        {
            vec_pair_layer1.push_back(vec_pair_clu[q]);
            LOne++;
        }
        else if (vec_pair_clu[q]->layer == 2)
        {
            vec_pair_layer2.push_back(vec_pair_clu[q]);
            LTwo++;
        }
        else if (vec_pair_clu[q]->layer == 3)
        {
            vec_pair_layer3.push_back(vec_pair_clu[q]);
            LThree++;
        }
        else if (vec_pair_clu[q]->layer == 4)
        {
            vec_pair_layer4.push_back(vec_pair_clu[q]);
            LFour++;
        }

 }


 // END OF FILTER TO GET ONLY HITS WITH A PAIR////////////////////////////////////////////////////////////
            if ( LOne > 0 && LTwo > 0 && LThree > 0 && LFour > 0)
            {
                if (vec_pair_layer1.size() > 0  )
                {
                    vec_Cl_L1 = clusterfinder(&vec_pair_layer1);
                }

                if (vec_pair_layer2.size() > 0 )
                {
                    vec_Cl_L2 = clusterfinder(&vec_pair_layer2);
                }
                if (vec_pair_layer2.size() > 0 )
                {
                    vec_Cl_L3 = clusterfinder(&vec_pair_layer3);
                }
                if (vec_pair_layer2.size() > 0 )
                {
                    vec_Cl_L4 = clusterfinder(&vec_pair_layer4);
                }
            }
            else continue;


std::vector< vector<SttHit*> > vec_All_X;
std::vector< vector<SttHit*> > vec_All_Y;
vec_All_X.clear();
vec_All_Y.clear();




for (Int_t xa=0; xa<vec_Cl_L1->size(); xa++)
{

    for (Int_t xb=0; xb<vec_Cl_L2->size(); xb++)
    {
        for (Int_t xc=0; xc< vec_Cl_L3->size(); xc++)
        {
            for (Int_t xd=0; xd< vec_Cl_L4->size(); xd++)
            {
                    vec_Clusters.clear();

                    for (Int_t xaa =0; xaa< vec_Cl_L1->at(xa)->size(); xaa++)
                    {
                        //cout<< "Vector  : "<<vec_Cl_L1->at(xa)->at(xaa)->layer <<"\t"<< vec_Cl_L1->at(xa)->at(xaa)->cell<<endl;
                        vec_Clusters.push_back(vec_Cl_L1->at(xa)->at(xaa));
                    }               

                    for (Int_t xbb=0; xbb< vec_Cl_L2->at(xb)->size(); xbb++ )
                    {
                        //cout<< "Vector  : "<<vec_Cl_L2->at(xb)->at(xbb)->layer <<"\t"<< vec_Cl_L2->at(xb)->at(xbb)->cell<<endl;
                        vec_Clusters.push_back(vec_Cl_L2->at(xb)->at(xbb));
                    }

                    for (Int_t xcc=0; xcc< vec_Cl_L3->at(xc)->size(); xcc++ )
                    {
                        //cout<< "Vector  : "<<vec_Cl_L3->at(xc)->at(xcc)->layer <<"\t"<< vec_Cl_L3->at(xc)->at(xcc)->cell<<endl;
                        vec_Clusters.push_back(vec_Cl_L3->at(xc)->at(xcc));
                    }

                    for (Int_t xdd=0; xdd< vec_Cl_L4->at(xd)->size(); xdd++ )
                    {
                        //cout<< "Vector  : "<<vec_Cl_L4->at(xd)->at(xdd)->layer <<"\t"<< vec_Cl_L4->at(xd)->at(xdd)->cell<<endl;
                        vec_Clusters.push_back(vec_Cl_L4->at(xd)->at(xdd));

                    }
//cout<<endl;

        Double_t chi_valueX =0;
        Double_t chi_valueY =0;
        Int_t loneCounterX =0;
        Int_t loneCounterY =0;

        std::vector<SttHit*> vec_ClustersX;
        std::vector<SttHit*> vec_ClustersY;

        vec_ClustersX.clear();
        vec_ClustersY.clear();

                    for (Int_t ya=0; ya<vec_Clusters.size(); ya++)
                    {
                        cout<< " Cluster Vector :"<<vec_Clusters[ya]->layer<<"\t"<<vec_Clusters[ya]->cell<<"\t"<<vec_Clusters[ya]->x<<"\t"<<vec_Clusters[ya]->y<<endl;
                        if (vec_Clusters[ya]->layer == 1 || vec_Clusters[ya]->layer ==3)
                        {
                            vec_ClustersX.push_back(vec_Clusters[ya]);
                            loneCounterX++;
                        }
                        if (vec_Clusters[ya]->layer == 2 || vec_Clusters[ya]->layer ==4)
                        {
                            vec_ClustersY.push_back(vec_Clusters[ya]);
                            loneCounterY++;
                        }
                    }

     //                cout<<"(LONE COUNT : "<<loneCounterX<<"-"<<loneCounterY<<")"<<endl;
                    vec_All_X.push_back(vec_ClustersX);
                    vec_All_Y.push_back(vec_ClustersY);

                    // if (loneCounterX < 3 || loneCounterY < 3)
                    // {
                    //     clt.vec_LoneTrackC.push_back(vec_Clusters);
                    //  }

                    //  else 
                    //     clt.vec_PairTrackC.push_back(vec_Clusters);


                Double_t clusterArrayX[vec_ClustersX.size()];
                Double_t clusterArrayZx[vec_ClustersX.size()];              
                Double_t clusterArrayY[vec_ClustersY.size()];               
                Double_t clusterArrayZy[vec_ClustersY.size()];  


                for (Int_t yb=0; yb<vec_ClustersX.size(); yb++)
                {
                    //cout<< "X Cluster Vector :"<<vec_ClustersX[yb]->layer<<"\t"<<vec_ClustersX[yb]->cell<<"\t"<<vec_ClustersX[yb]->x<<"\t"<<vec_ClustersX[yb]->y<<"\t"<<vec_ClustersX[yb]->z<<endl;

                    clusterArrayX[yb]=vec_ClustersX[yb]->x;
                    clusterArrayZx[yb]=vec_ClustersX[yb]->z;
                }
    
                    
                for (Int_t yc=0; yc<vec_ClustersY.size(); yc++)
                {
                    //cout<< "Y Cluster Vector :"<<vec_ClustersY[yc]->layer<<"\t"<<vec_ClustersY[yc]->cell<<"\t"<<vec_ClustersY[yc]->x<<"\t"<<vec_ClustersY[yc]->y<<"\t"<<vec_ClustersY[yc]->z<<endl;

                    clusterArrayY[yc]=vec_ClustersY[yc]->y;
                    clusterArrayZy[yc]=vec_ClustersY[yc]->z;
                }
            

                    TF1* f1 = new TF1("f1", "pol1");
                    TF1* f2 = new TF1("f2", "pol1");


                    TGraph* chiX = new TGraph(vec_ClustersX.size(), clusterArrayX, clusterArrayZx);
                    chiX->Fit(f1);
                    chi_valueX = f1->GetChisquare();
                    vec_Chi2x.push_back(chi_valueX);
                    Double_t p0 = f1->GetParameter(0);
                    Double_t p1 = f1->GetParameter(1);
                    Double_t extrpX = ((65 - p0) / p1);

                    vec_emcX.push_back(extrpX);
        
                    TGraph* chiY = new TGraph(vec_ClustersY.size(), clusterArrayY, clusterArrayZy);
                    chiY->Fit(f2,"QN");
                    chi_valueY = f2->GetChisquare();
                    vec_Chi2y.push_back(chi_valueY);
                    Double_t pp0 = f2->GetParameter(0);
                    Double_t pp1 = f2->GetParameter(1);
                    Double_t extrpY = ((65 - pp0) / pp1);

                    vec_emcY.push_back(extrpY);

                    Double_t sumChi = (chi_valueX + chi_valueY);

                    h_chiX->Fill(chi_valueX);
                    h_chiY->Fill(chi_valueY);
                    h_chisumAll->Fill(sumChi);
                    cout<<"X CHI :"<<chi_valueX<<"\t"<<"Y CHI"<<chi_valueY<<endl;

                    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^Chi X : "<<chi_valueX<<"\t"<<"Chi Y : "<<chi_valueY<<"^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
            }
        }
    }   

}

//Track_clusters->Fill();
  //Find the smallest Chi2
std::vector<SttHit*> vec_tracks;
vec_tracks.clear();

    Float_t smallestX = vec_Chi2x[0];
    Int_t chi_indexX = 0;

    for (Int_t ci = 0; ci < vec_Chi2x.size(); ci++) 
    {
        cout << "chiSquare X :" << vec_Chi2x[ci] << endl;

        if (smallestX > vec_Chi2x[ci])
         {
            smallestX = vec_Chi2x[ci];
            chi_indexX = ci;
        }
    }
  Float_t smallestY = vec_Chi2y[0];
    Int_t chi_indexY = 0;

    for (Int_t cj = 0; cj < vec_Chi2y.size(); cj++) {
        cout << "chiSquare Y :" << vec_Chi2y[cj] << endl;

        if (smallestY > vec_Chi2y[cj]) {
            smallestY = vec_Chi2y[cj];
            chi_indexY = cj;
        }
    }
    cout<<"INDEX X:"<<chi_indexX<<"\t"<<"INDEX Y:"<<chi_indexY<<endl;

    for (Int_t ck = 0; ck < vec_All_X.at(chi_indexX).size(); ck++)
    {
        cout<<"       BEST  X      "<< vec_All_X.at(chi_indexX).at(ck)->cell<<endl;
        vec_tracks.push_back(vec_All_X.at(chi_indexX).at(ck));
    }
    for (Int_t cl = 0; cl < vec_All_Y.at(chi_indexY).size(); cl++)
    {
        cout<<"       BEST  Y      "<< vec_All_Y.at(chi_indexY).at(cl)->cell<<endl;
        vec_tracks.push_back(vec_All_Y.at(chi_indexY).at(cl));
    }

Double_t sum_leadtime = 0.0;
Double_t mean_leadtime = 0.0;

    for (Int_t tq=0; tq<vec_tracks.size(); tq++)
    {
        cout<<"TRACKS  : "<<vec_tracks[tq]->layer<<"\t"<<vec_tracks[tq]->cell<<"\t"<<vec_tracks[tq]->channel<<endl;

        delT = (38400 - vec_tracks[tq]->leadTime) - emcTime;
        counterofdt++;
        vec_o_test.push_back(delT);
        vec_o_test1.push_back(delT);

        vec_x.push_back(vec_tracks[tq]->x);
        vec_y.push_back(vec_tracks[tq]->y);
        vec_z.push_back(vec_tracks[tq]->z);
        vec_layer.push_back(vec_tracks[tq]->layer);
        vec_module.push_back(vec_stthits[tq]->module);
        vec_fee.push_back(vec_tracks[tq]->fee);
        vec_fee_ch.push_back(vec_tracks[tq]->fee_channel);
        vec_cell.push_back(vec_tracks[tq]->cell);
        vec_tdc_ch.push_back(vec_tracks[tq]->channel);
        vec_Track_obj.push_back(vec_tracks[tq]);

        sum_leadtime += vec_tracks[tq]->leadTime;

     }

    mean_leadtime = sum_leadtime/vec_tracks.size();

    for ( Int_t tx =0; tx <vec_tracks.size(); tx++)
       {
        h_straw_mean_straw->Fill((vec_tracks[tx]->leadTime- mean_leadtime));
       // cout<<" straw leadtime- mean leadtime : "<<(vec_tracks[tx]->leadTime- mean_leadtime)<<endl;
         }
        h_straw_mean_EMC->Fill( (38400 - mean_leadtime) - emcTime);
       // cout<<"Mean straw - emctime : "<<mean_leadtime<<"   "<<emcTime<<endl;



vec_Chi2x.clear();
vec_Chi2y.clear();



cout<<"*********************************************************************************************************************"<< endl;
/////////////////////////////////////////////////////////////END OF CLUSTER FILTER////////////////////////////////////////////////////////////
         
            DR_Tree->Fill();

            vec_o_test.clear();
            vec_x.clear();
            vec_y.clear();
            vec_z.clear();
            vec_layer.clear();
            vec_module.clear();
            vec_fee.clear();
            vec_fee_ch.clear();
            vec_cell.clear();
            vec_tdc_ch.clear();

            vec_layer1.clear();
            vec_layer2.clear();
            vec_layer3.clear();
            vec_layer4.clear();


                // cout << "delT :" << delT << endl;

                meanTime /= vec_stthits.size();

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

            

        if (emcCosmic == true)
            h_emc_cosmic->Fill(2);


        else if (sttCosmic == true)
            h_stt_cosmic->Fill(1);

        //else  if (emcCosmic == true && sttCosmic == true)
    } // end of event loop.//////////////////////////////////////////////
 

//////////////////////////////////////////////////Drift Time calliberation for straws/////////////////////////////////////////////
std::vector<Int_t> vec_dr_channel;
std::vector<Int_t> vec_dr_correction;
Int_t ar_dr_channel[296];
Int_t ar_dr_correction[296];

// TH1F* h_FEE[16];

// for (Int_t jh=1; jh<17; jh++)
// { 
//     h_FEE[jh] = new TH1F (Form("h_FEE%d",jh),Form("h_FEE%d",jh), 600, 100, 700);
//  }



 for ( Int_t ef=0; ef< vec_Allhits.size(); ef++)
 {
    Int_t FrontEnd = ((4*(vec_Allhits[ef]->layer - 1))+(2*(vec_Allhits[ef]->module)-1)+((vec_Allhits[ef]->fee)-1));
    h_Straw_DriftTime->Fill(vec_Allhits[ef]->channel,vec_Allhits[ef]->drifttime);
    h_Fee_DriftTime->Fill(FrontEnd,vec_Allhits[ef]->drifttime);

    for (Int_t il =1; il<17; il++)
    {
         
        if (FrontEnd == 1)
        {
            h_Front1->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 2)
        {
            h_Front2->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 3)
        {
            h_Front3->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 4)
        {
            h_Front4->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 5)
        {
            h_Front5->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 6)
        {
            h_Front6->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 7)
        {
            h_Front7->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 8)
        {
            h_Front8->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 9)
        {
            h_Front9->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 10)
        {
            h_Front10->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 11)
        {
            h_Front11->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 12)
        {
            h_Front12->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 13)
        {
            h_Front13->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 14)
        {
            h_Front14->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 15)
        {
            h_Front15->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 16)
        {
            h_Front16->Fill(vec_Allhits[ef]->drifttime);

         }
        else if (FrontEnd == 17)
        {
            h_Front17->Fill(vec_Allhits[ef]->drifttime);

         }
    }
  }


// for (Int_t ch = 0; ch<296; ch++)
// {
//  for ( Int_t sq=0; sq< vec_Allhits.size(); sq++)
//  {
//     if (vec_Allhits[sq]->channel == ch)
//     {
//         h_straw_drift->Fill(vec_Allhits[sq]->drifttime);

//      }

//   }

for (Int_t ch = 1; ch<17; ch++)
{
 for ( Int_t sq=0; sq< vec_Allhits.size(); sq++)
 {
    if ((4*(vec_Allhits[sq]->layer - 1))+(2*(vec_Allhits[sq]->module)-1)+((vec_Allhits[sq]->fee)-1) == ch)
    {
        h_Front->Fill(vec_Allhits[sq]->drifttime);

     }

  }

    Int_t maximum = h_Front->GetBinContent(h_Front->GetMaximumBin());
    Int_t y_th = maximum/10;
    Int_t gbinx = 100 + h_Front->FindFirstBinAbove(y_th,1);
    cout<<"Channel : "<<ch<<"| Y max : "<<maximum<<"|  threshold : "<<y_th<<"|  bin@th -"<<gbinx<<endl;
    h_Front->Reset();

    vec_dr_channel.push_back(ch);
    vec_dr_correction.push_back(gbinx);
 }

for (Int_t c=0; c<16; c++)
{
 ar_dr_channel[c] = vec_dr_channel[c];
 ar_dr_correction[c] = vec_dr_correction[c];
 }

TGraph* dr_correction = new TGraph(vec_dr_channel.size(), ar_dr_channel, ar_dr_correction);
dr_correction->SetName("dr_correction");
dr_correction->GetYaxis()->SetRangeUser(220,450);
dr_correction->Write();


/////////////////////////////////////////////////////////END of Drift Time calliberation////////////////////////////////////////////////


Double_t emcX1array[vec_emcX.size()]; 
Double_t emcY1array[vec_emcY.size()]; 
cout<<"sizes : "<<vec_emcX.size()<<"\t"<<vec_emcY.size()<<endl;  

for (Int_t em=0; em<vec_emcX.size(); em++)
{
     emcX1array[em]=vec_emcX[em];
     emcY1array[em]=vec_emcY[em];
     //cout<<"HERE  : "<<vec_emcX[em]<<"\t"<<vec_emcY[em]<<endl;
 }

TGraph* gEMC = new TGraph(vec_emcX.size(), emcX1array, emcY1array);
    gEMC->SetMarkerStyle(3);
    gEMC->SetMarkerSize(1);
    gEMC->SetMarkerColor(2);
    gEMC->SetLineColor(0);
    gEMC->Draw();
//     //--------
// cout<<"Number of drifttimes :  "<<counterofdt<<endl;


    // Drift Radius ////////////////////////////////////////////////////



//Only under 450ns.

std::vector< vector<Double_t> > vec_Fee_drift_time;

for (Int_t ao=1; ao< 17; ao++)
{
     std::vector<Double_t>vec_inFee_drift_time;
     vec_inFee_drift_time.clear();

    for (Int_t ae=0; ae< vec_Track_obj.size(); ae++)
    {
        Int_t FeNo =  ((4*(vec_Track_obj[ae]->layer - 1))+(2*(vec_Track_obj[ae]->module)-1)+((vec_Track_obj[ae]->fee)-1));
        if (FeNo == ao)
        {
            vec_inFee_drift_time.push_back(vec_Track_obj[ae]->drifttime);

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

        //     // Calculate the cummulative sum (integral) of the occurances.

            for (int m = 0; m < vec_occurance.size(); m++)
            {
                int sum = 0;

                for (int k = 0; k < m + 1; k++)
                {
                    sum += vec_occurance[k];
                }

                vec_cumsum.push_back(sum);
            }


        //     //Calculate the drift radius.

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
                //cout<<"CHARRRRRRRRRRRRRR "<<buff<<endl;
    
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
    DR_Tree->Write();
    
    //Track_clusters->Write();

       cout << "Repeated entries  :"<< repeat<<"/"<<All_repeat<<endl;  
       //cout<< "TOTAL ENTRIES : "<< AllCount<<endl;     

    if (fp)
        fclose(fp);
}


void PDAQ_EMC_STT_cluster_analysis() {}