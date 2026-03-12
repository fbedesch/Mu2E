//
#ifndef G__MU2EDATA_H
#define G__MU2EDATA_H
//
// ROOT
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TObjArray.h>
#include <TH1.h>
#include <TH2.h>
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
        // Tree info
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
        Int_t *fNofsamples;       // nofsamples[nhits]
        Int_t *fFirstsample;      // firstsample[nhits]
        Int_t fNsamples;
        Int_t *fADC;            // ADC[nsamples]
        //
        // Methods
        void InitTree();
public:
        //
        // Constructors
        Mu2Edata(TString Input_File, Int_t Opt=0);
        // Destructor
        ~Mu2Edata();
        //
        // Print structure
        void PrintBranches() { fBranchList->Print();};
        void PrintLeaves() { fLeaveList->Print();};
        //
        // Accessors
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
        // Setting dimensions
        void SetMaxHit(Int_t MaxHit) {
                fMaxHit = MaxHit;
                InitTree(); };
        void SetMaxSamp(Int_t MaxSamp) {
                fMaxSamp = MaxSamp;
                InitTree(); };
};
#endif
