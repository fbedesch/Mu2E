#include <TFile.h>
#include <TTree.h>
#include <TObjArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <iostream>
#include "classes/Mu2Edata.h"

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
    const Int_t Nhit = 6;
    TH1D *h_First[Nhit];
    TH1D *h_Leng[Nhit];
    //
    for(Int_t i=0; i<Nhit; i++){
        TString hFid = Form("h_First%d",i);
        TString hTitle = Form("First sample for hit %d",i);
        h_First[i] = new TH1D(hFid,hTitle,300,-0.5,299.5);
        TString hLid = Form("h_Leng%d",i);
        TString hLTitle = Form("Nr of  samples for hit %d",i);
        h_Leng[i] = new TH1D(hLid,hLTitle,300,-0.5,299.5);
    }
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
            //
            h_First[k]->Fill((Double_t) data.GetFirstsample(k));
            h_Leng [k]->Fill((Double_t) data.GetNofsamples(k));
            //
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
    TCanvas *Cnv1 = new TCanvas("Cnv1","First hit start",150,150,1600,800);
    Cnv1->Divide(3,2);
    for(Int_t i=0; i<Nhit; i++){
        Cnv1->cd(i+1);
        h_First[i]->Draw();
    }
    //
    TCanvas *Cnv2 = new TCanvas("Cnv2","Hit length",150,150,1600,800);
    Cnv2->Divide(3,2);
    for(Int_t i=0; i<Nhit; i++){
        Cnv2->cd(i+1);
        h_Leng[i]->Draw();
    }

}
