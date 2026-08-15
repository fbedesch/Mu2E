
#include "classes/LaserConf.h"

void PrintAll(TString fName)
{
    //
    // View basic features of all photodiodes in the laser system
    //
    Int_t Opt = 1;  // Assume ART format
    LaserConf LC(fName, Opt);
    LC.PrintMeans();
}
