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

	TFile file("Drift_Radius.root", "READ"); 
	TTree* tree =(TTree*)file.Get("DR_Tree");

   f1 = new TF1("f1","pol1");
   f2 = new TF1("f2","pol1");
   f3 = new TF1("f3","pol1");
   f4 = new TF1("f4","pol1");


    TFile* driftfile1 = new TFile("XYZ_Coordinates.root", "RECREATE");
    //TFile* driftfile2 = new TFile("Y_Coordinates.root", "RECREATE");

    TH1F* hx = new TH1F("hx","dummy_resolutionX",400,0,4);
    TH1F* hy = new TH1F("hy","dummy_resolutionY",400,0,4);
    TH1F* DR = new TH1F("hy","drift_radius",350,0,350);

    TH1F* Z_value = new TH1F("Z_value","dummy",5,0,5);


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



    Double_t a1[230];
    Double_t b1[230];

    Double_t zaxis[16];

    Double_t A1[4];
    Double_t A2[4];

    Double_t B1[4];
    Double_t B2[4];


    Int_t array_length = 8;
    Int_t pair_length =2;
    Int_t total_pairs = (array_length/pair_length);
    Int_t no_of_pairs = (total_pairs*total_pairs);


	tree->SetBranchAddress("Vec_o_test", &Vec_o_test);
	tree->SetBranchAddress("vec_x", &vec_x);
	tree->SetBranchAddress("vec_y", &vec_y);
	tree->SetBranchAddress("vec_z", &vec_z);
	tree->SetBranchAddress("vec_layer", &vec_layer);
	tree->SetBranchAddress("vec_module", &vec_module);
	tree->SetBranchAddress("vec_fee", &vec_fee);
	tree->SetBranchAddress("vec_fee_ch", &vec_fee_ch);
	tree->SetBranchAddress("vec_tdc_ch", &vec_tdc_ch);


TGraph* gDR = new TGraph(220, a1,b1);
gDR = (TGraph*)file.Get("PDAQ_DR");

Double_t xperfect1[16];
Double_t xperfect2[16];
Double_t xperfect3[16];
//Double_t strawX[8];


Double_t yperfect1[16];
Double_t yperfect2[16];
Double_t yperfect3[16];

//Double_t strawY[8];
//Double_t strawZ[8];


Double_t yperfectmean[16];

SttHit* new_y1=0;
SttHit* new_y2=0;


	Int_t iev =(Int_t) tree->GetEntries();
	cout<<"number of entries in tree:"<<iev<<endl<<endl;

Int_t count =0;
Int_t count1 =0;
vector<SttHit*> vec_hits;
vector<SttHit*> vec_hits_new;
vec_driftradius.clear();


//loop over all the vectors in the tree.

	for (Int_t i=0; i<iev; i++)
	{
		tree->GetEntry(i);
		cout<<endl<<endl<<endl;
		cout<<"entry no. "<<i<<endl;
		Int_t oiv= Vec_o_test->size();
		cout<< "vecsize  :"<<oiv<<endl;

		if (Vec_o_test->size()>8)
		{
			cout<<"SIZE GREATER THAN 8"<<endl;
		}			

		//vector<SttHit*> vec_hits;
		vec_hits.clear();
		vec_hits_new.clear();
		vec_dr_xaxis.clear();
		vec_dr_yaxis.clear();

		Int_t oc_count =0;

		char buff[200];
		sprintf(buff, "can_%d", i);
		TCanvas *c1 = new TCanvas(buff);
		sprintf(buff, "h_%d", i);
		TH2I* h = new TH2I(buff, "h;x [mm];z [mm]", 700, -10, 60, 700, -10, 60);
		c1->cd();
		h->Draw();
// 		c1->Range(-10,-10,60,60);

			//cout<<"hello 1:"<<endl;

//Loop over the vector elements

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

			TMultiGraph *mg = new TMultiGraph();
			TMultiGraph *mg1 = new TMultiGraph();

//cout<<"see :"<<a->drifttime<<"\t"<<a->layer<<"\t"<<a->module<<"\t"<<a->fee<<"\t"<<a->fee_channel<<"\t"<<a->x<<"\t"<<a->y<<"\t"<<a->z<<endl;
/////////

		cout<<"\t"<<vec_hits.size()<<"\t"<<vec_hits[n]->drifttime<<"\t"<<vec_hits[n]->layer<<"\t"<<vec_hits[n]->module<<"\t"<<vec_hits[n]->fee<<"\t"<<vec_hits[n]->fee_channel<<"\t"<<vec_hits[n]->x<<"\t"<<vec_hits[n]->y<<"\t"<<vec_hits[n]->z<<"\t"<<endl;		
			straws->Draw("same");

		}


//Filter to get only the sets having unique Z values		

if (vec_hits.size() >0)
{
		for (Int_t u=0; u<vec_hits.size() - 1; u++)
		{
			for (Int_t uu=u+1; uu<vec_hits.size(); uu++)
			{
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

		Z_value->Fill(3);

//Take only the events having unique Z coordinate

		if (oc_count >=0 )
		{
			cout<<"oc_count :";
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

		for (Int_t j = 0; j< vec_hits_new.size(); j++)
		{

			//cout<<"THIS IS Z :"<<vec_hits_new[j]->z<<endl;
			strawX[j]=vec_hits_new[j]->x;
			strawY[j]=vec_hits_new[j]->y;
			strawZ[j]=vec_hits_new[j]->z;

			straws2 = new TEllipse(vec_hits_new[j]->x, vec_hits_new[j]->z, 0.505, 0.505);
		   straws2->SetFillColor(7);
		   straws2->SetFillStyle(1001);
		   straws2->SetLineColor(6);
		   straws2->SetLineWidth(4);
			straws2->Draw("same");

// Get the drift radius for the corresponding drift time for the hits having x-coordinates

			if (vec_hits_new[j]->layer==1 || vec_hits_new[j]->layer==3)
			{

				Double_t dr1 = gDR->Eval(vec_hits_new[j]->drifttime);
				SttHit* new_x1 = new SttHit();
				SttHit* new_x2 = new SttHit();

				vec_driftradius.push_back(dr1);

				new_x1->x =vec_hits_new[j]->x+dr1;
				new_x1->y =vec_hits_new[j]->y;
				new_x1->z =vec_hits_new[j]->z; 
				new_x1->layer =vec_hits_new[j]->layer; 
				new_x1->module =vec_hits_new[j]->module; 
				new_x1->fee =vec_hits_new[j]->fee; 
				new_x1->fee_channel =vec_hits_new[j]->fee_channel; 
				
				new_x2->x=vec_hits_new[j]->x-dr1;
				new_x2->y =vec_hits_new[j]->y;
				new_x2->z = vec_hits_new[j]->z;
				new_x2->layer =vec_hits_new[j]->layer; 
				new_x2->module =vec_hits_new[j]->module; 
				new_x2->fee =vec_hits_new[j]->fee; 
				new_x2->fee_channel =vec_hits_new[j]->fee_channel; 				

				vec_dr_xaxis.push_back(new_x1);
				vec_dr_xaxis.push_back(new_x2);
				//zaxis[j]= vec_hits[j]->z;

				//cout<< "Xaxis :  "<<vec_hits[j]->layer<<"\t"<<vec_hits[j]->x<<"\t"<<vec_hits[j]->y<<"\t"<<vec_hits[j]->z<<"\t"<<vec_hits[j]->x<<"\t"<<dr1<<endl;
				count++;

			}

// Get the drift radius for the corresponding drift time for the hits having y-coordinates

			if (vec_hits_new[j]->layer==2 || vec_hits_new[j]->layer==4)
			{
				Double_t dr2 = gDR->Eval(vec_hits_new[j]->drifttime);

				SttHit* new_y1 = new SttHit();
				SttHit* new_y2 = new SttHit();

				new_y1->y =vec_hits_new[j]->y+dr2;
				new_y1->z =vec_hits_new[j]->z; 
				new_y1->x =vec_hits_new[j]->x;
				new_y1->layer =vec_hits_new[j]->layer; 
				new_y1->module =vec_hits_new[j]->module; 
				new_y1->fee =vec_hits_new[j]->fee; 
				new_y1->fee_channel =vec_hits_new[j]->fee_channel; 

				strawY[j]=vec_hits[j]->y;
				
				new_y2->y=vec_hits_new[j]->y-dr2;
				new_y2->z = vec_hits_new[j]->z;
				new_y2->x =vec_hits_new[j]->x;
				new_y2->layer =vec_hits_new[j]->layer; 
				new_y2->module =vec_hits_new[j]->module; 
				new_y2->fee =vec_hits_new[j]->fee; 
				new_y2->fee_channel =vec_hits_new[j]->fee_channel; 
	
				//SttHit* new_y1=vec_hits[j]->y+dr2;
				//SttHit* new_y2=vec_hits[j]->y-dr2;
				vec_dr_yaxis.push_back(new_y1);
				vec_dr_yaxis.push_back(new_y2);

				yperfectmean[j]=dr2;
				//zaxis[j]= vec_hits[j]->z;
				//cout <<"\t"<< "Yaxis :"<<vec_hits[j]->y<<vec_hits[j]->layer<<endl;
				//<<"\t"<<vec_hits[j]->layer<<"\t"<<dr2<<endl;

				count1++;

			}

		}		

//cout <<"here  :"<<oc_count<<" "<<vec_dr_xaxis.size()<<endl;

//Fill all the 16 drift radius (8straws * 2) in an array.

		for( Int_t ii=0; ii<vec_dr_xaxis.size();ii++)
		{

			xperfect1[ii]=vec_dr_xaxis[ii]->x;
			xperfect2[ii]=vec_dr_xaxis[ii]->z;	
			//cout<<"Radius size test  :"<<vec_dr_xaxis[ii]->x<<endl;	
		}

/////////////////////////////////////////FIND THE BEST COMBINATION//////////////////////////////////////////////////////

//COMBINATIONS to get least ChiSquar

		Int_t e_index =0;
		Double_t chiX_array[16];
		Double_t chi_value;


		vector<vector<Double_t> > myCombination;
		myCombination.clear();

		Int_t row = 16;
		Int_t col = 4;


		for(Int_t co=0;co<no_of_pairs;co++)
		{
			//cout<<e_index<<endl;
			//cout<<"{";

			vector<Double_t> vt;
			vt.clear();

	
			for(Int_t coo=0; coo<total_pairs;coo++)
			{
				e_index = (Int_t)(((Int_t)(floor(( co / (no_of_pairs/pow(2,coo+1))))) % 2) + (coo*pair_length));

				//cout<<"  "<<xperfect1[e_index]<<"("<<((int)(floor(( co / (no_of_pairs/pow(2,coo+1))))) % 2)<<")  ";

				A1[coo]=xperfect1[e_index];
				A2[coo]=xperfect2[e_index];

				//cout<<"   STRAW_LOC  @@@@@@@@@@@@@@@@&&&&&&&&&:"<<ex<<endl;

				vt.push_back(xperfect1[e_index]);

			}

			myCombination.push_back(vt);

			//cout<<"}";
			cout<<"\n";

//cout <<"size1 A1 :"<<(sizeof(A1))/8<<endl;
//cout <<"size2 A2:"<<(sizeof(A2))/8<<endl;
//cout <<"size3 xperfect2:"<<(sizeof(xperfect2))/8<<endl;

			/*for (Int_t cooo=0; cooo<total_pairs;cooo++)
			{
				cout<<"\t\t"<<A1[cooo]<<"\t";

			}
			cout<<"\n"<<endl;
			*/
				TGraph* chiX = new TGraph(vt.size(),A1,A2);
				chiX->Fit(f3);
				chi_value = f3->GetChisquare();
			//	cout<<"\n\n@#$@#$@#$@#$@#$"<<chi_value<<endl;

				chiX_array[co]=chi_value;
			
			
		}

	//Get the index of the combination having the least chisquare.
					Int_t chi_size = 16;
					Double_t smallest = chiX_array[0];


					for (Int_t ci=0; ci<=chi_size-1; ci++) 
			    	{
				    	cout<<"chiSquare  :"<<chiX_array[ci]<<endl;

				    	if (smallest>chiX_array[ci] )
				    	{
				    		smallest=chiX_array[ci];
				    		Int_t chi_index = ci;
				    	}
			    	
			    	}

			    cout<<"\n\n"<<"BEST COMBINATION  :";
				for (Int_t gdd =0; gdd<4; gdd++)
				{
					cout <<"\t "<< myCombination.at(chi_index).at(gdd) << " ";
				}
				cout<<"\n\n\n"<<endl;

    	cout<<"\n SMALLEST ChiSquar  :"<<smallest<<"("<<chi_index<<")"<<endl;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


for ( Int_t cdf=0; cdf< vec_hits_new.size(); cdf++)
{
	cout<<"  XX  :"<<strawX[cdf]<<"  ZZ  :"<<strawZ[cdf]<<endl;
}

cout <<"seeMYsize :"<<(sizeof(A2))/8<<endl;

//Plot X vs Z coordinate and fit the points

			if(vec_dr_xaxis.size()!=0)
			{

				xfit = new TGraph(vt.size(),A1,A2);
				xfit1 = new TGraph(vec_hits_new.size(),strawX,strawZ);


				xfit->GetXaxis()->SetLimits(10,50);

				xfit->GetXaxis()->SetTitle("X Axix [cm]");
				xfit->GetYaxis()->SetTitle("Z Axix [cm]");
				xfit->SetTitle("X-Coordinates");

				xfit->SetMarkerStyle(7);
				xfit->SetMarkerSize(1);
				xfit->SetMarkerColor(kBlue+2);
				xfit->SetLineColor(0);
				xfit->SetLineWidth(2);


				xfit1->SetLineColor(0);

				xfit1->SetMarkerStyle(24);
				xfit1->SetMarkerSize(2);
				xfit1->SetMarkerColor(kRed+2);
				//xfit1->SetLineColor(kRed-10);
				//xfit1->SetLineWidth(2);

				xfit->Fit(f1);
				
				 f1 = xfit->GetFunction("f1");
				 Double_t p0 = f1->GetParameter(0);
				 Double_t p1 = f1->GetParameter(1);

				for(Int_t k=0; k<vt.size();k++)
				{

					xperfect3[k]= (A2[k]-p0)/p1;	

					cout<<"SPACE X  :"<<fabs(A1[k]-xperfect3[k])<<endl;
					hx->Fill(fabs(A1[k]-xperfect3[k]));
				}
cout<<"\n\n"<<endl;
			}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Y - Coordinates@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
			//cout<<"display size :"<<vec_dr_yaxis.size();

		for( Int_t iii=0; iii<vec_dr_yaxis.size();iii++)

		{
			yperfect1[iii]=vec_dr_yaxis[iii]->y;
			yperfect2[iii]= vec_dr_yaxis[iii]->z;			
		}
			
///////////////////////////////////////////////////////////////////////////////////
//COMBINATIONS to get least Y ChiSquar2############################################

		Int_t e_index1 =0;
		Double_t chiY_array[16];
		Double_t chi_value1;


		vector<vector<Double_t> > myCombination1;
		myCombination1.clear();

		Int_t row1 = 16;
		Int_t col1 = 4;



		for(Int_t coq=0;coq<no_of_pairs;coq++)
		{
			//cout<<e_index<<endl;
			//cout<<"{";

			vector<Double_t> vt1;
			vt1.clear();

	
			for(Int_t cooq=0; cooq<total_pairs;cooq++)
			{
				e_index1 = (Int_t)(((Int_t)(floor(( coq / (no_of_pairs/pow(2,cooq+1))))) % 2) + (cooq*pair_length));

				//cout<<"  "<<xperfect1[e_index]<<"("<<((int)(floor(( co / (no_of_pairs/pow(2,coo+1))))) % 2)<<")  ";

				B1[cooq]=yperfect1[e_index1];
				B2[cooq]=yperfect2[e_index1];

				vt1.push_back(yperfect1[e_index1]);

			}

			myCombination1.push_back(vt1);

			//cout<<"}";
			cout<<"\n";

cout <<"size1 B1 :"<<(sizeof(B1))/8<<endl;
cout <<"size2 B2:"<<(sizeof(B2))/8<<endl;
cout <<"size3 yperfect2:"<<(sizeof(yperfect2))/8<<endl;

			for (Int_t coooq=0; coooq<total_pairs;coooq++)
			{
				cout<<"\t\t"<<B1[coooq]<<"\t";

			}
			cout<<"\n"<<endl;

				TGraph* chiY = new TGraph(vt1.size(),B1,B2);
				chiY->Fit(f4);
				chi_value1 = f4->GetChisquare();
			//	cout<<"\n\n@#$@#$@#$@#$@#$"<<chi_value<<endl;

				chiY_array[coq]=chi_value1;
			
			
		}

					Int_t chi_size1 = 16;
					Double_t smallest1 = chiY_array[0];


					for (Int_t ciq=0; ciq<=chi_size1-1; ciq++) 
			    	{
				    	cout<<"chiSquareY  :"<<chiY_array[ciq]<<endl;

				    	if (smallest1>chiY_array[ciq] )
				    	{
				    		smallest1=chiY_array[ciq];
				    		Int_t chi_index1 = ciq;
				    	}
			    	
			    	}

			    cout<<"\n\n"<<"BEST COMBINATION 2 :";
				for (Int_t gddq =0; gddq<4; gddq++)
				{
					cout <<"\t "<< myCombination1.at(chi_index1).at(gddq) << " ";
				}
				cout<<"\n\n\n"<<endl;

    	cout<<"\n SMALLEST ChiSquar 2 :"<<smallest1<<"("<<chi_index1<<")"<<endl;

			if(vec_dr_yaxis.size()!=0)
			{

				 yfit = new TGraph(vt1.size(),B1,B2);
				 yfit1 = new TGraph(vec_hits_new.size(),strawY,strawZ);

				yfit->GetXaxis()->SetLimits(40,100);


				//TGraph* yfit2 = new TGraph(vt1.size(),yperfectmean,yperfect2);

				yfit->GetXaxis()->SetTitle("Y Axix [cm]");
				yfit->GetYaxis()->SetTitle("Z Axix [cm]");
				yfit->SetTitle("Y-Coordinates");


				yfit->SetMarkerStyle(7);
				yfit->SetMarkerSize(2);
				yfit->SetMarkerColor(kRed+2);
				yfit->SetLineColor(0);
				yfit->SetLineWidth(2);

				yfit1->SetMarkerStyle(24);
				yfit1->SetMarkerSize(2);
				yfit1->SetMarkerColor(kBlue+2);
				yfit1->SetLineColor(0);
	

				yfit->Fit(f2);

				
				 f2 = yfit->GetFunction("f2");
				 Double_t pp0 = f2->GetParameter(0);
				 Double_t pp1 = f2->GetParameter(1);

				 //yfit->SetPoint(1, 10,10);

				for(Int_t kk=0; kk<vt1.size();kk++)
				{

					yperfect3[kk]= (yperfect2[kk]-pp0)/pp1;	
					cout<<"SPACE Y  :"<<fabs(B1[kk]-yperfect3[kk])<<endl;
					hy->Fill(fabs(B1[kk]-yperfect3[kk]));

					//cout<<yperfect3[kk]<<endl;
				}

			}

		//mg->Add(yfit);
		//mg->Add(yfit2);
		//xfit1->Draw("AP");
		//mg->Add(yfit);


		/*mg->Add(xfit);
		mg->Add(xfit1);
		mg->Write("X");
		mg1->Add(yfit);
		mg1->Add(yfit1);
		mg1->Write("Y");*/

		//yfit->Write("Y");
		xfit->Draw("same,P");
		xfit->Write("X");
		//yfit->Draw("AL*");

	}

			c1->Write();
			c1->Close();

}
cout<<"all driftradius   :"<<vec_driftradius.size()<<endl;

	Z_value->Write();
	hx->Write();
	hy->Write();
	//DR->Draw();
	//cout<<"count in Layer1+layer3 : "<< count<<"\t"<<"count in Layer2+layer4 : "<<"\t"<<count1<<"\t"<<"TOTAL : "<<count+count1<<endl;
	return; 
}