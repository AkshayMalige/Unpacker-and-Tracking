#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <TH1F.h>
#include "TFile.h"
#include <TGraph.h>
#include <TLinearFitter.h>
#include <TH2D.h>
#include "TTree.h"
#include <TNamed.h>
#include <TObject.h>
#include <math.h>
#include <cstdlib>

#include "TRandom.h"
#include "SttHit.h"
#include "SttEvent.h"

using namespace std;

Bool_t Drift_Radius(void)
{
    TFile file("Drift_Radius_test.root", "READ");
    TTree* tree = (TTree*)file.Get("DR_Tree");

    f1 = new TF1("f1", "pol1");
    f2 = new TF1("f2", "pol1");
    f3 = new TF1("f3", "pol1");
    f4 = new TF1("f4", "pol1");

    TFile* driftfile1 = new TFile("XYZ_Coordinates.root", "RECREATE");
    Double_t theta_X =0;
    Double_t theta_Y =0;

    TH1F* hx = new TH1F("hx", "dummy_resolutionX", 500, -1, 4);
    TH1F* hy = new TH1F("hy", "dummy_resolutionY", 500, -1, 4);
    TH1F* DR = new TH1F("hy", "drift_radius", 350, 0, 350);
    TH1F *h_theeta_X =new TH1F("h_theeta_X","h_theeta_X",50,-5,5);
    TH1F *h_theeta_Y =new TH1F("h_theeta_Y","h_theeta_Y",50,-5,5);

    TH1F* Z_value = new TH1F("Z_value", "dummy", 5, 0, 5);

    TH2F* h_Straw_DriftTime = new TH2F("h_Straw_DriftTime", "h_Straw_DriftTime", 296, 0, 296, 700, -100, 600);
    TH2F* h_Fee_DriftTime = new TH2F("h_Fee_DriftTime", "h_Fee_DriftTime", 16, 0, 16, 700, -100, 600);

    TH2F* h_projectionX = new TH2F("h_projectionX", "h_projectionX", 200, -100, 100, 100, 0, 100);
    TH2F* h_projectionY = new TH2F("h_projectionY", "h_projectionY", 200, -100, 100, 100, 0, 100);


    std::vector<double>* vec_driftTime;
    std::vector<double>* vec_x;
    std::vector<double>* vec_y;
    std::vector<double>* vec_z;
    std::vector<double>* vec_layer;
    std::vector<double>* vec_module;
    std::vector<double>* vec_fee;
    std::vector<double>* vec_fee_ch;
    std::vector<double>* vec_tdc_ch;
    std::vector<SttHit*> vec_dr_xaxis[2];
    std::vector<SttHit*> vec_dr_yaxis[2];
    std::vector<double> vec_driftradius;
    
    std::vector<double> vec_emcX;
    std::vector<double> vec_emcY;
    std::vector<double> vec_emcZ;


    std::vector<double> vec_Xtheta;
    std::vector<double> vec_Ytheta;

    std::vector<double> vec_Xsr;
    std::vector<double> vec_Ysr;

    std::vector<SttHit*> vec_All_Hits;

    Double_t a1[230];
    Double_t b1[230];

    Double_t ar_ch[296];
    Double_t ar_corr[296];

    Double_t zaxis[16];

    Double_t A1[100];
    Double_t A2[100];

    Double_t B1[100];
    Double_t B2[100];
   
    Double_t F1[2000];
    Double_t F2[2000];  
    Double_t F3[2000];
    Double_t F4[2000];
    Double_t F5[2000];
    Double_t F6[2000];
    Double_t F7[2000];
    Double_t F8[2000];
    Double_t F9[2000];
    Double_t F10[2000];  
    Double_t F11[2000];
    Double_t F12[2000];
    Double_t F13[2000];
    Double_t F14[2000];
    Double_t F15[2000];
    Double_t F16[2000];
    Double_t F17[2000];
    Double_t F18[2000];  
    Double_t F19[2000];
    Double_t F20[2000];
    Double_t F21[2000];
    Double_t F22[2000];
    Double_t F23[2000];
    Double_t F24[2000];
    Double_t F25[2000];
    Double_t F26[2000];  
    Double_t F27[2000];
    Double_t F28[2000];
    Double_t F29[2000];
    Double_t F30[2000];
    Double_t F31[2000];
    Double_t F32[2000];

    Double_t xperfect3[16];
    Double_t yperfect3[16];

    Int_t array_length = 8;
    Int_t pair_length = 2;
    Int_t total_pairs = (array_length / pair_length);
    Int_t no_of_pairs = (total_pairs * total_pairs);

    tree->SetBranchAddress("vec_driftTime", &vec_driftTime);
    tree->SetBranchAddress("vec_x", &vec_x);
    tree->SetBranchAddress("vec_y", &vec_y);
    tree->SetBranchAddress("vec_z", &vec_z);
    tree->SetBranchAddress("vec_layer", &vec_layer);
    tree->SetBranchAddress("vec_module", &vec_module);
    tree->SetBranchAddress("vec_fee", &vec_fee);
    tree->SetBranchAddress("vec_fee_ch", &vec_fee_ch);
    tree->SetBranchAddress("vec_tdc_ch", &vec_tdc_ch);

        TGraph* fee_drift_0 = new TGraph(500, F1, F2);
    fee_drift_0 = (TGraph*)file.Get("fee_drift_0");

        TGraph* fee_drift_1 = new TGraph(500, F3, F4);
    fee_drift_1 = (TGraph*)file.Get("fee_drift_1");

        TGraph* fee_drift_2 = new TGraph(500, F5, F6);
    fee_drift_2 = (TGraph*)file.Get("fee_drift_2");

        TGraph* fee_drift_3 = new TGraph(500, F7, F8);
    fee_drift_3 = (TGraph*)file.Get("fee_drift_3");

        TGraph* fee_drift_4 = new TGraph(500, F9, F10);
    fee_drift_4 = (TGraph*)file.Get("fee_drift_4");

        TGraph* fee_drift_5 = new TGraph(500, F11, F12);
    fee_drift_5 = (TGraph*)file.Get("fee_drift_5");

        TGraph* fee_drift_6 = new TGraph(500, F13, F14);
    fee_drift_6 = (TGraph*)file.Get("fee_drift_6");

        TGraph* fee_drift_7 = new TGraph(500, F15, F16);
    fee_drift_7 = (TGraph*)file.Get("fee_drift_7");

        TGraph* fee_drift_8 = new TGraph(500, F17, F18);
    fee_drift_8 = (TGraph*)file.Get("fee_drift_8");

        TGraph* fee_drift_9 = new TGraph(500, F19, F20);
    fee_drift_9 = (TGraph*)file.Get("fee_drift_9");

        TGraph* fee_drift_10 = new TGraph(500, F21, F22);
    fee_drift_10 = (TGraph*)file.Get("fee_drift_10");

        TGraph* fee_drift_11 = new TGraph(500, F23, F24);
    fee_drift_11 = (TGraph*)file.Get("fee_drift_11");

        TGraph* fee_drift_12 = new TGraph(500, F25, F26);
    fee_drift_12 = (TGraph*)file.Get("fee_drift_12");

        TGraph* fee_drift_13 = new TGraph(500, F27, F28);
    fee_drift_13 = (TGraph*)file.Get("fee_drift_13");

        TGraph* fee_drift_14 = new TGraph(500, F29, F30);
    fee_drift_14 = (TGraph*)file.Get("fee_drift_14");

        TGraph* fee_drift_15 = new TGraph(500, F31, F32);
    fee_drift_15 = (TGraph*)file.Get("fee_drift_15");

    TGraph* dr_correction = new TGraph(296, ar_ch, ar_corr);
    dr_correction = (TGraph*)file.Get("dr_correction");

    Double_t yperfectmean[16];

    SttHit* new_y1 = 0;
    SttHit* new_y2 = 0;

    Int_t iev = (Int_t)tree->GetEntries();
    cout << "number of entries in tree:" << iev << endl
         << endl;

    vector<SttHit*> vec_hits;
    vector<SttHit*> vec_hits_new;
    vec_driftradius.clear();
    vec_emcX.clear();
    vec_emcY.clear();

    //loop over all the vectors in the tree.

    for (Int_t i = 0; i < iev; i++) {
	    Int_t count = 0;
    	Int_t count1 = 0;

        tree->GetEntry(i);
        cout << endl
             << endl
             << endl;
        cout << "entry no. " << i << endl;
        Int_t oiv = vec_driftTime->size();
        cout << "vecsize  :" << oiv << endl;

        if (vec_driftTime->size() > 8) {
            cout << "SIZE GREATER THAN 8" << endl;
        }

        //vector<SttHit*> vec_hits;
        vec_hits.clear();
        vec_hits_new.clear();
        vec_dr_xaxis[0].clear();
        vec_dr_xaxis[1].clear();
        vec_dr_yaxis[0].clear();
        vec_dr_yaxis[1].clear();

        Int_t oc_count = 0;

        char buff[200];
        sprintf(buff, "can_%d", i);
        TCanvas* c1 = new TCanvas(buff);
        sprintf(buff, "h_%d", i);
        int x_min = -10;
        int x_max = 90;
        int x_bins = (x_max - x_min) * 5;
        int z_min = -10;
        int z_max = 80;
        int z_bins = (z_max - z_min) * 5;

        TH2I* h = new TH2I(buff, "h;x,y [cm];z [cm]", x_bins, x_min, x_max, z_bins, z_min, z_max);
        c1->cd();
        h->Draw();
      
        //Loop over the vector elements//////////////////////////////////////////////////////
        for (int n = 0; n < oiv; n++) {
            SttHit* a = new SttHit();
            cout<<"CHANNEL : "<<vec_tdc_ch->at(n)<<endl;
            
            for (Int_t aj=0; aj<16; aj++)
            {

                Int_t FrontEnd = ((4*(vec_layer->at(n) - 1))+(2*(vec_module->at(n))-1)+(vec_fee->at(n)-1));

                if (FrontEnd == 1)
                {
                    a->DriftRadius = fee_drift_0->Eval(vec_driftTime->at(n)-(dr_correction->Eval(1)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(1));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);

                 }
                else if (FrontEnd == 2)
                {
                    a->DriftRadius = fee_drift_1->Eval(vec_driftTime->at(n)-(dr_correction->Eval(2)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(2));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 3)
                {
                    a->DriftRadius = fee_drift_2->Eval(vec_driftTime->at(n)-(dr_correction->Eval(3)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(3));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 4)
                {
                    a->DriftRadius = fee_drift_3->Eval(vec_driftTime->at(n)-(dr_correction->Eval(4)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(4));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 5)
                {
                    a->DriftRadius = fee_drift_4->Eval(vec_driftTime->at(n)-(dr_correction->Eval(5)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(5));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 6)
                {
                    a->DriftRadius = fee_drift_5->Eval(vec_driftTime->at(n)-(dr_correction->Eval(6)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(6));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 7)
                {
                    a->DriftRadius = fee_drift_6->Eval(vec_driftTime->at(n)-(dr_correction->Eval(7)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(7));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 8)
                {
                    a->DriftRadius = fee_drift_7->Eval(vec_driftTime->at(n)-(dr_correction->Eval(8)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(8));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 9)
                {
                    a->DriftRadius = fee_drift_8->Eval(vec_driftTime->at(n)-(dr_correction->Eval(9)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(9));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 10)
                {
                    a->DriftRadius = fee_drift_9->Eval(vec_driftTime->at(n)-(dr_correction->Eval(10)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(10));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 11)
                {
                    a->DriftRadius = fee_drift_10->Eval(vec_driftTime->at(n)-(dr_correction->Eval(11)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(11));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 12)
                {
                    a->DriftRadius = fee_drift_11->Eval(vec_driftTime->at(n)-(dr_correction->Eval(12)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(12));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 13)
                {
                    a->DriftRadius = fee_drift_12->Eval(vec_driftTime->at(n)-(dr_correction->Eval(13)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(13));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 14)
                {
                    a->DriftRadius = fee_drift_13->Eval(vec_driftTime->at(n)-(dr_correction->Eval(14)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(14));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 15)
                {
                    a->DriftRadius = fee_drift_14->Eval(vec_driftTime->at(n)-(dr_correction->Eval(15)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(15));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }
                else if (FrontEnd == 16)
                {
                    a->DriftRadius = fee_drift_15->Eval(vec_driftTime->at(n)-(dr_correction->Eval(16)));
                    a->drifttime = vec_driftTime->at(n)-(dr_correction->Eval(16));
                    h_Straw_DriftTime->Fill(vec_tdc_ch->at(n),a->drifttime);
                    h_Fee_DriftTime->Fill(FrontEnd,a->drifttime);
                 }

            }
          
            a->x = vec_x->at(n);
            a->y = vec_y->at(n);
            a->z = vec_z->at(n);
            a->layer = vec_layer->at(n);
            a->module = vec_module->at(n);
            a->fee = vec_fee->at(n);
            a->fee_channel = vec_fee_ch->at(n);
            a->channel = vec_tdc_ch->at(n);
            vec_hits.push_back(a);
            vec_All_Hits.push_back(a);


            float uuu = 0.0;
            bool is_y = (a->layer % 2 == 0);
            if (is_y)
                uuu = a->y;
            else
                uuu = a->x;

            straws = new TEllipse(uuu, vec_z->at(n), 0.505, 0.505);

            TMultiGraph* mg = new TMultiGraph();
            TMultiGraph* mg1 = new TMultiGraph();
            cout << "\t" << vec_hits.size() << "\t" << vec_hits[n]->drifttime << "\t" << vec_hits[n]->layer << "\t" << vec_hits[n]->module << "\t" << vec_hits[n]->fee << "\t" << vec_hits[n]->fee_channel << "\t" << vec_hits[n]->x << "\t" << vec_hits[n]->y << "\t" << vec_hits[n]->z << "\t" << endl;
            straws->Draw("same");
        }

        //Filter to get only the sets having unique Z values

        if (vec_hits.size() > 0) {
            for (Int_t u = 0; u < vec_hits.size() - 1; u++) {
                for (Int_t uu = u + 1; uu < vec_hits.size(); uu++) {
                    if (fabs(vec_hits[u]->z - vec_hits[uu]->z) < 0.5)
                        oc_count++;

                    //cout<<vec_hits[u]->z<<"\t"<<vec_hits[uu]->z<<endl;
                }
            }
            //cout<<oc_count<<endl;

            TGraph* xfit;
            TGraph* xfit1;
            TGraph* yfit;
            TGraph* yfit1;

            Double_t strawX[8];
            Double_t strawY[8];
            Double_t strawZ[8];
            std::vector<double> vec_strawX;
    		std::vector<double> vec_strawY;
            std::vector<double> vec_strawZx;
    		std::vector<double> vec_strawZy;

            Z_value->Fill(3);

            //Take only the events having unique Z coordinate

            if (oc_count >= 0) {
                cout << "oc_count :";
                //cout<<oc_count<<"\t"<<vec_hits.size()<<endl;
                vec_hits_new = vec_hits;
                //cout<<vec_hits_new.size()<<endl;;
                Z_value->Fill(1);
            }

            else {

                Z_value->Fill(2);

                continue;
            }

            ///////////////////////////////////////////////////////////////////

            // Draw an ellipse on the straw position
            vec_strawX.clear();
            vec_strawY.clear();
            vec_strawZx.clear();
            vec_strawZy.clear();
            for (Int_t j = 0; j < vec_hits_new.size(); j++) 
            {
                float uuu = 0.0;
                bool is_y = (vec_hits_new[j]->layer % 2 == 0);
                if (is_y)
                    uuu = vec_hits_new[j]->y;
                else
                    uuu = vec_hits_new[j]->x;
                straws2 = new TEllipse(uuu, vec_hits_new[j]->z, 0.505, 0.505);
                if (is_y)
                    straws2->SetFillColor(46);
                else
                    straws2->SetFillColor(38);
                straws2->SetFillStyle(1001);
                straws2->SetLineColor(1);
                straws2->SetLineWidth(1);
                straws2->Draw("same");

                // Get the drift radius for the corresponding drift time for the hits having x-coordinates

                if (vec_hits_new[j]->layer == 1 || vec_hits_new[j]->layer == 3) {

                    Double_t dr1 = vec_hits_new[j]->DriftRadius;
                    SttHit* new_x1 = new SttHit();
                    SttHit* new_x2 = new SttHit();

                    vec_driftradius.push_back(dr1);

                    new_x1->x = vec_hits_new[j]->x + dr1;
                    new_x1->y = vec_hits_new[j]->y;
                    new_x1->z = vec_hits_new[j]->z;
                    new_x1->layer = vec_hits_new[j]->layer;
                    new_x1->module = vec_hits_new[j]->module;
                    new_x1->fee = vec_hits_new[j]->fee;
                    new_x1->fee_channel = vec_hits_new[j]->fee_channel;

                    vec_strawX.push_back(vec_hits_new[j]->x);
                    vec_strawZx.push_back(vec_hits_new[j]->z);

                    new_x2->x = vec_hits_new[j]->x - dr1;
                    new_x2->y = vec_hits_new[j]->y;
                    new_x2->z = vec_hits_new[j]->z;
                    new_x2->layer = vec_hits_new[j]->layer;
                    new_x2->module = vec_hits_new[j]->module;
                    new_x2->fee = vec_hits_new[j]->fee;
                    new_x2->fee_channel = vec_hits_new[j]->fee_channel;

                    vec_dr_xaxis[0].push_back(new_x1);
                    vec_dr_xaxis[1].push_back(new_x2);
                    count++;
                }

                // Get the drift radius for the corresponding drift time for the hits having y-coordinates

                if (vec_hits_new[j]->layer == 2 || vec_hits_new[j]->layer == 4) {
                   
                    Double_t dr2 = vec_hits_new[j]->DriftRadius;

                    SttHit* new_y1 = new SttHit();
                    SttHit* new_y2 = new SttHit();

                    new_y1->y = vec_hits_new[j]->y + dr2;
                    new_y1->z = vec_hits_new[j]->z;
                    new_y1->x = vec_hits_new[j]->x;
                    new_y1->layer = vec_hits_new[j]->layer;
                    new_y1->module = vec_hits_new[j]->module;
                    new_y1->fee = vec_hits_new[j]->fee;
                    new_y1->fee_channel = vec_hits_new[j]->fee_channel;

                    vec_strawY.push_back(vec_hits_new[j]->y);
                    vec_strawZy.push_back(vec_hits_new[j]->z);

                    new_y2->y = vec_hits_new[j]->y - dr2;
                    new_y2->z = vec_hits_new[j]->z;
                    new_y2->x = vec_hits_new[j]->x;
                    new_y2->layer = vec_hits_new[j]->layer;
                    new_y2->module = vec_hits_new[j]->module;
                    new_y2->fee = vec_hits_new[j]->fee;
                    new_y2->fee_channel = vec_hits_new[j]->fee_channel;

                    vec_dr_yaxis[0].push_back(new_y1);
                    vec_dr_yaxis[1].push_back(new_y2);

                    yperfectmean[j] = dr2;
                    count1++;
                }

            }

            Int_t e_index = 0;
            std::vector<Double_t> chiX_array;
            Double_t chi_value;

            vector<vector<Double_t> > myCombination;
            myCombination.clear();


            Double_t dSlope0 =0; 
            Double_t dConst0 =0;
            Double_t X_perpX = 0;
            Double_t X_perpY = 0;
            Double_t X_short = 0;

            int no_comb_x = pow(2, count);
            chiX_array.resize(no_comb_x);
            for (Int_t co = 0; co < no_comb_x; co++) {

                vector<Double_t> vt;
                vt.clear();

                for (Int_t coo = 0; coo < count; coo++) {
                	int bit_idx = (1 << coo);
                	int comb_idx = (co & bit_idx) ? 1 : 0;

                    A1[coo] = vec_dr_xaxis[comb_idx][coo]->x;
                    A2[coo] = vec_dr_xaxis[comb_idx][coo]->z;
                    vt.push_back(vec_dr_xaxis[comb_idx][coo]->x);
                }

            myCombination.push_back(vt);
            cout << "\n";
			cout<<"\n"<<endl;
			
                TGraph* chiX = new TGraph(vt.size(), A1, A2);
                chiX->Fit(f3);
                chi_value = f3->GetChisquare();
                //	cout<<"\n\n@#$@#$@#$@#$@#$"<<chi_value<<endl;

                chiX_array[co] = chi_value;
            }

            //Get the index of the combination having the least chisquare.
            Double_t smallest = chiX_array[0];

            Int_t chi_index = 0;
            for (Int_t ci = 0; ci < no_comb_x; ci++) {
                cout << "chiSquare  :" << chiX_array[ci] << endl;

                if (smallest > chiX_array[ci]) {
                    smallest = chiX_array[ci];
                    chi_index = ci;
                }
            }

            Double_t Ex[50];

            cout << "\n\n"
                 << "BEST COMBINATION  :";
            for (Int_t gdd = 0; gdd < count; gdd++) {
                cout << "\t " << myCombination.at(chi_index).at(gdd) << " ";
                Ex[gdd]=myCombination.at(chi_index).at(gdd);
            }
            cout << "\n\n\n" << endl;

            cout << "\n SMALLEST ChiSquar  :" << smallest << "(" << chi_index << ")" << endl;

            for (Int_t coo = 0; coo < count; coo++) {
             	int bit_idx = (1 << coo);
               	int comb_idx = (chi_index & bit_idx) ? 1 : 0;

                A1[coo] = vec_dr_xaxis[comb_idx][coo]->x;
                A2[coo] = vec_dr_xaxis[comb_idx][coo]->z;
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            for (Int_t cdf = 0; cdf < vec_hits_new.size(); cdf++) {
                cout << "  XX  :" << strawX[cdf] << "  ZZ  :" << strawZ[cdf] << endl;
            }


            //Plot X vs Z coordinate and fit the points

            if (vec_dr_xaxis[0].size() != 0) {

                xfit = new TGraph(count, Ex, A2);
                xfit1 = new TGraph(vec_hits_new.size(), strawX, strawZ);

                xfit->GetXaxis()->SetLimits(x_min, x_max);
                xfit->GetYaxis()->SetLimits(z_min, z_max);
                xfit->GetXaxis()->SetTitle("X Axix [cm]");
                xfit->GetYaxis()->SetTitle("Z Axix [cm]");
                xfit->SetTitle("X-Coordinates");
                xfit->SetMarkerStyle(7);
                xfit->SetMarkerSize(1);
                xfit->SetMarkerColor(kRed + 2);
                xfit->SetLineColor(0);
                xfit->SetLineWidth(2);
                xfit1->SetLineColor(0);
                xfit1->SetMarkerStyle(24);
                xfit1->SetMarkerSize(2);
                xfit1->SetMarkerColor(kRed + 2);
                xfit->Fit(f1);

                f1 = xfit->GetFunction("f1");
                Double_t p0 = f1->GetParameter(0);
                Double_t p1 = f1->GetParameter(1);
                theta_X = atan (1/p1);
                cout<< " THETA X  : "<< theta_X <<endl;
        		for (Int_t af=40; af<100; af++)
                {
                    h_projectionX->Fill(((af - p0) / p1),af);
                }

                h_theeta_X->Fill(theta_X);

                for (Int_t k = 0; k < count; k++) {

                    xperfect3[k] = (A2[k] - p0) / p1;
                    cout << "SPACE X  :" << fabs(A1[k] - xperfect3[k]) << endl;
                    dSlope0 = -(1/p1);
                    dConst0 = vec_strawZx[k]+(vec_strawX[k]/p1);
                    X_perpX = (dConst0 - p0) / (p1 + (1/p1));
                    X_perpY = (dSlope0 * X_perpX) + dConst0;
                    X_short = (fabs(sqrt(((vec_strawX[k] - X_perpX) * (vec_strawX[k] - X_perpX)) + ((vec_strawZx[k] - X_perpY) * (vec_strawZx[k] - X_perpY)) ))) - (fabs(vec_strawX[k] - A1[k]));
                    hx -> Fill(X_short);
                    vec_Xtheta.push_back(theta_X);
                    vec_Xsr.push_back(X_short);
                }
                cout << "\n\n" << endl;
            }

            ///////////////////////////////////////////////////////////////////////////////////
            //COMBINATIONS to get least Y ChiSquar2############################################

            Int_t e_index1 = 0;
            std::vector<Double_t> chiY_array;
            Double_t chi_value1;

            Double_t dSlope =0; 
            Double_t dConst =0;
            Double_t Y_perpX = 0;
            Double_t Y_perpY = 0;
            Double_t Y_short = 0;

            vector<vector<Double_t> > myCombination1;
            myCombination1.clear();

            int no_comb_y = pow(2, count1);
            chiY_array.resize(no_comb_y);
            for (Int_t co = 0; co < no_comb_y; co++) {
                
                vector<Double_t> vt1;
                vt1.clear();

                for (Int_t coo = 0; coo < count1; coo++) {
                	int bit_idx = (1 << coo);
                	int comb_idx = (co & bit_idx) ? 1 : 0;

                    B1[coo] = vec_dr_yaxis[comb_idx][coo]->y;
                    B2[coo] = vec_dr_yaxis[comb_idx][coo]->z;
                    vt1.push_back(vec_dr_yaxis[comb_idx][coo]->y);
                }

                myCombination1.push_back(vt1);
                cout << "\n";

                cout << "size1 B1 :" << (sizeof(B1)) / 8 << endl;
                cout << "size2 B2:" << (sizeof(B2)) / 8 << endl;
                for (Int_t coooq = 0; coooq < total_pairs; coooq++) {
                    cout << "\t\t" << B1[coooq] << "\t";
                }
                cout << "\n" << endl;

                TGraph* chiY = new TGraph(vt1.size(), B1, B2);
                chiY->Fit(f4);
                chi_value1 = f4->GetChisquare();
                chiY_array[co] = chi_value1;
            }

            Double_t smallest1 = chiY_array[0];

			Int_t chi_index1 = 0;
            for (Int_t ciq = 0; ciq < no_comb_y; ciq++) {
                cout << "chiSquareY  :" << chiY_array[ciq] << endl;

                if (smallest1 > chiY_array[ciq]) {
                    smallest1 = chiY_array[ciq];
                    chi_index1 = ciq;
                }
            }

            Double_t Why[50];

            cout << "\n\n"
                 << "BEST COMBINATION 2 :";
            for (Int_t gddq = 0; gddq < count1; gddq++) {
                cout << "\t " << myCombination1.at(chi_index1).at(gddq) << " ";
                Why[gddq]=myCombination1.at(chi_index1).at(gddq);
            }
            cout << "\n\n\n" << endl;

            cout << "\n SMALLEST ChiSquar 2 :" << smallest1 << "(" << chi_index1 << ")" << endl;

           for (Int_t coo = 0; coo < count1; coo++) {
             	int bit_idx = (1 << coo);
               	int comb_idx = (chi_index & bit_idx) ? 1 : 0;

                B1[coo] = vec_dr_yaxis[comb_idx][coo]->y;
                B2[coo] = vec_dr_yaxis[comb_idx][coo]->z;
            }

            if (vec_dr_yaxis.size() != 0) {

                yfit = new TGraph(count1, Why, B2);
                yfit1 = new TGraph(vec_hits_new.size(), strawY, strawZ);
                yfit->GetXaxis()->SetTitle("Y Axix [cm]");
                yfit->GetYaxis()->SetTitle("Z Axix [cm]");
                yfit->SetTitle("Y-Coordinates");
                yfit->SetMarkerStyle(7);
                yfit->SetMarkerSize(2);
                yfit->SetMarkerColor(kBlue + 2);
                yfit->SetLineColor(0);
                yfit->SetLineWidth(2);
                yfit1->SetMarkerStyle(24);
                yfit1->SetMarkerSize(2);
                yfit1->SetMarkerColor(kBlue + 2);
                yfit1->SetLineColor(0);
                yfit->Fit(f2);

                f2 = yfit->GetFunction("f2");
                Double_t pp0 = f2->GetParameter(0);
                Double_t pp1 = f2->GetParameter(1);
                theta_Y = atan (1/pp1);
                cout<< " THETA Y  : "<< theta_Y <<endl;
                
                for (Int_t bf=40; bf<100; bf++)
                {
                    h_projectionY->Fill(((bf - pp0) / pp1),bf);
                 }

	            h_theeta_Y->Fill(theta_Y);
                for (Int_t kk = 0; kk < count1; kk++) {

                    yperfect3[kk] = (B2[kk] - pp0) / pp1;
                    cout << "SPACE Y  :" << fabs(B1[kk] - yperfect3[kk]) << endl;
                    dSlope = -(1/pp1);
                    dConst = vec_strawZy[kk]+(vec_strawY[kk]/pp1);
                    Y_perpX = (dConst - pp0) / (pp1 + (1/pp1));
                    Y_perpY = (dSlope * Y_perpX) + dConst;
                    Y_short = (fabs(sqrt(((vec_strawY[kk] - Y_perpX) * (vec_strawY[kk] - Y_perpX)) + ((vec_strawZy[kk] - Y_perpY) * (vec_strawZy[kk] - Y_perpY)) ))) - (fabs(vec_strawY[kk] - B1[kk]));

                    hy -> Fill(Y_short);


                    cout << "Y Real Check  :  " << vec_strawY[kk] << "\t" << vec_strawZy[kk] <<"\t" << Y_perpX <<"\t" <<Y_perpY<<"\t PERP : "<<Y_short << endl;
                }
            }

            xfit->Draw("same,P");
            xfit->Write("X");
            yfit->Draw("same,P");
            yfit->Write("Y");

        }

        c1->Write();
        c1->Close();
    }


std::vector< vector<Double_t> > vec_Fee_drift_time;

for (Int_t ao=1; ao< 17; ao++)
{
     std::vector<Double_t>vec_inFee_drift_time;
     vec_inFee_drift_time.clear();

    for (Int_t ae=0; ae< vec_All_Hits.size(); ae++)
    {
        Int_t FeNo =  ((4*(vec_All_Hits[ae]->layer - 1))+(2*(vec_All_Hits[ae]->module)-1)+((vec_All_Hits[ae]->fee)-1));
        if (FeNo == ao)
        {
            vec_inFee_drift_time.push_back(vec_All_Hits[ae]->drifttime);

         }

     }

     vec_Fee_drift_time.push_back(vec_inFee_drift_time);
}

for (Int_t ij=0; ij<vec_Fee_drift_time.size(); ij++)
        {

            Double_t min_DT = vec_Fee_drift_time.at(ij).at(0);
            for (Int_t rr = 0; rr < vec_Fee_drift_time.at(ij).size(); rr++)
            {
                if (vec_Fee_drift_time.at(ij).at(rr) < min_DT)
                    min_DT=vec_Fee_drift_time.at(ij).at(rr);
            }
            cout<<"Minimum : "<<"\t"<<vec_Fee_drift_time.size()<<"\t"<<ij<<"\t"<<vec_Fee_drift_time.at(ij).size()<<"\t"<<min_DT<<endl;
        }

    Double_t emcX_arry[100000];
    Double_t emcY_arry[100000];

    cout << "all driftradius   :" << vec_driftradius.size() << endl;
    cout << "\n\n\n SIZES   :   " << vec_emcX.size()<< "  -  "<< vec_emcX.size()<<endl;

    emc = new TGraph(vec_emcX.size(), emcX_arry, emcY_arry);
	emc->SetMarkerStyle(3);
	emc->SetMarkerSize(1);
	emc->SetMarkerColor(2);
	emc->SetLineColor(0);
    hx->Write();
    hy->Write();
    h_theeta_X->Write();
    h_theeta_Y->Write();
    h_projectionX->Write();
    h_projectionY->Write();

    cout <<"THETA SIZE : "<<vec_Xsr.size()<<"  "<<vec_Xtheta.size()<<endl;

    Double_t arr_Xt[500];
    Double_t arr_Xsr[500];

    for (tt =0; tt< 500; tt++)
    {
    arr_Xt[tt]=vec_Xtheta[tt];
    arr_Xsr[tt]=vec_Xsr[tt];
    }
    theta_SR = new TGraph(500, arr_Xt, arr_Xsr);
   
    theta_SR->Draw();
    theta_SR->Write();
    Z_value->Write();
    emc->Draw();
    emc->Write();
    h_Straw_DriftTime->Write();
    h_Fee_DriftTime->Write();

    //emc->Write();
    //DR->Draw();
    //cout<<"count in Layer1+layer3 : "<< count<<"\t"<<"count in Layer2+layer4 : "<<"\t"<<count1<<"\t"<<"TOTAL : "<<count+count1<<endl;
    return;
}
