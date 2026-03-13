#include <TFile.h>
#include <TTree.h>
#include <TObjArray.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <iostream>
#include "classes/Mu2Edata.h"

void WavePlot(TString fName)
{
    //
    // Open data  file and configure data access
    Mu2Edata data(fName);
    //
    // Setup graphs for Waveforms
    const Int_t MinHit = 6;
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
            std::vector<Int_t *>WaveCh;
            std::vector<Int_t *>WaveDt;
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
                Int_t WaveData[100];
                Int_t WaveChan[100];
                for(Int_t j=First[k]; j<First[k]+Length[k]; j++){   // Load waveform arrays
                    WaveChan[j-First[k]] = j-First[k];
                    WaveData[j-First[k]] = data.GetADC(j);
                }
                WaveCh.push_back(WaveChan);     // Store waveform
                WaveDt.push_back(WaveData);
            }
            //
            //  Plot 6 waveforms
            //
            TCanvas *Cnv = new TCanvas("Cnv","Hits & samples",50,50,1500,1000);
            Cnv->Divide(3,2);
            for(Int_t k=0; k<MinHit; k++){
                Cnv->cd(k+1);
                g_Wave[k] = new TGraph(Length[k],WaveCh[k],WaveDt[k]);
                g_Wave[k]->SetTitle(Title[k]);
                g_Wave[k]->Draw();
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
