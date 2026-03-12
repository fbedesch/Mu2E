#include <TFile.h>
#include <TTree.h>
#include <TObjArray.h>
#include <TAxis.h>
#include <TGraph.h>
#include <TVector.h>
#include <TSpline.h>
#include <TF1.h>
#include <TCanvas.h>
#include <iostream>
#include "classes/Mu2Edata.h"

TSpline3* template_spline;  // vector with splines
//
// Test function
//
Double_t SplFun(Double_t *x, Double_t *par)
{
    Double_t fun = 1000*template_spline->Eval(x[0]);
    return fun;
}
//
// Fit function
//
Double_t FitFun(Double_t *x, Double_t *par)
{
/*Fit parameters:
    par[0]=scale factor;
    par[1]=clock tick offset
    par[2]=pedestal offset
*/
  Double_t Scale = par[0];
  Double_t TimeOffSet = par[1];
  Double_t PedOffSet  = par[2];
  Double_t fun;
  fun = Scale*template_spline->Eval(x[0]-TimeOffSet)+PedOffSet;
  return fun;
}

void WaveFit(TString fName)
{
    //
    //
    const Int_t MinHit = 6; //Number of hits
    //
    // Read splines
    //
    TString splineFile = "../data/splines/laser_splines_20250529_disk1phi1_laser_scan_fw04_02_merged.root";
    TFile template_file(splineFile, "READ");
    if (!template_file.IsOpen()){
        std::cout << splineFile <<  " NOT FOUND" << std::endl;
        exit(0);
    }
    else{
        std::cout << "LOADING SPLINES FROM " << splineFile << std::endl;
    }
    //
    // Load spline in vector
    //
    TString Spline_Name = "spline_122_10";
    //
    template_spline = (TSpline3*)template_file.Get(Spline_Name.Data());
    //
    // Check spline
    TCanvas *Csp = new TCanvas("Csp","Test spline",100,100,800,800);
    TF1 *fSpline = new TF1("fSpline",SplFun,-1500.,1500.,1);
    fSpline->SetNpx(1000);
    Csp->Divide(1,1);
    Csp->cd(1);
    fSpline->Draw();
    //
    // Define fitting functions
    //
    TF1 *sFit[MinHit];
    TString sFname[MinHit];
    for(Int_t i=0; i<MinHit; i++){
        sFname[i] = Form("sFit%d",i);
        sFit[i] = new TF1(sFname[i],FitFun,0.,40,3);
        sFit[i]->SetNpx(1000);
        sFit[i]->SetParameter(0,2800.);
        sFit[i]->SetParameter(1,17.);
        sFit[i]->SetParameter(2,2050.);
        gPad->Modified();
        gPad->Update();
    }

    //
    // Open data  file and configure data access
    Mu2Edata data(fName);
    //
    // Setup graphs for Waveforms
    TGraph *g_Wave[MinHit];
    //
    //
    // Main event loop
    //
    TTree *tree = data.GetTree();
    Long64_t nentries = (Int_t) tree->GetEntries();
    cout<<"Nentries= "<<nentries<<endl;
    for (Long64_t i = 0; i < nentries; ++i) {
        tree->GetEntry(i);                  // Access entry
        Int_t Nhits = data.GetNhits();
        if(Nhits == MinHit){                // Select only events with MinHit hits
            std::vector<TVectorD *>WaveCh;
            std::vector<TVectorD *>WaveDt;
            Int_t Length[MinHit];           // Hit length
            Int_t First [MinHit];           // Hit start
            Int_t Board [MinHit];           // Board number
            Int_t Chan  [MinHit];           // Channel number
            TString Title[MinHit];          // Graph titles
            for(Int_t k=0; k<Nhits; k++){   // Loop over hits in event
                First [k] = data.GetFirstsample(k);     // Wave start
                Length[k] = data.GetNofsamples(k);      // Wave length
                Board [k] = data.GetBoardID(k);
                Chan  [k] = data.GetChanID(k);
                Title [k] = Form("Board %d - Channel %d", Board[k], Chan[k]);
                TVectorD WaveData(100);
                TVectorD WaveChan(100);
                for(Int_t j=First[k]; j<First[k]+Length[k]; j++){   // Load waveform arrays
                    WaveChan(j-First[k]) = (Double_t) (j-First[k]);
                    WaveData(j-First[k]) = (Double_t) data.GetADC(j);
                }
                WaveCh.push_back(new TVectorD(WaveChan));     // Store waveform
                WaveDt.push_back(new TVectorD(WaveData));
            }
            //
            //  Plot 6 waveforms
            //
            //
            // Define plotting order
            Int_t Order[MinHit] = {0,2,3,1,4,5};
            TCanvas *Cnv = new TCanvas("Cnv","Hits & samples",50,50,1500,1000);
            Cnv->Divide(3,2);
            for(Int_t k=0; k<MinHit; k++){
                Cnv->cd(k+1);
                Int_t j = Order[k];
                Double_t *Channel = new Double_t[100];
                Double_t *Data = new Double_t[100];
                Channel = WaveCh[j]->GetMatrixArray();
                Data = WaveDt[j]->GetMatrixArray();
                g_Wave[j] = new TGraph(Length[j],Channel,Data);
                g_Wave[j]->SetTitle(Title[j]);
                g_Wave[j]->GetXaxis()->SetLimits(0.,40.);
                g_Wave[j]->Draw();
                g_Wave[j]->Fit(sFname[j]);
                gPad->Modified();
                gPad->Update();
            }
            //
            // User interface
            //
            std::cout<<"New event? (Y/N)"<<std::endl;
            TString resp;
            std::cin>>resp;
            if(resp == "N" || resp == "n") exit(0);
            for(Int_t k=0; k<Nhits; k++){
                delete g_Wave[k];
                g_Wave[k] = nullptr;
            }
        }
    }
}
