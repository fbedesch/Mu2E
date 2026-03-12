#include <TFile.h>
#include <TTree.h>
#include <TObjArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <iostream>
#include "Mu2Edata.h"

void SimplePlot(TString fName)
{
    //
    // Access data and configure
    Mu2Edata data(fName);
    //
    // Now fill some plots
    //
    TH1D *h_nHit  = new TH1D("h_nHit",  "Number of hits",   20, -0.5, 19.5);
    TH1D *h_nSamp = new TH1D("h_nSamp", "Number of samples",150, 99.5, 249.5);
    //
    TH1D *h_ppos = new TH1D("h_ppos","Peak position", 20,0.,20.);
    TH1D *h_pval = new TH1D("h_pval","Peak value",300,2000.,5000.);
    //
    // Main event loop
    //
    TTree *tree = data.GetTree();
    Long64_t nentries = (Int_t) tree->GetEntries();
    cout<<"Nentries= "<<nentries<<endl;
    for (Long64_t i = 0; i < nentries; ++i) {
        tree->GetEntry(i);                      // Load new entry
        if(i%1000 == 0)cout<<"nev="<<i<<", Nhit= "<<data.GetNhits()
            <<", Nsamp= "<<data.GetNsamples()<<endl;
        h_nHit ->Fill((Double_t) data.GetNhits());      // Fill histograms
        h_nSamp->Fill((Double_t) data.GetNsamples());
        for(Int_t k=0; k<data.GetNhits(); k++){
            h_ppos->Fill((Double_t) data.GetPeakpos(k));    // Fill more histograms
            h_pval->Fill((Double_t) data.GetPeakval(k));
            if(i%1000 == 0)cout<<"nev="<<i<<", k "<<k
                <<", pos= "<<data.GetPeakpos(k)<<", val= "<<data.GetPeakval(k)<<endl;
        }
    }
    //
    // Display results
    //
    TCanvas *Cnv = new TCanvas("Cnv","Hits & samples",50,50,800,800);
    Cnv->Divide(2,2);
    Cnv->cd(1);
    h_nHit->Draw();
    h_nHit->SetDirectory(nullptr);
    Cnv->cd(2);
    h_nSamp->Draw();
    h_nSamp->SetDirectory(nullptr);
    Cnv->cd(3);
    h_ppos->Draw();
    h_ppos->SetDirectory(nullptr);
    Cnv->cd(4);
    h_pval->Draw();
    h_pval->SetDirectory(nullptr);
    //
}
