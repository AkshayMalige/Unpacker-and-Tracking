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
                           
using namespace std;

bool f_sttHitCompareCell(SttHit* a, SttHit* b)
{
    return (a->cell < b->cell);
}


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


std::vector<SttHit*>  GetPairs(std::vector<SttHit*> vec_get_pairs)
{
    std::vector<SttHit*> vec_fpair_clu;
    std::sort(vec_get_pairs.begin(), vec_get_pairs.end(), f_sttHitCompareCell);   


        for (Int_t sa=0; sa<vec_get_pairs.size(); sa++)
        {

            if ( sa < vec_get_pairs.size()-1)
            {
                if(fabs(vec_get_pairs[sa]->cell - vec_get_pairs[sa+1]->cell) == 1)
                {vec_fpair_clu.push_back(vec_get_pairs[sa]);
                cout<<"PAIR : "<<vec_get_pairs[sa]->layer<<"\t"<<vec_get_pairs[sa]->cell<<endl;}

                else if (sa >0)
                {
                    if(fabs(vec_get_pairs[sa-1]->cell - vec_get_pairs[sa]->cell) == 1)
                    vec_fpair_clu.push_back(vec_get_pairs[sa]);
                cout<<"PAIR : "<<vec_get_pairs[sa]->layer<<"\t"<<vec_get_pairs[sa]->cell<<endl;

                }

            }

            else if (sa == vec_get_pairs.size()-1)
            {
                if(fabs(vec_get_pairs[sa-1]->cell - vec_get_pairs[sa]->cell) == 1)
                vec_fpair_clu.push_back(vec_get_pairs[sa]);
                cout<<"PAIR : "<<vec_get_pairs[sa]->layer<<"\t"<<vec_get_pairs[sa]->cell<<endl;

            }

         }
            return vec_fpair_clu;

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

    // TFile* Stage2 = new TFile("Stage2.root", "RECREATE");


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

    std::vector<Double_t> vec_test;
    std::vector<Double_t> vec_driftTime;
    std::vector<Double_t> vec_roundoff;
    std::vector<Double_t> vec_occurance;
    std::vector<Double_t> vec_pos_DT;
    std::vector<Double_t> vec_cumsum;
    std::vector<Double_t> vec_drift_radius;


    std::vector<Double_t> vec_x;
    std::vector<Double_t> vec_y;
    std::vector<Double_t> vec_z;
    std::vector<Double_t> vec_layer;
    std::vector<Double_t> vec_module;
    std::vector<Double_t> vec_fee;
    std::vector<Double_t> vec_cell;
    std::vector<Double_t> vec_fee_ch;
    std::vector<Double_t> vec_tdc_ch;

    std::vector<SttHit*> vec_Track_obj;


    TFile* Ttree = new TFile("Drift_Radius_test.root", "RECREATE");
    TTree* DR_Tree = new TTree("DR_Tree", "DR_Tree");

    DR_Tree->Branch("vec_driftTime", &vec_driftTime);
    DR_Tree->Branch("vec_layer", &vec_layer);
    DR_Tree->Branch("vec_x", &vec_x);
    DR_Tree->Branch("vec_y", &vec_y);
    DR_Tree->Branch("vec_z", &vec_z);
    DR_Tree->Branch("vec_module", &vec_module);
    DR_Tree->Branch("vec_fee", &vec_fee);
    DR_Tree->Branch("vec_fee_ch", &vec_fee_ch);
    DR_Tree->Branch("vec_cell", &vec_cell);
    DR_Tree->Branch("vec_tdc_ch", &vec_tdc_ch);


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

    TH1F* h_straw_mean_straw = new TH1F("h_straw_mean_straw", "h_straw_mean_straw", 6000, -1000, 7000);

    TH1F* h_Front = new TH1F("h_Front", "h_Front", 600, 100, 700);    

// TH1F* h_Front[16];
// for (int i = 0; i < 16; i++) 
// {
//     //h_Front[i] = new TH1F(Form("h_Front%d", i + 1), Form("h_Front%d", i + 1), 600, 100, 700 );
//     h_Front[i] = new TH1F(TString::Format("h_Front%i", i), "h_Front", 600, 100, 700);
// }


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

        }

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

                    h_STT_EMC_timeDiff->Fill(vec_stthits[w]->drifttime);


                    meanTime += vec_stthits.at(w)->leadTime;

                    if ((vec_stthits[w]->drifttime) >= 220
                        && (vec_stthits[w]->drifttime) <= 450)

                    {

                        if (vec_stthits.size()<40)
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

            std::vector<SttHit*> vec_pair_layer11;
            std::vector<SttHit*> vec_pair_layer22;
            std::vector<SttHit*> vec_pair_layer33;
            std::vector<SttHit*> vec_pair_layer44;

            vec_pair_layer11.clear();
            vec_pair_layer22.clear();
            vec_pair_layer33.clear();
            vec_pair_layer44.clear();

            if (vec_layer1.size()>1 && vec_layer2.size()>1 && vec_layer3.size()>1 && vec_layer4.size()>1 )
            {
                vec_pair_layer11 = GetPairs(vec_layer1);
                vec_pair_layer22 = GetPairs(vec_layer2);
                vec_pair_layer33 = GetPairs(vec_layer3);
                vec_pair_layer44 = GetPairs(vec_layer4);
                
            }
            else continue;


for (Int_t a =0; a< vec_pair_layer11.size(); a++)
{
 
cout<<"COUT : "<<vec_pair_layer11[a]->cell<<endl;
 }

 // END OF FILTER TO GET ONLY HITS WITH A PAIR////////////////////////////////////////////////////////////
           
            if ( vec_pair_layer11.size() > 0 && vec_pair_layer22.size() > 0 && vec_pair_layer33.size() > 0 && vec_pair_layer44.size() > 0)
            {                
                vec_Cl_L1 = clusterfinder(&vec_pair_layer11);
                vec_Cl_L2 = clusterfinder(&vec_pair_layer22);
                vec_Cl_L3 = clusterfinder(&vec_pair_layer33);
                vec_Cl_L4 = clusterfinder(&vec_pair_layer44);                
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

                vec_All_X.push_back(vec_ClustersX);
                vec_All_Y.push_back(vec_ClustersY);

                Double_t clusterArrayX[vec_ClustersX.size()];
                Double_t clusterArrayZx[vec_ClustersX.size()];              
                Double_t clusterArrayY[vec_ClustersY.size()];               
                Double_t clusterArrayZy[vec_ClustersY.size()];  


                for (Int_t yb=0; yb<vec_ClustersX.size(); yb++)
                {
                    clusterArrayX[yb]=vec_ClustersX[yb]->x;
                    clusterArrayZx[yb]=vec_ClustersX[yb]->z;
                }
    
                    
                for (Int_t yc=0; yc<vec_ClustersY.size(); yc++)
                {
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

                //vec_emcX.push_back(extrpX);
    
                TGraph* chiY = new TGraph(vec_ClustersY.size(), clusterArrayY, clusterArrayZy);
                chiY->Fit(f2,"QN");
                chi_valueY = f2->GetChisquare();
                vec_Chi2y.push_back(chi_valueY);
                Double_t pp0 = f2->GetParameter(0);
                Double_t pp1 = f2->GetParameter(1);
                Double_t extrpY = ((65 - pp0) / pp1);

                //vec_emcY.push_back(extrpY);

                Double_t sumChi = (chi_valueX + chi_valueY);

                cout<<"X CHI :"<<chi_valueX<<"\t"<<"Y CHI"<<chi_valueY<<endl;

                cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^Chi X : "<<chi_valueX<<"\t"<<"Chi Y : "<<chi_valueY<<"^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
            }
        }
    }   

}

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

    for (Int_t cj = 0; cj < vec_Chi2y.size(); cj++) 
    {
        cout << "chiSquare Y :" << vec_Chi2y[cj] << endl;

        if (smallestY > vec_Chi2y[cj]) 
        {
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
    vec_driftTime.clear();
    vec_x.clear();
    vec_y.clear();
    vec_z.clear();
    vec_layer.clear();
    vec_module.clear();
    vec_fee.clear();
    vec_fee_ch.clear();
    vec_cell.clear();
    vec_tdc_ch.clear();

    for (Int_t tq=0; tq<vec_tracks.size(); tq++)
    {
        cout<<"TRACKS  : "<<vec_tracks[tq]->layer<<"\t"<<vec_tracks[tq]->cell<<"\t"<<vec_tracks[tq]->channel<<endl;

        vec_driftTime.push_back(vec_tracks[tq]->drifttime);
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

    vec_Chi2x.clear();
    vec_Chi2y.clear();

    DR_Tree->Fill();

  }

    std::vector<Int_t> vec_dr_channel;
    std::vector<Int_t> vec_dr_correction;
    Int_t ar_dr_channel[296];
    Int_t ar_dr_correction[296];

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
    cout<<"FrontEnd : "<<ch<<"| Y max : "<<maximum<<"|  threshold : "<<y_th<<"|  bin@th :"<<gbinx<<endl;
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
dr_correction->Write();

/////////////////////////////////////////////////////////END of Drift Time calliberation////////////////////////////////////////////////

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

    h_STT_EMC_td1->Write();
    h_STT_EMC_td2->Write();
    h_STT_EMC_td3->Write();
    h_STT_EMC_td4->Write();
    h_XvsZ->Write();
    h_YvsZ->Write();
    h_STT_EMC_timeDiff->Write();
    h_straw_mean_straw->Write();

    return 0;
}

