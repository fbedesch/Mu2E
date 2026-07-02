//
#ifndef G__LASERCONF_H
#define G__LASERCONF_H
//
// ROOT
#include <TString.h>
#include <TFile.h>
#include <TMath.h>
#include <TVectorD.h>
#include <TCanvas.h>
#include <TH1.h>
//
// STD
#include <iostream>
//
// Local
#include "code/classes/Mu2Edata.h"
//
//
//
class LaserConf
{
        //
        // Class to display state of pin diodes of laser system
        //
private:
        //
        // Inputs
        TString fName;
        //
        // Configuration data
        // Identification of pin diodes
        // Disk and phi = -2 for diodes on the optical table before the FW
        // Sphere   FW0 and pin selection 0/1      (FW00, FW01)
        // Disk and phi = -1 for diodes on the optical table after  the FW
        // Sphere   FW1 and pin selection 0/1      (FW10, FW11)
        static const Int_t fNdiode  = 20;    // Number of pin diodes in whole system
        static const Int_t fNsphere  = 10;    // Number of spheres in whole system
        // Disk on Nth diode
        Int_t fDisk[fNdiode] = {-2, -2, -1, -1,                 // Optical Board
                                 0, 0, 0, 0, 0, 0, 0, 0,        // Disk 0
                                 1, 1, 1, 1, 1, 1, 1, 1};       // Disk 1
        // Phi of Nth diode
        Int_t fPhi[fNdiode]  = {-2, -2, -1, -1,
                                 0, 0, 0, 0, 1, 1, 1, 1,
                                 0, 0 ,0, 0, 1, 1, 1, 1};
        // Board of Nth diode
        Int_t fBoard[fNdiode]= {160, 160, 160, 160,
                                  9, 10,  8, 11, 51, 48, 50, 49,
                                 89, 90, 88, 91,129,128,130,131} ;
        // Channel of Nth diode
        Int_t fChann[fNdiode]= {  4,   5,  16,  17,
                                 19, 19, 19, 19,  0,  0,  0,  0,
                                 19, 19, 19, 19,  0,  0,  0,  0};
        // Sphere of Nth diode (S or L)
        TString fSphere[fNdiode] = {"FW0", "FW0", "FW1", "FW1",
                                    "S", "S", "L", "L", "S", "S", "L", "L",
                                    "S", "S", "L", "L", "S", "S", "L", "L"};
        // SPhere top of bottom (TOP or BOT)
        TString fTopBot[fNdiode] = {"FW00", "FW01", "FW10", "FW11",
                                    "TOP", "BOT", "TOP", "BOT", "TOP", "BOT", "TOP", "BOT",
                                    "TOP", "BOT", "TOP", "BOT", "TOP", "BOT", "TOP", "BOT"};
        //
        // Channel descriptions
        //
        TString fDescr[fNdiode];
public:
        //
        // Constructors
        LaserConf();    // Just load configuration
        LaserConf(TString Input_File);  // Prepare also histograms
        void InitConf();
        // Destructor
        ~LaserConf();
        //
        //
        // Accessors
        Int_t GetNdiodes(){ return fNdiode; };  // Nr. of diodes
        Int_t GetDisk (Int_t nD){ return fDisk [nD]; }; // Disk
        Int_t GetPhi  (Int_t nD){ return fPhi  [nD]; }; // Phi
        Int_t GetBoard(Int_t nD){ return fBoard[nD]; }; // Board
        Int_t GetChann(Int_t nD){ return fChann[nD]; }; // Channel
        TString GetSphere(Int_t nD){ return fSphere[nD]; };     // Sphere
        TString GetTopBot(Int_t nD){ return fTopBot[nD]; };     // PIN selection
        TString GetDescr (Int_t nD){ return fDescr [nD]; };     // Channel description
        Int_t GetDiode(Int_t nBoard, Int_t nChann);     // Return diode number from board and channel (-1 = fail)
        //
        // Histograms
        //
        TCanvas *fC;            // Global histograms
        TCanvas *fCnv[fNdiode]; // two canvanses for each sphere
        TH1D *fh_nHit;          // # Hits
        TH1D *fh_nSamp;         // # Samples
        TH1D *fh_base[fNdiode]; // diode baseline distribution
        TH1D *fh_bRMS[fNdiode]; // diode baseline RMS distribution
        TH1D *fh_peak[fNdiode]; // diode peak value distribution
        TH1D *fh_PkRatio[fNsphere]; // peak ratio of diodes in same sphere
        TH1D *fh_PkInt[fNdiode];// diode peak interpolation variable distribution
        TH1D *fh_PkCum[fNdiode];// Cumulative of the above
        //
        void FillHist(Int_t Opt);  // Fill histograms (Opt = 0 binary files, 1 for ART)
        void PrintHist();          // Display histograms
};
#endif
