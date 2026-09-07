
#include "classes/Mu2Edata.h"
#include "classes/LaserConf.h"

void BundleView(TString fName, Bool_t Prt = kFALSE)
{
    //
    // View basic features of all bundles in the laser system
    //
    Int_t Opt = 1;  // Assume ART format
    Mu2Edata *data = new Mu2Edata(fName, Opt);  // Access data file
    //
    // Start Laser processing
    LaserConf LC(data);
    //
    LC.FillBundHist();
    std::cout<<"BundleView: Histograms filled"<<std::endl;
    //
    LC.PrintBundHist(Prt);
}
