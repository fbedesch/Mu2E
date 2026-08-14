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
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
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
        static const Int_t fNdiode   = 20;    // Number of pin diodes in whole system
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
        Int_t fChann[fNdiode]= { 18, 19, 16, 17,                // was 4,5,16,17 until morning 21/7/2026
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
        //
        // Bundles
        //
        void ReadBundle(TString InFile);        // Readin bundle configuration from map
        void GetMeans();                        // Scans file to get mean&sigma of every channel
        static const Int_t fNboard  = 161;      // Number of boards
        static const Int_t fNchann  = 20;       // Number of Channels/board
        Int_t fBoardChToBundle  [fNboard][fNchann];     // Bundle number associated to board/channel
        Double_t fBoardChToMean [fNboard][fNchann];     // Peak mean  associated to board/channel
        Double_t fBoardChToSigma[fNboard][fNchann];     // Peak sigma associated to board/channel
        Double_t fBoardChToNum  [fNboard][fNchann];     // Nr. of events associated to board/channel
        Double_t fRefMean;                              // Mean of diodes 0 and 1 (on table before FW)
        static const Int_t fNbundle  = 16;      // Number of bundles
        Int_t fBundleToPIN1[fNbundle] = {4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14, 14, 16, 16, 18, 18};
        Int_t fBundleToPIN2[fNbundle] = {5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15, 17, 17, 19, 19};

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
        // Laser correction

        void LaserCorrection(TH1D *hRatio, TH1D *hPeakBs, TH1D *hCorr); // Correct for laser fluctuations
        //
        // Histograms for PIN
        //
        TCanvas *fC;            // Global histograms
        TCanvas *fCnv[fNdiode]; // two canvanses for each sphere
        TH1D *fh_nHit;          // # Hits
        TH1D *fh_nSamp;         // # Samples
        TH1D *fh_base[fNdiode]; // diode baseline distribution
        TH1D *fh_bRMS[fNdiode]; // diode baseline RMS distribution
        TH1D *fh_peak[fNdiode]; // diode peak value distribution
        TH1D *fh_peak_bs[fNdiode]; // diode peak value distribution (baseline subtracted)
        TH1D *fh_PkRatio[fNsphere]; // peak ratio of diodes in same sphere
        TH1D *fh_PkInt[fNdiode];// diode peak interpolation variable distribution
        TH1D *fh_PkCum[fNdiode];// Cumulative of the above
        TH1D *fh_PkRti[fNdiode];// Ratio of Peak value and mean of FW00/FW01
        TH1D *fh_PkCor[fNdiode];// Laser corrected peak distribution
        //
        void BookPINplots();          // Book PIN/diode histograms
        void FillPINhist(Int_t Opt);  // Fill histograms (Opt = 0 binary files, 1 for ART)
        void PrintPINhist();          // Display histograms
        //
        // Histograms for bundles
        //
        TCanvas *fCbdl[fNbundle];       // One canvas/bundle
        TH1D *fhb_num [fNbundle];       // Number of fibers found in bundle
        // Uncorrected
        TH1D *fhb_Mean[fNbundle];       // Mean of highest bin in bundle
        TH1D *fhb_Min [fNbundle];       // Smallest value in bundle
        TH1D *fhb_Max [fNbundle];       // Highest value in bundle
        // Baseline subtracted
        TH1D *fhb_Meanb[fNbundle];       // Mean of all values in bundle
        TH1D *fh_MbRti [fNbundle];       // Ratio of Peak value mean and mean of FW00/FW01
        TH1D *fhb_Meanbc [fNbundle];        // Laser corrected peak mean distribution
        TH1D *fhb_Minb [fNbundle];       // Smallest value in bundle
        TH1D *fhb_Maxb [fNbundle];       // Highest value in bundle
        TH1D *fhb_Fibreb[fNbundle];      // All fiber values
        TH1D *fhb_Fibrebc[fNbundle];      // All fiber values corrected
        TH1D *fh_FbRti [fNbundle];        // Ratio of all fiber values and mean of FW00/FW01
        //
        void BookBundlePlots();        // Book bundle plots
        void FillBundHist(Int_t Opt);  // Fill histograms (Opt = 0 binary files, 1 for ART)
        void PrintBundHist();          // Display histograms
};
#endif
