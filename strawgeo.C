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
#include <TEllipse.h>

#include "TRandom.h"
#include "SttHit.h"
#include "SttEvent.h"

using namespace std;


Bool_t strawgeo(void)
{

	TFile file("Drift_Radius.root", "READ"); 
	TTree* tree =(TTree*)file.Get("DR_Tree");


    TFile* driftfile1 = new TFile("Straws.root", "RECREATE");


	std::vector<double> *Vec_o_test;
	std::vector<double> *vec_x;
	std::vector<double> *vec_y;
	std::vector<double> *vec_z;
	std::vector<double> *vec_layer;
	std::vector<double> *vec_module;
	std::vector<double> *vec_fee;
	std::vector<double> *vec_fee_ch;
	std::vector<double> *vec_tdc_ch;
	std::vector<SttHit*> vec_dr_xaxis;
	std::vector<SttHit*> vec_dr_yaxis;
	std::vector<double> vec_driftradius;


	tree->SetBranchAddress("Vec_o_test", &Vec_o_test);
	tree->SetBranchAddress("vec_x", &vec_x);
	tree->SetBranchAddress("vec_y", &vec_y);
	tree->SetBranchAddress("vec_z", &vec_z);
	tree->SetBranchAddress("vec_layer", &vec_layer);
	tree->SetBranchAddress("vec_module", &vec_module);
	tree->SetBranchAddress("vec_fee", &vec_fee);
	tree->SetBranchAddress("vec_fee_ch", &vec_fee_ch);
	tree->SetBranchAddress("vec_tdc_ch", &vec_tdc_ch);

	TEllipse * straws;

	Int_t iev =(Int_t) tree->GetEntries();
	cout<<"number of entries in tree:"<<iev<<endl<<endl;

Int_t count =0;
Int_t count1 =0;
vector<SttHit*> vec_hits;
vector<SttHit*> vec_hits_new;




//Loop over all vectors

	for (Int_t i=0; i<iev; i++)
	{
		tree->GetEntry(i);
		cout<<endl<<endl<<endl;
		cout<<"entry no. "<<i<<endl;
		Int_t oiv= Vec_o_test->size();
		cout<< "vecsize  :"<<oiv<<endl;		

		vec_hits.clear();
		vec_hits_new.clear();
		vec_dr_xaxis.clear();
		vec_dr_yaxis.clear();
		Int_t oc_count =0;

   TCanvas *c1 = new TCanvas("cow");
   c1->Range(0,0,100,100);


//Loop over vectors

		for(int n=0; n< oiv;n++)
		{
			SttHit* a = new SttHit();

			a->drifttime = Vec_o_test->at(n);
			a->x = vec_x->at(n);
			a->y = vec_y->at(n);
			a->z = vec_z->at(n);
			a->layer = vec_layer->at(n);
			a->module = vec_module->at(n);
			a->fee = vec_fee->at(n);
			a->fee_channel = vec_fee_ch->at(n);
			a->channel = vec_tdc_ch->at(n);
			vec_hits.push_back(a);	

   		straws = new TEllipse(vec_x->at(n), vec_z->at(n), 0.505, 0.505);


		straws->Draw();

		}

		
		c1->Write();
	}



	return; 
}

