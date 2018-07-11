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
#include "cluster.h"

// #ifdef __MAKECINT__
// #pragma link C++ class vector<UInt_t>+;
// #pragma link C++ class vector<Int_t>+;
// #pragma link C++ class vector<UShort_t>+;
// #pragma link C++ class vector<UChar_t>+;
// #pragma link C++ class SttEvent+;
// #pragma link C++ class SttHit+;
// #pragma link C++ class cluster+;
// #endif                               

using namespace std;

bool sttHitCompareLeadTime(SttHit* a, SttHit* b)
{
    return (a->cell < b->cell);
}

Bool_t sorthit(double a, double b)
{
    return (a < b);
}

void Print()
{
     cout<<"Print"<<endl;
    return;
}

//cluster cluu;

std::vector<std::vector<SttHit*>*>* clusterfinder(std::vector<SttHit*>* vec_flayer)
{
    std::vector<std::vector<SttHit*>*>* vec_Cl = new std::vector<std::vector<SttHit*>*>();
    std::vector<SttHit*>* clusterPointer;

    //std::sort(vec_flayer->begin(), vec_flayer->end(), f_sttHitCompareCell);   
            
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


Bool_t stage2(void)
{

    TFile file("Stage1.root", "READ");
    TTree* tree = (TTree*)file.Get("Stage1");
    if (!tree) {
        std::cerr << "Tree doesn't exists" << std::endl;
        return 1;
    }
    tree->Print();
    TFile* Stage2 = new TFile("Stage2.root", "RECREATE");

    std::vector<double>* vec_Stage_DT = 0;
    std::vector<double>* vec_Stage_x = 0;
    std::vector<double>* vec_Stage_y = 0;
    std::vector<double>* vec_Stage_z = 0;
    std::vector<double>* vec_Stage_layer = 0;
    std::vector<double>* vec_Stage_module = 0;
    std::vector<double>* vec_Stage_fee = 0;
    std::vector<double>* vec_Stage_cell = 0;
    std::vector<double>* vec_Stage_fee_ch = 0;
    std::vector<double>* vec_Stage_tdc_ch = 0;
    std::vector<double>* vec_Stage_leadtime = 0;
    std::vector<double>* vec_Stage_trailtime = 0;
    
    std::vector<SttHit*> vec_stthits;
    std::vector<SttHit*> vec_Allhits;
    std::vector<double> vec_dum;

    tree->SetBranchAddress("vec_Stage_DT", &vec_Stage_DT);
    tree->SetBranchAddress("vec_Stage_x", &vec_Stage_x);
    tree->SetBranchAddress("vec_Stage_y", &vec_Stage_y);
    tree->SetBranchAddress("vec_Stage_z", &vec_Stage_z);
    tree->SetBranchAddress("vec_Stage_layer", &vec_Stage_layer);
    tree->SetBranchAddress("vec_Stage_module", &vec_Stage_module);
    tree->SetBranchAddress("vec_Stage_fee", &vec_Stage_fee);
    tree->SetBranchAddress("vec_Stage_cell", &vec_Stage_cell);
    tree->SetBranchAddress("vec_Stage_fee_ch", &vec_Stage_fee_ch);
    tree->SetBranchAddress("vec_Stage_tdc_ch", &vec_Stage_tdc_ch);
    tree->SetBranchAddress("vec_Stage_leadtime", &vec_Stage_leadtime);
    tree->SetBranchAddress("vec_Stage_trailtime", &vec_Stage_trailtime);

    TH1F* h_STT_EMC_td1 = new TH1F("h_STT_EMC_td1", "h_STT_EMC_td1", 1000, 0, 1000);
    TH1F* h_STT_EMC_td2 = new TH1F("h_STT_EMC_td2", "h_STT_EMC_td2", 1000, 0, 1000);
    TH1F* h_STT_EMC_td3 = new TH1F("h_STT_EMC_td3", "h_STT_EMC_td3", 1000, 0, 1000);
    TH1F* h_STT_EMC_td4 = new TH1F("h_STT_EMC_td4", "h_STT_EMC_td4", 1000, 0, 1000);
    TH2F* h_XvsZ = new TH2F("h_XvsZ", "h_XvsZ", 100, -20, 80, 100, -20, 80);
    TH2F* h_YvsZ = new TH2F("h_YvsZ", "h_YvsZ", 100, 0, 100, 100, 0, 100);
    TH1F* h_STT_EMC_timeDiff = new TH1F("h_STT_EMC_timeDiff", "h_STT_EMC_timeDiff", 600, 100, 700);

    TH1F* h_cell_diff_L1 = new TH1F("h_cell_diff_L1", "h_cell_diff_L1", 66, -2, 64);
    TH1F* h_cell_diff_L2 = new TH1F("h_cell_diff_L2", "h_cell_diff_L2", 66, -2, 64);
    TH1F* h_cell_diff_L3 = new TH1F("h_cell_diff_L3", "h_cell_diff_L3", 66, -2, 64);
    TH1F* h_cell_diff_L4 = new TH1F("h_cell_diff_L4", "h_cell_diff_L4", 66, -2, 64);
    TH1F* h_x_diff_L1 = new TH1F("h_x_diff_L1", "h_x_diff_L1", 64, 0, 32);
    TH1F* h_y_diff_L2 = new TH1F("h_y_diff_L2", "h_y_diff_L2", 64, 0, 32);
    TH1F* h_x_diff_L3 = new TH1F("h_x_diff_L3", "h_x_diff_L3", 64, 0, 32);
    TH1F* h_y_diff_L4 = new TH1F("h_y_diff_L4", "h_y_diff_L4", 64, 0, 32);



    Int_t iev = (Int_t)tree->GetEntries();
    cout << "number of entries in tree:" << iev << endl
         << endl;

    //loop over all the vectors in the tree.

    for (Int_t i = 0; i < iev; i++) 
    {
        tree->GetEntry(i);
        cout << endl
             << endl;
        cout << "entry no. " << i << endl;
        Int_t oiv = vec_Stage_DT->size();
        cout << "vecsize  :" << oiv << endl;
        
        vec_stthits.clear();

       //std::sort(vec_Stage_cell->begin(), vec_Stage_cell->end());


        //Loop over the vector elements//////////////////////////////////////////////////////
        for (int n = 0; n < oiv; n++) 
        {
            SttHit* u = new SttHit();

            u->x            = vec_Stage_x->at(n);
            u->y            = vec_Stage_y->at(n);
            u->z            = vec_Stage_z->at(n);
            u->layer        = vec_Stage_layer->at(n);
            u->module       = vec_Stage_module->at(n);
            u->fee          = vec_Stage_fee->at(n);
            u->fee_channel  = vec_Stage_fee_ch->at(n);
            u->channel      = vec_Stage_tdc_ch->at(n);
            u->leadTime     = vec_Stage_leadtime->at(n);
            u->trailTime    = vec_Stage_trailtime->at(n);
            u->cell         = vec_Stage_cell->at(n);
            u->drifttime    = vec_Stage_DT->at(n);

            vec_stthits.push_back(u);
            vec_Allhits.push_back(u);
            vec_dum.push_back(vec_Stage_cell->at(n));

        }

     // if (vec_stthits.size() > 2)
     // {
         std::sort(vec_stthits.begin(), vec_stthits.end(), sttHitCompareLeadTime);

     // }

    //if (vec_dum.size() > 2)
    // {
        sort(vec_dum.begin(), vec_dum.end(), sorthit);

    // }

        // cluu.cluster();

        Print();

            double meanTime = 0;
            std::vector<SttHit*> vec_layer1;
            std::vector<SttHit*> vec_layer2;
            std::vector<SttHit*> vec_layer3;
            std::vector<SttHit*> vec_layer4;
            vec_layer1.clear();
            vec_layer2.clear();
            vec_layer3.clear();
            vec_layer4.clear();

                for (int w = 0; w < vec_stthits.size(); w++)
                {
                    cout<<"["<<w<<"]"<<" L, M, C, F, Ch, T {"<<vec_stthits[w]->layer<<", "<<vec_stthits[w]->module<<", "<<vec_stthits[w]->cell<<", "<<vec_stthits[w]->fee<<", "<<vec_stthits[w]->fee_channel<<", "<<vec_stthits[w]->channel<<"}  "<<" X , Y , Z :{"<<vec_stthits[w]->x<<", "<<vec_stthits[w]->y<<", "<<vec_stthits[w]->z<<"}   "<<" LT DT  {"<<vec_stthits[w]->leadTime<<",  "<<vec_stthits[w]->drifttime<<"}"<<endl;
                    if (vec_stthits[w]->layer == 1)
                    {
                        h_STT_EMC_td1->Fill(vec_stthits[w]->drifttime);
                        h_XvsZ-> Fill(vec_stthits[w]->x,vec_stthits[w]->z);

                    }
                    else if (vec_stthits[w]->layer == 2)
                    {
                        h_STT_EMC_td2->Fill(vec_stthits[w]->drifttime);
                        h_YvsZ-> Fill(vec_stthits[w]->y,vec_stthits[w]->z);

                    }
                    else if (vec_stthits[w]->layer == 3)
                    {
                        h_STT_EMC_td3->Fill(vec_stthits[w]->drifttime);
                        h_XvsZ-> Fill(vec_stthits[w]->x,vec_stthits[w]->z);

                    }
                    else if (vec_stthits[w]->layer == 4)
                    {
                        h_STT_EMC_td4->Fill(vec_stthits[w]->drifttime);
                        h_YvsZ-> Fill(vec_stthits[w]->y,vec_stthits[w]->z);

                    }

                    //drift time : STT-EMC

                    //h_STT_EMC_timeDiff->Fill(vec_stthits[w]->drifttime);


                    meanTime += vec_stthits.at(w)->leadTime;


                    if ((vec_stthits[w]->drifttime) >= 220 && (vec_stthits[w]->drifttime) <= 450)
                    {

                           //  cout<<"["<<w<<"]";
                           //  printf(": cell,l,m,c,cf=%d,%d,%d,%d,%2d,%2d    x,y,z=%.3f,%.3f,%.3f  lt=%f   dt=%f\n",
                           // vec_stthits[w]->cell,vec_stthits[w]->layer, vec_stthits[w]->module, vec_stthits[w]->channel, vec_stthits[w]->fee_channel,
                           // vec_stthits[w]->x, vec_stthits[w]->y, vec_stthits[w]->z,
                           // vec_stthits[w]->leadTime, vec_stthits[w]->drifttime);

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

                }

            }

    }

    h_STT_EMC_td1->Write();
    h_STT_EMC_td2->Write();
    h_STT_EMC_td3->Write();
    h_STT_EMC_td4->Write();
    h_XvsZ->Write();
    h_YvsZ->Write();
    h_STT_EMC_timeDiff->Write();

    return 0;
}

