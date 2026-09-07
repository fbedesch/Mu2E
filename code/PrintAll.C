
#include "classes/LaserConf.h"

void PrintAll(TString fName)
{
    //
    // View basic features of all photodiodes in the laser system
    //
    Int_t Opt = 1;  // Assume ART format
    Mu2Edata *data = new Mu2Edata(fName, Opt);  // Access data file
    //
    // Start Laser processing
    LaserConf LC(data);
    LC.PrintMeans();
}
