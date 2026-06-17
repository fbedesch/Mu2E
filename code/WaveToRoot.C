#include <TString.h>
#include <iostream>
#include "classes/Mu2Edata.h"


void WaveToRoot(TString fName, TString fOutPut)
{
    //
    // fName is input root file
    // fOutPut is output root file with fit results
    //
    //
    // Open data  file and configure data access
    Mu2Edata data(fName);
    //
    // write file with fit results
    //
    data.MakeFitROOT(fOutPut);
}
