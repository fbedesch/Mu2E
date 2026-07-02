
#include "classes/LaserConf.h"

void LaserView(TString fName)
{
    //
    // View basic features of all photodiodes in the laser system
    //
    LaserConf LC(fName);
    //
    Int_t Opt = 1;  // Assume ART format
    LC.FillHist(Opt);
    std::cout<<"LaserView: Histograms filled"<<std::endl;
    LC.PrintHist();

}
