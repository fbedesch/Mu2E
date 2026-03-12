#include <TROOT.h>

void LoadAll()
{
gROOT->Reset();
//gROOT->ProcessLine(".I ");
gROOT->ProcessLine(".L code/classes/Mu2Edata.cc+");
gROOT->ProcessLine(".L code/SimplePlot.C+");
gROOT->ProcessLine(".L code/WavePlot.C+");
gROOT->ProcessLine(".L code/WaveFit.C+");
}
