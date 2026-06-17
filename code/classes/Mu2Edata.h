//
#ifndef G__MU2EDATA_H
#define G__MU2EDATA_H
//
// ROOT
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TObjArray.h>
#include <TF1.h>
#include <TSpline.h>
#include <TVectorD.h>
#include <TCanvas.h>
//
// STD
#include <iostream>
//
//
//
class Mu2Edata
{
        //
        // Class to unpack Mu2E data
        //
private:
        //
        // Inputs
        TString fName;
        TFile *fIn;
        TSpline3 *fTemplate_spline;
        // Tree info
        // Input tree
        TTree *fTree;
        TObjArray *fBranchList;
        TObjArray *fLeaveList;
        //
        Int_t fMaxHit;
        Int_t fMaxSamp;
        Int_t fRun;
        Int_t fSubrun;
        Int_t fNevt;
        Int_t fDtcID;
        Long64_t fCurrentDTCEventWindow;
        Int_t fNhits;
        Int_t *fBoardID;  // boardID[nhits]
        Int_t *fLinkID;   // linkID[nhits]
        Int_t *fChanID;   // chanID[nhits]
        Int_t *fErrflag;  // errflag[nhits]
        Int_t *fFff;      // fff[nhits]
        Int_t *fTimetot;  // timetot[nhits]
        Int_t *fEwhit;    // ewhit[nhits]
        Int_t *fPeakpos;  // peakpos[nhits]
        Int_t *fPeakval;  // peakval[nhits]
        Int_t *fNofsamples;     // nofsamples[nhits]
        Int_t *fFirstsample;    // firstsample[nhits]
        Int_t fNsamples;
        Int_t *fADC;            // ADC[nsamples]
        //
        // Output tree
        //
        TFile *fInput;
        TTree *foTree;  // Writeing tree
        TTree *frTree;  // Readout tree
        Int_t fNevto;          // Event number
        Int_t fHitNr;          // Nt of hits
        Int_t *fBoardNr;       // Board number
        Int_t *fChNr;          // Channel number
        Int_t *fSampNr;        // Nr of samples
        Int_t *fFirst;         // First sample
        Int_t *fTtot;          // Total time
        Double_t *fChi2;       // Fit Chi2
        Double_t *fNorm;       // Normalization
        Double_t *fTimOff;     // Time Offset
        Double_t *fPedOff;     // Baseline offset
        //
        // Methods
        void InitTreeIn();      // Initialize input data tree
        Double_t FitFun(Double_t *x, Double_t *par);
        void InitArrays();
public:
        //
        // Constructors
        Mu2Edata();
        Mu2Edata(TString Input_File, Int_t Opt=0);
        // Destructor
        ~Mu2Edata();
        //
        // Print structure
        void PrintBranches() { fBranchList->Print();};
        void PrintLeaves() { fLeaveList->Print();};
        //
        void MakeFitROOT(TString RootFile);     // Build root file with fits
        void ReadFitROOT(TString RootFile);     // Read root file with fits
        //
        // Accessors for input
        TString GetFileName() { return fName;};
        TTree *GetTree() { return fTree;};
        Int_t GetMaxHit() { return fMaxHit;};
        Int_t GetMaxSample() { return fMaxSamp;};
        Int_t GetRun() { return fRun;};
        Int_t GetSubRun() { return fSubrun;};
        Int_t GetNevt() { return fNevt;};;
        Int_t GetDtcID() { return fDtcID;};
        Long64_t GetCurrentDTCEventWindow() {return fCurrentDTCEventWindow;};
        Int_t GetNhits() { return fNhits;};
        Int_t GetBoardID(Int_t nh);  // boardID[nhits]
        Int_t GetLinkID(Int_t nh);   // linkID[nhits]
        Int_t GetChanID(Int_t nh);   // chanID[nhits]
        Int_t GetErrflag(Int_t nh);  // errflag[nhits]
        Int_t GetFff(Int_t nh);      // fff[nhits]
        Int_t GetTimetot(Int_t nh);  // timetot[nhits]
        Int_t GetEwhit(Int_t nh);    // ewhit[nhits]
        Int_t GetPeakpos(Int_t nh);  // peakpos[nhits]
        Int_t GetPeakval(Int_t nh);  // peakval[nhits]
        Int_t GetNofsamples(Int_t nh);       // nofsamples[nhits]
        Int_t GetFirstsample(Int_t nh);      // firstsample[nhits]
        Int_t GetNsamples() { return fNsamples;};
        Int_t GetADC(Int_t ns);            // ADC[nsamples]
        //
        // Accessors for output
        TTree *GetOutTree() { return foTree;};
        TTree *GetReadTree() { return frTree;};
        void InitTreeOut();   // Initialize output data tree
        void InitTreeRead();   // Initialize output data tree
        //
        Int_t GetNevto(){ return fNevto;};
        Int_t GetHitNr(){ return fHitNr;};
        Int_t GetBoardNr(Int_t nh);
        Int_t GetChNr(Int_t nh);
        Int_t GetSampNr(Int_t nh);
        Int_t GetFirst(Int_t nh);
        Int_t GetTtot(Int_t nh);
        Double_t GetChi2(Int_t nh);
        Double_t GetNorm(Int_t nh);
        Double_t GetTimOff(Int_t nh);
        Double_t GetPedOff(Int_t nh);
        //
        // Setting dimensions
        void SetMaxHit(Int_t MaxHit) {
                fMaxHit = MaxHit;
                InitTreeIn();
                InitTreeOut();};
        void SetMaxSamp(Int_t MaxSamp) {
                fMaxSamp = MaxSamp;
                InitTreeIn(); };
};
#endif
