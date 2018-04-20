{

gSystem->Load("libGraf");
printf("Loading libraries\n"); 

gROOT->ProcessLine(".L SttHit.cpp+");
gROOT->ProcessLine(".L SttEvent.cpp+");
gROOT->ProcessLine(".L SttDetector.cpp+");


gStyle->SetPalette(1);
gStyle->SetOptFit(1111);
}
