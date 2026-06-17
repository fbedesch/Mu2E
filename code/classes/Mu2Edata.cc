#include "Mu2Edata.h"

Mu2Edata::Mu2Edata()
{
    //
    // Just to access fit data tree
    //
    fMaxHit = 6;
    InitArrays();
}
//
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
        fMaxHit = 6;
        fMaxSamp = 500;
        InitArrays();
        InitTreeIn();
    }
}
void Mu2Edata::InitArrays()
{
// Data file
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
// Fit file

    fBoardNr    = new Int_t[fMaxHit];    // Board number
    fChNr       = new Int_t[fMaxHit];    // Channel number
    fSampNr     = new Int_t[fMaxHit];    // Nr of samples
    fFirst      = new Int_t[fMaxHit];    // First sample
    fTtot       = new Int_t[fMaxHit];    // Total time
    fChi2       = new Double_t[fMaxHit]; // Fit Chi2
    fNorm       = new Double_t[fMaxHit]; // Normalization
    fTimOff     = new Double_t[fMaxHit]; // Time Offset
    fPedOff     = new Double_t[fMaxHit]; // Baseline offset
}
//
Mu2Edata::~Mu2Edata()
{
    /*
    if(fIn)     fIn->Close();
    if(fInput)  fInput->Close();
    if(fBoardID) delete [] fBoardID;
    if(fLinkID)  delete [] fLinkID;
    if(fChanID)  delete [] fChanID;
    if(fErrflag) delete [] fErrflag;
    if(fFff)     delete [] fFff;
    if(fTimetot) delete [] fTimetot;
    if(fEwhit)   delete [] fEwhit;
    if(fPeakpos) delete [] fPeakpos;
    if(fPeakval) delete [] fPeakval;
    if(fNofsamples)     delete [] fNofsamples;
    if(fFirstsample)    delete [] fFirstsample;
    if(fADC)     delete [] fADC;
    //
    if(fBoardNr) delete [] fBoardNr;          // Board number
    if(fChNr)    delete [] fChNr;          // Channel number
    if(fNorm)    delete [] fNorm;          // Normalization
    if(fTimOff)  delete [] fTimOff;          // Time Offset
    if(fPedOff)  delete [] fPedOff;          // Baseline offset
    */
}
void Mu2Edata::InitTreeIn()
{
    //
    // Initiate arrays
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
void Mu2Edata::InitTreeOut()
{
    cout<<"Inside InitTreeOut"<<endl;
    //
    // Initialize output tree
    //
    //
    //
    foTree->Branch("Nevto",  &fNevto, "Nevto/I");
    foTree->Branch("HitNr",  &fHitNr, "HitNr/I");
    foTree->Branch("BoardNr",fBoardNr,"BoardNr[HitNr]/I");
    foTree->Branch("ChNr",   fChNr,   "ChNr[HitNr]/I");
    foTree->Branch("FirstSp",fFirst,  "FirstSp[HitNr]/I");
    foTree->Branch("SampNr", fSampNr, "SampNr[HitNr]/I");
    foTree->Branch("Ttot",   fTtot,   "Ttot[HitNr]/I");
    foTree->Branch("Chi2",   fChi2,   "Chi2[HitNr]/D");
    foTree->Branch("Norm",   fNorm,   "Norm[HitNr]/D");
    foTree->Branch("timOff", fTimOff, "timOff[HitNr]/D");
    foTree->Branch("pedOff", fPedOff, "pedOff[HitNr]/D");
}
//
// Accessors for input arrays
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
//
// Accessors for output arrays

Int_t Mu2Edata::GetBoardNr(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fBoardNr[nh];
}
Int_t Mu2Edata::GetChNr(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fChNr[nh];
}
Double_t Mu2Edata::GetNorm(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    return fNorm[nh];
}
    //
Int_t Mu2Edata::GetSampNr(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    return fSampNr[nh];
}
//
Int_t Mu2Edata::GetFirst(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    return fFirst[nh];
}
//
Int_t Mu2Edata::GetTtot(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    return fTtot[nh];
}
//
Double_t Mu2Edata::GetChi2(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    return fChi2[nh];
}
//
Double_t Mu2Edata::GetTimOff(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fTimOff[nh];
}
Double_t Mu2Edata::GetPedOff(Int_t nh){
    if(nh<0 ||nh>fMaxHit){
        std::cerr<<"Error index out of limits!"<<std::endl;
        return -1;
    }
    //
    return fPedOff[nh];
}
//
// Make root file with template fit results
//
//
// Fit function
//
Double_t Mu2Edata::FitFun(Double_t *x, Double_t *par)
{
/*Fit parameters:
    par[0]=scale factor;
    par[1]=clock tick offset
    par[2]=pedestal offset
*/
  Double_t Scale = par[0];
  Double_t TimeOffSet = par[1];
  Double_t PedOffSet  = par[2];
  Double_t BaseOffset = 0.770712;
  Double_t fun;
  fun = Scale*(fTemplate_spline->Eval(x[0]-TimeOffSet)-BaseOffset)+PedOffSet;
  return fun;
}
void Mu2Edata::MakeFitROOT(TString RootFile)
{
    //
    // Setup output file structure
    //
    auto fOut = TFile::Open(RootFile, "RECREATE");
    foTree = new TTree("foTree", "FitData");
    InitTreeOut();
    std::cout<<"MakeFitROOT: TTree pointer = "<<foTree<<std::endl;
    const Int_t MinHit = 6;     // Only events with 6 hits
    //
    // Read splines
    //
    TString splineFile = "../data/splines/laser_splines_caloDTC2_Laser_ROC_0503_D1P0F1_fw04.root";
    TFile template_file(splineFile, "READ");
    if (!template_file.IsOpen()){
        std::cout << splineFile <<  " NOT FOUND" << std::endl;
        exit(0);
    }
    else std::cout << "LOADING SPLINE FROM " << splineFile << std::endl;
    //
    TString Spline_Name = "spline_160_4";
    //
    // Load spline
    fTemplate_spline = (TSpline3*)template_file.Get(Spline_Name.Data());
    std::cout<<"TSpline "<<Spline_Name<<" loaded"<<endl;
    // Get spline range
    Double_t Xmin = fTemplate_spline->GetXmin();
    Double_t Xmax = fTemplate_spline->GetXmax();
    cout<<"Spline: Xmin= "<<Xmin<<", Xmax= "<<Xmax<<endl;
    //
    template_file.Close();
    //
    // Define fitting functions
    // Assume only board 160 ch 4, 5, 16, 17 for now
    // 2 hits each for ch 4 and 5
    //
    TF1 *sFit[MinHit];
    TString sFname[MinHit];
    for(Int_t i=0; i<MinHit; i++){
        sFname[i] = Form("sFit%d",i);
        // Fit version with splines
        sFit[i] = new TF1(sFname[i],this,&Mu2Edata::FitFun,0.,40,3,"Mu2Edata","FitFun");
        sFit[i]->SetNpx(1000);
        sFit[i]->SetParameter(0,2800.);
        sFit[i]->SetParameter(1,0.);
        sFit[i]->SetParameter(2,2050.);
    }
    //
    //
    //
    // Setup graphs for Waveforms
    TGraph *g_Wave[MinHit];
    //
    //
    // Main event loop
    // Fill waveforms into TGraph' s
    //
    Long64_t nentries = (Long64_t) fTree->GetEntries();
    std::cout<<"Nentries= "<<nentries<<std::endl;
    for (Long64_t i = 0; i < nentries; ++i) {
        fTree->GetEntry(i);                  // Access entry
        if(i%1000 == 0)std::cout<<"Processing event "<<i<<std::endl;
        Int_t Nhits = GetNhits();
        if(Nhits == MinHit){                // Select only events with MinHit hits
            TString Title[MinHit];          // Graph titles
            for(Int_t k=0; k<Nhits; k++){   // Loop over hits in event
                fFirst   [k] = GetFirstsample(k);     // Wave start
                fSampNr  [k] = GetNofsamples(k);      // Wave length
                fBoardNr [k] = GetBoardID(k);
                fChNr    [k] = GetChanID(k);
                fSampNr  [k] = GetNofsamples(k);
                fTtot    [k] = GetTimetot(k);
                if(i%1000 == 0)std::cout<<"Processing hit "<<k
                    <<", Ch="<< fChNr[k]<<", First= "<<fFirst[k]
                    <<", Nsamp= "<<fSampNr[k]<<", Ttot= "<<fTtot[k]<<std::endl;
                //Title [k] = Form("Board %d - Channel %d", fBoardNr[k], fChNr[k]);
                //cout<<Title[k]<<endl;
                TVectorD WaveData(fSampNr[k]); WaveData.Zero();
                TVectorD WaveChan(fSampNr[k]); WaveChan.Zero();
                for(Int_t j=fFirst[k]; j<fFirst[k]+fSampNr[k]; j++){   // Load waveform arrays
                    WaveChan(j-fFirst[k]) = (Double_t) (j-fFirst[k]);
                    WaveData(j-fFirst[k]) = (Double_t) GetADC(j);
                }
                //
                // Fill TGraph and fit it
                g_Wave[k] = new TGraph(fSampNr[k],
                                WaveChan.GetMatrixArray(),WaveData.GetMatrixArray());
                //Double_t Start = (Double_t) First[k];
                //sFit[k]->SetParameter(1,Start);
                //g_Wave[k]->Fit(sFname[k],"RQ","",Xmin+Start, Xmax+Start);
                g_Wave[k]->Fit(sFname[k],"RQ","",Xmin, Xmax);
                // Full output tree
                fNorm[k]   = sFit[k]->GetParameter(0);
                fTimOff[k] = sFit[k]->GetParameter(1);
                fPedOff[k] = sFit[k]->GetParameter(2);
                fChi2[k]   = sFit[k]->GetChisquare();
                //cout<<"Stored fit parameters"<<endl;
            }
            fNevto = i;
            fHitNr = Nhits;
            //
            // Fill output tree entry
            foTree->Fill();
        }
    }
    fOut->cd();
    foTree->Write();
    //
    // Close all open files
    fOut->Close();
}
//
// Setup to read fit file
//
void Mu2Edata::InitTreeRead()
{
    cout<<"Inside InitTreeRead"<<endl;
    //
    // Initialize output tree
    //
    //
    frTree->SetBranchAddress("Nevto",  &fNevto);
    frTree->SetBranchAddress("HitNr",  &fHitNr);
    frTree->SetBranchAddress("BoardNr",fBoardNr);
    frTree->SetBranchAddress("ChNr",   fChNr);
    frTree->SetBranchAddress("FirstSp",fFirst);
    frTree->SetBranchAddress("SampNr", fSampNr);
    frTree->SetBranchAddress("Ttot",   fTtot);
    frTree->SetBranchAddress("Chi2",   fChi2);
    frTree->SetBranchAddress("Norm",   fNorm);
    frTree->SetBranchAddress("timOff", fTimOff);
    frTree->SetBranchAddress("pedOff", fPedOff);
    cout<<"Done branch setting"<<endl;
}
void Mu2Edata::ReadFitROOT(TString RootFile)
{
    //
    // Open the ROOT file in read mode
    //
    cout<<"ReadFitROOT: input file is "<<RootFile<<endl;
    fInput = TFile::Open(RootFile, "READ");
    if (!fInput || fInput->IsZombie()) {
        std::cerr << "Error opening file!"<<RootFile.Data() << std::endl;
        return;
    }
    cout<<"ReadFitROOT: input file read"<<endl;
    //
    // Get the TTree object from the file
    //
    frTree = (TTree*)fInput->Get("foTree");
    cout<<"Got tree from file"<<endl;
    if (!frTree) {
        std::cerr << "Error getting tree!" << std::endl;
        fInput->Close();
        return;
    }
    InitTreeRead();
    cout<<"Tree initialized"<<endl;
}
