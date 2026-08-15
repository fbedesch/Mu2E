#include <TString.h>
#include <iostream>
#include "classes/Mu2Edata.h"


void WaveToRoot(TString fName, TString fOutPut, Int_t Opt)
{
    //
    // fName is input root file
    // fOutPut is output root file with fit results
    // Opt = 0 Binary (default)
    // Opt = 1 ART
    //
    //
    // Open data  file and configure data access
    Mu2Edata data(fName, Opt);
    //
    // write file with fit results
    //
    data.MakeFitROOT(fOutPut);
}
