
#include "classes/LaserConf.h"

void BundleView(TString fName)
{
    //
    // View basic features of all photodiodes in the laser system
    //
    LaserConf LC(fName);
    //
    Int_t Opt = 1;  // Assume ART format
    LC.FillBundHist(Opt);
    std::cout<<"BundleView: Histograms filled"<<std::endl;
    LC.PrintBundHist();

}
