{

gSystem->Load("libGraf");
printf("Loading libraries\n"); 

gROOT->ProcessLine(".L SttRawHit.C+");
gROOT->ProcessLine(".L SttHit.cpp+");
gROOT->ProcessLine(".L SttEvent.cpp+");
gROOT->ProcessLine(".L Stt_Cal_Event.cpp+");

gROOT->ProcessLine(".L SttTrackHit.cpp+");
gROOT->ProcessLine(".L SttTrackEvent.cpp+");


gROOT->ProcessLine(".L SttDetector.cpp+");


gROOT->ProcessLine(".L EmcHit.C+");
gROOT->ProcessLine(".L EmcEvent.C+");

gROOT->ProcessLine(".L panda_subsystem.C+");
gROOT->ProcessLine(".L panda_subsystem_stt.C+");
gROOT->ProcessLine(".L panda_subsystem_sb.C+");
gROOT->ProcessLine(".L panda_subsystem_emc.C+");

gROOT->ProcessLine(".L EmcHit.C+");
gROOT->ProcessLine(".L EmcEvent.C+");

gROOT->ProcessLine(".L panda_stt_cal.C+");
gROOT->ProcessLine(".L panda_stt_track.C+");
gROOT->ProcessLine(".L panda_stt_driftradius.C+");


gStyle->SetPalette(1);
gStyle->SetOptFit(1111);
}
