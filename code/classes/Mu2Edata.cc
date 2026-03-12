#include "Mu2Edata.h"

Mu2Edata::Mu2Edata(TString InFile, Int_t Opt)
{
    //
    // Opt = 0 Normal operation
    // Opt = 1 Do not match tree to local variables
    //
    // Open the ROOT file in read mode
    //
    fIn = TFile::Open(InFile, "READ");
    if (!fIn || fIn->IsZombie()) {
        std::cerr << "Error opening file!"<<InFile.Data() << std::endl;
        return;
    }
    //
    // Get the TTree object from the file
    //
    fTree = (TTree*)fIn->Get("tree");
    if (!fTree) {
        std::cerr << "Error getting tree!" << std::endl;
        fIn->Close();
        return;
    }
    //
    // Get list of branches
    //
    TObjArray *BranchList = fTree->GetListOfBranches();
    //
    // Get list of leaves
    //
    TObjArray *LeaveList = fTree->GetListOfLeaves();
    //
    // Only if normal operation
    if(Opt == 0){
        //
        // Default array sizes
        fMaxHit = 10;
        fMaxSamp = 500;
        InitTree();
    }
}

Mu2Edata::~Mu2Edata()
{
    fIn->Close();
}
void Mu2Edata::InitTree()
{
    //
    // Initiate arrays
    fBoardID = new Int_t[fMaxHit];       // boardID[nhits]
    fLinkID  = new Int_t[fMaxHit];       // linkID[nhits]
    fChanID  = new Int_t[fMaxHit];       // chanID[nhits]
    fErrflag = new Int_t[fMaxHit];       // errflag[nhits]
    fFff     = new Int_t[fMaxHit];       // fff[nhits]
    fTimetot = new Int_t[fMaxHit];       // timetot[nhits]
    fEwhit   = new Int_t[fMaxHit];       // ewhit[nhits]
    fPeakpos = new Int_t[fMaxHit];       // peakpos[nhits]
    fPeakval = new Int_t[fMaxHit];       // peakval[nhits]
    fNofsamples = new Int_t[fMaxHit];    // nofsamples[nhits]
    fFirstsample= new Int_t[fMaxHit];    // firstsample[nhits]
    fADC = new Int_t[fMaxSamp];          // ADC[nsamples]
    //
    // Link all to tree
    fTree->SetBranchAddress("run",       &fRun);
    fTree->SetBranchAddress("subrun",    &fSubrun);
    fTree->SetBranchAddress("nevt",      &fNevt);
    fTree->SetBranchAddress("dtcID",     &fDtcID);
    fTree->SetBranchAddress("currentDTCEventWindow", &fCurrentDTCEventWindow);
    fTree->SetBranchAddress("nhits",     &fNhits);
    fTree->SetBranchAddress("boardID",   fBoardID);
    fTree->SetBranchAddress("linkID",    fLinkID);
    fTree->SetBranchAddress("chanID",    fChanID);
    fTree->SetBranchAddress("errflag",   fErrflag);
    fTree->SetBranchAddress("fff",       fFff);
    fTree->SetBranchAddress("timetot",   fTimetot);
    fTree->SetBranchAddress("ewhit",     fEwhit);
    fTree->SetBranchAddress("peakpos",   fPeakpos);
    fTree->SetBranchAddress("peakval",   fPeakval);
    fTree->SetBranchAddress("nofsamples", fNofsamples);
    fTree->SetBranchAddress("firstsample",fFirstsample);
    fTree->SetBranchAddress("nsamples",  &fNsamples);
    fTree->SetBranchAddress("ADC",       fADC);
}
//
// Accessors for arrays
Int_t Mu2Edata::GetBoardID(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fBoardID[nh];
}
//
Int_t Mu2Edata::GetLinkID(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fLinkID[nh];
}
Int_t Mu2Edata::GetChanID(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fChanID[nh];
}
Int_t Mu2Edata::GetErrflag(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fErrflag[nh];
}
Int_t Mu2Edata::GetFff(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fFff[nh];
}
Int_t Mu2Edata::GetTimetot(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fTimetot[nh];
}
Int_t Mu2Edata::GetEwhit(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fEwhit[nh];
}
Int_t Mu2Edata::GetPeakpos(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fPeakpos[nh];
}
Int_t Mu2Edata::GetPeakval(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fPeakval[nh];
}
Int_t Mu2Edata::GetNofsamples(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fNofsamples[nh];
}
Int_t Mu2Edata::GetFirstsample(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fFirstsample[nh];
}
Int_t Mu2Edata::GetADC(Int_t ns){
    if(ns<0 ||ns>fMaxSamp){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fADC[ns];
}
