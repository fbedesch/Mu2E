
#include "classes/LaserConf.h"

void BundleView(TString fName)
{
    //
    // View basic features of all photodiodes in the laser system
    //
    Int_t Opt = 1;  // Assume ART format
    LaserConf LC(fName, Opt);
    //
    LC.FillBundHist();
    std::cout<<"BundleView: Histograms filled"<<std::endl;
    LC.PrintBundHist();

}
