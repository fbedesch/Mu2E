#include <TTree.h>
#include <TH1.h>
#include <TCanvas.h>
#include <iostream>
#include "classes/Mu2Edata.h"

void PlotFitData(TString fName, Double_t Tmin=770., Double_t Tmax=775.)
{
    //

    Double_t TickTime = 5.0;    // ns/tick
    //
    // Access data and configure
    Mu2Edata data;
    cout<<"Mu2Edata initialized"<<endl;;
    data.ReadFitROOT(fName);
    cout<<"ReadFitROOT called"<<endl;
    //
    // Now fill some plots
    //
    TH1D *h_time4_0  = new TH1D("h_time4_0",  "Time hits ch 4",   300, -2.0, 4.);
    TH1D *h_time4_1  = new TH1D("h_time4_1",  "Time second hit ch 4",   300, -2.0, 4.);
    //
    TH1D *h_time5_0  = new TH1D("h_time5_0",  "Time hits ch 5",   300, -2.0, 4.);
    TH1D *h_time5_1  = new TH1D("h_time5_1",  "Time second hit ch 5",  300, -2.0, 4.);
    //
    TH1D *h_tdiff4  = new TH1D("h_tdiff4",  "Time difference ch 4",   200, -10., 10.);
    TH1D *h_tdiff5  = new TH1D("h_tdiff5",  "Time difference ch 5",   200, -10., 10.);
    TH1D *h_atdiff4  = new TH1D("h_atdiff4",  "Abs. Time difference ch 4 (ns)",   200, Tmin, Tmax);
    TH1D *h_atdiff5  = new TH1D("h_atdiff5",  "Abs. Time difference ch 5 (ns)",   200, Tmin, Tmax);
    //
    // Main event loop
    //
    TTree *tree = data.GetReadTree();
    cout<<"Tree located"<<endl;
    Long64_t nentries = (Long64_t) tree->GetEntries();
    cout<<"Obtained entries"<<endl;
    cout<<"Nentries= "<<nentries<<endl;
    for (Long64_t i = 0; i < nentries; ++i) {
        tree->GetEntry(i);                      // Load new entry
        if(i%1000 == 0)cout<<"nev="<<i<<", Nhit= "<<data.GetHitNr()<<endl;
        Int_t i4 = 0;           // Data ch 4 order
        Double_t Dat4_0 = 0.;   // First ch 4 data
        Double_t Dat4_1 = 0.;   // Second ch 4 data
        Double_t tAbs4_0 = 0.;  // Absolute time 4_0
        Double_t tAbs4_1 = 0.;  // Absolute time 4_1
        //
        Int_t i5 = 0;           // Data ch 5 order
        Double_t Dat5_0 = 0.;   // First ch 5 data
        Double_t Dat5_1 = 0.;   // Seconf ch 5 data
        Double_t tAbs5_0 = 0.;  // Absolute time 5_0
        Double_t tAbs5_1 = 0.;  // Absolute time 5_1
        //
        //cout<<"Number of hits = "<<data.GetHitNr()<<endl;
        for(Int_t k=0; k<data.GetHitNr(); k++){ // Hit loop
            // Channel 4 data
            if(data.GetChNr(k) == 4){
                if(i4 == 0){
                    Dat4_0 = data.GetTimOff(k);
                    tAbs4_0 = ((Double_t) data.GetTtot(k)+data.GetTimOff(k))*TickTime;
                    i4++;
                }else {
                    Dat4_1 = data.GetTimOff(k);
                    tAbs4_1 = ((Double_t) data.GetTtot(k)+data.GetTimOff(k))*TickTime;
                }
            }
            // Channel 5 data
            if(data.GetChNr(k) == 5){
                if(i5 == 0){
                    Dat5_0 = data.GetTimOff(k);
                    tAbs5_0 = ((Double_t) data.GetTtot(k)+data.GetTimOff(k))*TickTime;
                    i5++;
                }else {
                    Dat5_1 = data.GetTimOff(k);
                    tAbs5_1 = ((Double_t) data.GetTtot(k)+data.GetTimOff(k))*TickTime;
                }
            }
            if(i%1000 == 0){
                std::cout<<"nev="<<i<<", k "<<k
                <<", Channel= "<<data.GetChNr(k)<<", Time= "<<data.GetTimOff(k)<<std::endl;
                Double_t AbsTime = TickTime*data.GetTimOff(k)+(Double_t) data.GetTtot(k);
                std::cout<<"nev="<<i<<", k "<<k
                <<", Channel= "<<data.GetChNr(k)<<", First= "<<data.GetFirst(k)<<", AbsTime= "
                <<AbsTime<<", Total time = "<<data.GetTtot(k)<<std::endl;
            }
        }
        h_time4_0->Fill(Dat4_0);
        h_time4_1->Fill(Dat4_1);
        h_tdiff4->Fill(Dat4_1-Dat4_0);
        h_atdiff4->Fill(tAbs4_1-tAbs4_0);
        //
        h_time5_0->Fill(Dat5_0);
        h_time5_1->Fill(Dat5_1);
        h_tdiff5->Fill(Dat5_1-Dat5_0);
        h_atdiff5->Fill(tAbs5_1-tAbs5_0);
    }
    //
    // Display results
    //
    TCanvas *Cnv = new TCanvas("Cnv","Time distributions",50,50,1600,800);
    Cnv->Divide(2,1);
    Cnv->cd(1);
    h_time4_0->Draw();
    h_time4_0->SetDirectory(nullptr);
    h_time4_1->SetLineColor(kRed);
    h_time4_1->Draw("SAME");
    h_time4_1->SetDirectory(nullptr);
    Cnv->cd(2);
    h_time5_0->Draw();
    h_time5_0->SetDirectory(nullptr);
    h_time5_1->SetLineColor(kRed);
    h_time5_1->Draw("SAME");
    h_time5_1->SetDirectory(nullptr);
    //

    TCanvas *Cnv1 = new TCanvas("Cnv1","Time differences",150,150,1600,1600);
    Cnv1->Divide(2,2);
    Cnv1->cd(1);
    h_tdiff4->Draw();
    h_tdiff4->SetDirectory(nullptr);
    Cnv1->cd(2);
    h_tdiff5->Draw();
    h_tdiff5->SetDirectory(nullptr);
    Cnv1->cd(3);
    h_atdiff4->Draw();
    h_atdiff4->SetDirectory(nullptr);
    Cnv1->cd(4);
    h_atdiff5->Draw();
    h_atdiff5->SetDirectory(nullptr);
}
