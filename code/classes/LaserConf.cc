#include "LaserConf.h"

LaserConf::LaserConf()
{
    //
    // Just to access configuration data
    //
    InitConf();
}
//
LaserConf::LaserConf(TString InFile)
{
    //
    // Input filte
    fName = InFile;
    //
    // Setup descriptions
    InitConf();
    //cout<<"After InitConf()"<<endl;
    //
    // Setup histograms and canvanses
    //
    fC = new TCanvas("fC","Global quantities",0,0,800,800);
    fh_nHit = new TH1D("fh_nHit","Number of hits",100,0.,4000.);
    fh_nSamp = new TH1D("fh_nSamp","Number of samples",100,0.,250.);
    //
    fCnv[0] = new TCanvas("fCnv_0","Optical table before the FW",10,10,800,800);
    fh_base[0] = new TH1D("fh_base_0","Baseline FW00", 100, 1950., 2250.);
    fh_bRMS[0] = new TH1D("fh_bRMS_0","Baseline RMS FW00", 100, -5., 5.);
    fh_peak[0] = new TH1D("fh_peak_0","Peak value FW00",100, 2100.,4100.);
    fh_PkInt[0] = new TH1D("fh_PkInt_0","Peak interpolation FW00",100, 0., 1.);
    fh_PkCum[0] = new TH1D("fh_PkCum_0","Peak interp. cumulative FW00",100, 0.,1.);
    fh_PkRatio[0] = new TH1D("fh_PkRatio_0","Peak ratio FW00/FW01", 100, 0.5, 1.5);
    //
    fCnv[1] = new TCanvas("fCnv_1","Optical table before the FW",20,20,800,800);
    fh_base[1] = new TH1D("fh_base_1","Baseline FW01", 100, 1950., 2250.);
    fh_bRMS[1] = new TH1D("fh_bRMS_1","Baseline RMS FW01", 100, -5., 5.);
    fh_peak[1] = new TH1D("fh_peak_1","Peak value FW01",100, 2100.,4100.);
    fh_PkInt[1] = new TH1D("fh_PkInt_1","Peak interpolation FW01",100, 0., 1.);
    fh_PkCum[1] = new TH1D("fh_PkCum_1","Peak interp. cumulative FW01",100, 0.,1.);
    //
    fCnv[2] = new TCanvas("fCnv_2","Optical table after the FW",30,30,800,800);
    fh_base[2] = new TH1D("fh_base_2","Baseline FW10", 100, 1950., 2250.);
    fh_bRMS[2] = new TH1D("fh_bRMS_2","Baseline RMS FW10", 100, -5., 5.);
    fh_peak[2] = new TH1D("fh_peak_2","Peak value FW10",100, 2100.,4100.);
    fh_PkInt[2] = new TH1D("fh_PkInt_2","Peak interpolation FW10",100, 0., 1.);
    fh_PkCum[2] = new TH1D("fh_PkCum_2","Peak interp. cumulative FW10",100, 0.,1.);
    fh_PkRatio[1] = new TH1D("fh_PkRatio_1","Peak ratio FW10/FW11", 100, 0.5, 1.5);
    //
    fCnv[3] = new TCanvas("fCnv_3","Optical table after the FW",40,40,800,800);
    fh_base[3] = new TH1D("fh_base_3","Baseline FW11", 100, 1950., 2250.);
    fh_bRMS[3] = new TH1D("fh_bRMS_3","Baseline RMS FW11", 100, -5., 5.);
    fh_peak[3] = new TH1D("fh_peak_3","Peak value FW11",100, 2100.,4100.);
    fh_PkInt[3] = new TH1D("fh_PkInt_3","Peak interpolation FW11",100, 0., 1.);
    fh_PkCum[3] = new TH1D("fh_PkCum_3","Peak interp. cumulative FW11",100, 0.,1.);
    cout<<"Optical board histograms booked"<<endl;
    //
    Int_t iSphere = 2;  // Sphere index
    for(Int_t i=4; i<fNdiode; i++){
        TString CnvId = Form("fCnv_%d",i);
        TString CnvName = Form("Disk %d, Phi %d, Sphere %s",
                         fDisk[i], fPhi[i], fSphere[i].Data());
        fCnv[i] = new TCanvas(CnvId,CnvName,10*(i+1),10*(i+1),800,800);
        TString hBaseID = Form("fh_base_%d",i);
        TString hBaseTitle = Form("Baseline board %d, channel %d",fBoard[i], fChann[i]);
        fh_base[i] = new TH1D(hBaseID,hBaseTitle, 100, 1950., 2250.);
        TString hRMS_ID = Form("fh_bRMS_%d",i);
        TString hRMS_Title = Form("Baseline RMS board %d, channel %d",fBoard[i], fChann[i]);
        fh_bRMS[i] = new TH1D(hRMS_ID,hRMS_Title, 100, -5., 5.);
        TString hPeakID = Form("fh_peak_%d",i);
        TString hPeakTitle = Form("Peak value board %d, channel %d",fBoard[i], fChann[i]);
        fh_peak[i] = new TH1D(hPeakID,hPeakTitle,100, 2100.,4100.);
        TString hPkIntID = Form("fh_PkInt_%d",i);
        TString hPkIntTitle = Form("Peak interpolation board %d, channel %d",fBoard[i], fChann[i]);
        fh_PkInt[i] = new TH1D(hPkIntID,hPkIntTitle,100, 0., 1.);
        TString hPkCumID = Form("fh_PkCum_%d",i);
        TString hPkCumTitle = Form("Peak interp. cumulative board %d, channel %d",fBoard[i], fChann[i]);
        fh_PkCum[i] = new TH1D(hPkCumID,hPkCumTitle,100, 0.,1.);
        if(i%2 == 0){
            TString hPkRatioID = Form("fh_PkRatio_%d",iSphere);
            TString hPkRatioTitle = Form("Peak ratio board %d-ch %d/board %d-ch %d",
                                         fBoard[i],fChann[i],fBoard[i+1],fChann[i+1]);
            fh_PkRatio[iSphere] = new TH1D("hPkRatioID","hPkRatioTitle", 100, 0.5, 1.5);
            iSphere++;
        }
    }
    cout<<"All histograms booked"<<endl;
}
void LaserConf::InitConf()
{
    //
    // Channel descriptions
    //
    fDescr[0] = "Optical table before filter wheel FW00";
    fDescr[1] = "Optical table before filter wheel FW01";
    fDescr[2] = "Optical table after filter wheel FW10";
    fDescr[3] = "Optical table after filter wheel FW10";
    for(Int_t i=4; i<fNdiode; i++){
        fDescr[i] = Form("Disk %d, Phi %d, Board %d, Channel %d, Sphere %s, Pin %s",
                         fDisk[i], fPhi[i],fBoard[i], fChann[i], fSphere[i].Data(), fTopBot[i].Data());
    }
}
//
LaserConf::~LaserConf()
{
}
//
Int_t LaserConf::GetDiode(Int_t nBoard, Int_t nChann)
{
    Int_t Diode = -1;   // default if no match
    for(Int_t i=0; i<fNdiode; i++){
        if(nBoard == fBoard[i] && nChann == fChann[i]){
            Diode = i;
        }
    }
    return Diode;
}
//
// Fill histograms
//
void LaserConf::FillHist(Int_t Opt)
{
    //
    // Open input file
    // Opt = 0 for binary (default) or 1 for ART
    Mu2Edata data(fName, Opt);
    //
    // Main event loop
    //
    TTree *tree = data.GetTree();
    Long64_t nentries = (Int_t) tree->GetEntries();
    cout<<"Nentries= "<<nentries<<endl;
    for (Long64_t i = 0; i <nentries; ++i) {
        tree->GetEntry(i);    // Load new entry
        Int_t Nhits = data.GetNhits();
        Int_t Nsamp = data.GetNsamples();
        if(i%1000 == 0)std::cout<<"nev="<<i<<", Nhit= "<<Nhits
            <<", Nsamp= "<<Nsamp<<std::endl;
        fh_nHit ->Fill((Double_t)Nhits);      // Fill histograms
        fh_nSamp->Fill((Double_t)Nsamp);
        TVectorD Peak(fNdiode); Peak.Zero();            // Store peak values
        //
        for(Int_t k=0; k<Nhits; k++){
            Int_t nBoard = data.GetBoardID(k);    // Get board
            Int_t nChann = data.GetChanID(k);    // Get Channel
            Int_t iDiode = GetDiode(nBoard, nChann);      // Get pin diode
            //std::cout<<"Hit= "<<k<<", Board= "<<nBoard<<", Channel= "<<nChann
            //<<", Diode = "<<iDiode<<std::endl;
            Int_t Sphere = -1;
            if(iDiode >= 0){
                // Found diode
                std::cout<<"Hit= "<<k<<", Board= "<<nBoard<<", Channel= "<<nChann
                <<", Diode = "<<iDiode<<std::endl;
                Sphere = iDiode/2;   // Get Sphere
                Double_t Pk0 = (Double_t) data.GetPeakval(k);
                Peak(iDiode)  = Pk0;    // Store peak value
                Int_t tMax   = data.GetPeakpos(k);                // Peak position
                fh_peak[iDiode]->Fill(Pk0);
                //
                // Get waveform data
                Int_t First  = data.GetFirstsample(k);     // Wave start
                Int_t Length = data.GetNofsamples(k);      // Wave length
                //
                // Peak interpolation
                Double_t PkMin = (Double_t) data.GetADC(First + tMax-1);
                Double_t PkMax = (Double_t) data.GetADC(First + tMax+1);
                Double_t PkInt = 2.*TMath::ATan((Pk0-PkMin)/(Pk0-PkMax))/TMath::Pi();
                fh_PkInt[iDiode]->Fill(PkInt);
                //
                // Baseline stability
                Double_t BaseV1 = 0.0;  // Bealine mean value
                Double_t BaseV2 = 0.0;  // Mean of baseline squared values
                Int_t nBase = 10;
                for(Int_t j=First; j<First+nBase; j++){
                    Double_t BaseV = (Double_t) data.GetADC(j); // baseline value at location j
                    BaseV1 += BaseV;
                    BaseV2 += BaseV*BaseV;
                }
                BaseV1 *= 1./(Double_t) nBase;  // <Base>
                BaseV2 *= 1./(Double_t) nBase;  // <Base^2>
                Double_t BaseRMS = TMath::Sqrt(BaseV2-BaseV1*BaseV1);   // Baseline RMS
                fh_base[iDiode]->Fill(BaseV1);
                fh_bRMS[iDiode]->Fill(BaseRMS);
            }  // end if(iDiode) >= 0)
        }   // end hit loop
        //std::cout<<"End of hit loop"<<std::endl;
        //
        //
        // Fill peak ratios in same sphere if available
        Int_t iSphere = 0;
        for(Int_t iD=0; iD<fNdiode; iD++){
            if(iD%2 == 0){
                if(Peak(iD)*Peak(iD+1)>0.)fh_PkRatio[iSphere]->Fill(Peak(iD)/Peak(iD+1));
                iSphere++;
            }
        }
        //std::cout<<"End event "<<i<<std::endl;
    } // end event loop
    //std::cout<<"End event loop"<<std::endl;
}
//
// Display histograms
//
void LaserConf::PrintHist()
{
    //
    // Display two canvases per diode
    //
    fC->Divide(2,1);
    fC->cd(1);
    fh_nHit->Draw();
    fC->cd(2);
    fh_nSamp->Draw();
    //
    for(Int_t i=0; i<fNdiode; i++){
        fCnv[i]->Divide(2,2);
        fCnv[i]->cd(1);
        fh_base[i]->Draw();
        fCnv[i]->cd(2);
        fh_bRMS[i]->Draw();
        fCnv[i]->cd(3);
        fh_peak[i]->Draw();
        fCnv[i]->cd(4);
        fh_PkInt[i]->Draw();
    }
}
