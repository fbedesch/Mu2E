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
    //
    //==============================================================
    //      PIN plots
    //
    // Setup optical board histograms for PIN diodes
    //
    fh_nHit = new TH1D("fh_nHit","Number of hits",100,0.,4000.);
    fh_nSamp = new TH1D("fh_nSamp","Number of samples",600,0.,60000.);
    //
    fh_base[0] = new TH1D("fh_base_0","Baseline FW00", 100, 1950., 2250.);
    fh_bRMS[0] = new TH1D("fh_bRMS_0","Baseline RMS FW00", 100, -5., 5.);
    fh_peak[0] = new TH1D("fh_peak_0","Peak value FW00",200, 2100.,4100.);
    fh_peak_bs[0] = new TH1D("fh_peak_bs_0","Peak value FW00 (subtracted)",210, 0.,2100.);
    fh_PkInt[0] = new TH1D("fh_PkInt_0","Peak interpolation FW00",100, 0., 1.);
    fh_PkCum[0] = new TH1D("fh_PkCum_0","Peak interp. cumulative FW00",100, 0.,1.);
    fh_PkRatio[0] = new TH1D("fh_PkRatio_0","Peak ratio FW00/FW01", 100, 0.5, 1.5);
    //
    fh_base[1] = new TH1D("fh_base_1","Baseline FW01", 100, 1950., 2250.);
    fh_bRMS[1] = new TH1D("fh_bRMS_1","Baseline RMS FW01", 100, -5., 5.);
    fh_peak[1] = new TH1D("fh_peak_1","Peak value FW01",200, 2100.,4100.);
    fh_peak_bs[1] = new TH1D("fh_peak_bs_1","Peak value FW01 (subtracted)",210, 0.,2100.);
    fh_PkInt[1] = new TH1D("fh_PkInt_1","Peak interpolation FW01",100, 0., 1.);
    fh_PkCum[1] = new TH1D("fh_PkCum_1","Peak interp. cumulative FW01",100, 0.,1.);
    //
    fh_base[2] = new TH1D("fh_base_2","Baseline FW10", 100, 1950., 2250.);
    fh_bRMS[2] = new TH1D("fh_bRMS_2","Baseline RMS FW10", 100, -5., 5.);
    fh_peak[2] = new TH1D("fh_peak_2","Peak value FW10",200, 2100.,4100.);
    fh_peak_bs[2] = new TH1D("fh_peak_bs_2","Peak value FW10 (subtracted)",210, 0.,2100.);
    fh_PkInt[2] = new TH1D("fh_PkInt_2","Peak interpolation FW10",100, 0., 1.);
    fh_PkCum[2] = new TH1D("fh_PkCum_2","Peak interp. cumulative FW10",100, 0.,1.);
    fh_PkRatio[1] = new TH1D("fh_PkRatio_1","Peak ratio FW10/FW11", 100, 0.5, 1.5);
    //
    fh_base[3] = new TH1D("fh_base_3","Baseline FW11", 100, 1950., 2250.);
    fh_bRMS[3] = new TH1D("fh_bRMS_3","Baseline RMS FW11", 100, -5., 5.);
    fh_peak[3] = new TH1D("fh_peak_3","Peak value FW11",200, 2100.,4100.);
    fh_peak_bs[3] = new TH1D("fh_peak_bs_3","Peak value FW11 (subtracted)",210, 0.,2100.);
    fh_PkInt[3] = new TH1D("fh_PkInt_3","Peak interpolation FW11",100, 0., 1.);
    fh_PkCum[3] = new TH1D("fh_PkCum_3","Peak interp. cumulative FW11",100, 0.,1.);
    //
    // Setup on detector histograms and canvases for on detector PIN diodes
    //
    Int_t iSphere = 2;  // Sphere index
    for(Int_t i=4; i<fNdiode; i++){
        TString hBaseID = Form("fh_base_%d",i);
        TString hBaseTitle = Form("Baseline board %d, channel %d",fBoard[i], fChann[i]);
        fh_base[i] = new TH1D(hBaseID,hBaseTitle, 100, 1950., 2250.);
        TString hRMS_ID = Form("fh_bRMS_%d",i);
        TString hRMS_Title = Form("Baseline RMS board %d, channel %d",fBoard[i], fChann[i]);
        fh_bRMS[i] = new TH1D(hRMS_ID,hRMS_Title, 100, -5., 5.);
        TString hPeakID = Form("fh_peak_%d",i);
        TString hPeakTitle = Form("Peak value board %d, channel %d",fBoard[i], fChann[i]);
        fh_peak[i] = new TH1D(hPeakID,hPeakTitle,200, 2100.,4100.);
        TString hPeakIDbs = Form("fh_peak_bs_%d",i);
        TString hPeakTitlebs = Form("Peak value board %d, channel %d (subtracted)",fBoard[i], fChann[i]);
        fh_peak_bs[i] = new TH1D(hPeakIDbs,hPeakTitlebs,210, 0.,2100.);
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
    //
    //====================================================================================
    //  Bundle plots
    //
    // Initialize board/chann to bundles
    //
    TString BundleMap = "./data/BundleMap.csv";
    ReadBundle(BundleMap);
    //
    // Configure plots
    //
    for(Int_t i=0; i<fNbundle; i++){
        // histogram ID
        TString b_numID = Form("fhb_num_%d",i);
        TString b_MeanID  = Form("fhb_Mean_%d",i);  // Uncorrected
        TString b_MinID  = Form("fhb_Min_%d",i);
        TString b_MaxID  = Form("fhb_Max_%d",i);
        //
        TString b_MeanIDb  = Form("fhb_Mean_b_%d",i);    // Baseline subtracted
        TString b_MinIDb  = Form("fhb_Min_b_%d",i);
        TString b_MaxIDb  = Form("fhb_Max_b_%d",i);
        // histogram titles
        TString b_numTit  = Form("Number of fibers fired in bundle %d",i);
        TString b_MeanTit = Form("Mean of fired fibers in bundle %d",i);    // Uncorrected
        TString b_MinTit  = Form("Lowest  fired fiber  in bundle %d",i);
        TString b_MaxTit  = Form("Highest fired fiber  in bundle %d",i);
        //
        TString b_MeanTitb = Form("Mean of fired fibers (baseline subtracted) in bundle %d",i); // Baseline subtracted
        TString b_MinTitb  = Form("Lowest  fired fiber (baseline subtracted) in bundle %d",i);
        TString b_MaxTitb  = Form("Highest fired fiber (baseline subtracted) in bundle %d",i);
        // histogram allocation
        fhb_num [i] = new TH1D(b_numID,b_numTit,  200,   0., 200.);
        fhb_Mean[i] = new TH1D(b_MeanID,b_MeanTit,210,2000.,4100.); // Uncorrected
        fhb_Min [i] = new TH1D(b_MinID,b_MinTit,  210,2000.,4100.);
        fhb_Max [i] = new TH1D(b_MaxID,b_MaxTit,  210,2000.,4100.);
        //
        fhb_Meanb[i] = new TH1D(b_MeanIDb,b_MeanTitb,210,0.,2100.); // Baseline subtracted
        fhb_Minb [i] = new TH1D(b_MinIDb,b_MinTitb,  210,0.,2100.);
        fhb_Maxb [i] = new TH1D(b_MaxIDb,b_MaxTitb,  210,0.,2100.);
    }

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
// Read bundle map and initialize board/chann to bundle pointers
//
void LaserConf::ReadBundle(TString InFile)
{
    //
    // Read in configuration file
    //
    std::ifstream fIn(InFile.Data());
    if (!fIn) {
        std::cerr << "Error opening bundle configuration file!"<<InFile.Data() << std::endl;
        return;
    }
    //
    // Arrays for storing data
    //
    std::vector<Int_t>Board;
    std::vector<Int_t>Disk;
    std::vector<Int_t>Phi;
    std::vector<Int_t>Channel;
    std::vector<Int_t>Bundle;
    //
    std::string Line;
    std::getline(fIn, Line);  // GetHeaders
    //std::cout<<"Header line: "<<Line<<std::endl;
    while(std::getline(fIn,Line)){
        //
        // Unpack data line
        //
        std::istringstream s(Line);
        std::string field;
        std::vector<std::string> fd;
        //std::cout<<"Fields";
        Int_t nField = 0;
        while (std::getline(s, field,',')){
            //std::cout<<" #"<<nField<<"->"<<field;
            fd.push_back(field);
            nField++;
        }
        //std::cout<<std::endl;
        //
        // Select fibers in bundles
        //
        Int_t iBundle = -1;
        if(fd[4] == "CAL"){
            try{ iBundle = std::stoi(fd[6]);}
            catch (std::invalid_argument const& ex)
            {
                //std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
            }
        }
        if(iBundle >= 0){
            //std::cout<<"New Line: "<<Line<<std::endl;
            Board.push_back    (std::stoi(fd[0]));
            Disk.push_back     (std::stoi(fd[1]));
            Phi.push_back      (std::stoi(fd[2]));
            Channel.push_back  (std::stoi(fd[3]));
            Bundle.push_back   (std::stoi(fd[6]));
        }
        fd.clear();
    }
    fIn.close();
    //
    // Build pointer map
    //
    for(Int_t i=0; i<fNboard; i++){
        for(Int_t j=0; j<fNchann; j++)fBoardChToBundle[i][j] = -1;  // Initialize to -1
    }
    Int_t Ndat = (Int_t) Board.size();
    //std::cout<<"Board\tDisk\tPhi\tChan\tBundle"<<std::endl;
    for(Int_t i=0; i<Ndat; i++){
        //std::cout<<Board[i]<<"\t"<<Disk[i]<<"\t"
        //<<Phi[i]<<"\t"<<Channel[i]<<"\t"<<Bundle[i]<<std::endl;
        Int_t ib = Board[i];
        Int_t ic = Channel[i];
        fBoardChToBundle[ib][ic] = Bundle[i];
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
void LaserConf::FillPINhist(Int_t Opt)
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
                /*
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
                */
                Double_t BaseV1; Double_t BaseRMS;
                data.BaselineCalc(k, BaseV1, BaseRMS);
                fh_base[iDiode]->Fill(BaseV1);
                fh_bRMS[iDiode]->Fill(BaseRMS);
                fh_peak_bs[iDiode]->Fill(Pk0-BaseV1);
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
void LaserConf::PrintPINhist()
{
    //
    // Display two canvases per diode
    //
    fC = new TCanvas("fC","Global quantities",0,0,800,800);
    fC->Divide(2,1);
    fC->cd(1);
    fh_nHit->Draw();
    fC->cd(2);
    fh_nSamp->Draw();
    //
    // Canvases for optical table PINs
    fCnv[0] = new TCanvas("fCnv_0","Optical table before the FW",10,10,800,800);
    fCnv[1] = new TCanvas("fCnv_1","Optical table before the FW",20,20,800,800);
    fCnv[2] = new TCanvas("fCnv_2","Optical table after the FW", 30,30,800,800);
    fCnv[3] = new TCanvas("fCnv_3","Optical table after the FW", 40,40,800,800);
    //
    for(Int_t i=0; i<fNdiode; i++){
        if(i>3){
            TString CnvId = Form("fCnv_%d",i);
            TString CnvName = Form("Disk %d, Phi %d, Sphere %s",
                         fDisk[i], fPhi[i], fSphere[i].Data());
            fCnv[i] = new TCanvas(CnvId,CnvName,10*(i+1),10*(i+1),800,800);
        }
        fCnv[i]->Divide(2,2);
        fCnv[i]->cd(1);
        fh_base[i]->Draw();
        fCnv[i]->cd(2);
        fh_bRMS[i]->Draw();
        fCnv[i]->cd(3);
        fh_peak[i]->Draw();
        fCnv[i]->cd(4);
        fh_peak_bs[i]->Draw();
        //fh_PkInt[i]->Draw();
    }
}
//
// Bundle histogram filling and printing
//
// Fill them
void LaserConf::FillBundHist(Int_t Opt)
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
        //
        Int_t MinHits = 1000;   // Minimum number of hits to select laser events
        Double_t bNum[fNbundle];     // Number of fibers hit
        // Uncorrected
        Double_t bMean[fNbundle];    // Mean of peak values
        Double_t bMin [fNbundle];    // Minimum peak in bundle
        Double_t bMax [fNbundle];    // Maximum peak in bundle
        // Baseline subtracted
        Double_t bMean_b[fNbundle];    // Mean of peak values
        Double_t bMin_b [fNbundle];    // Minimum peak in bundle
        Double_t bMax_b [fNbundle];    // Maximum peak in bundle
        for(Int_t ibn=0; ibn<fNbundle; ibn++){
            bNum [ibn]  = 0.;
            bMean[ibn]  = 0.;
            bMin [ibn]  = 10000.;
            bMax [ibn]  = 0.;
            //
            bMean_b[ibn]  = 0.;
            bMin_b [ibn]  = 10000.;
            bMax_b [ibn]  = 0.;
        }
        if(Nhits>MinHits){          // Select laser events
            for(Int_t k=0; k<Nhits; k++){
                Int_t nBoard  = data.GetBoardID(k);    // Get board
                Int_t nChann  = data.GetChanID(k);     // Get Channel
                Int_t iBundle = fBoardChToBundle[nBoard][nChann];      // Get bundle
                //
                // Process PINs
                //

                //
                // Process bundles
                //
                if(iBundle >=0){
                    //std::cout<<"Event "<<i<<", Hit= "<<k<<", Board= "<<nBoard<<", Channel= "<<nChann
                    //<<", Bundle = "<<iBundle<<std::endl;
                    //
                    // Get baseline for subtraction
                    Double_t mBase; Double_t sBase;
                    data.BaselineCalc(k, mBase, sBase);
                    /*
                    Int_t nBase = 10;
                    Double_t BaseV1 = 0.0;  // Bealine mean value
                    Int_t Length = data.GetNofsamples(k);      // Wave length
                    Int_t *iWave = new Int_t[Length];
                    iWave = data.GetWaveData(k);
                    for(Int_t j=0; j<nBase; j++)BaseV1 += (Double_t)iWave[j];
                    BaseV1 *= 1./(Double_t) nBase;  // <Baseline>
                    //
                    delete [] iWave;
                    */
                    //
                    Double_t Pk0 = (Double_t) data.GetPeakval(k);
                    bNum[iBundle]++;
                    bMean  [iBundle] += Pk0;
                    bMean_b[iBundle] += Pk0-mBase;
                    if(Pk0 < bMin[iBundle]){
                        bMin  [iBundle] = Pk0;
                        bMin_b[iBundle] = Pk0-mBase;
                    }
                    if(Pk0 > bMax[iBundle]){
                        bMax  [iBundle] = Pk0;
                        bMax_b[iBundle] = Pk0-mBase;
                    }
                }
            } // end loop on hits
            for(Int_t ibn=0; ibn<fNbundle; ibn++){
                fhb_num  [ibn]->Fill(bNum  [ibn]);
                fhb_Min  [ibn]->Fill(bMin  [ibn]);
                fhb_Max  [ibn]->Fill(bMax  [ibn]);
                fhb_Minb [ibn]->Fill(bMin_b[ibn]);
                fhb_Maxb [ibn]->Fill(bMax_b[ibn]);
                if(bNum[ibn]>0.){
                    fhb_Mean [ibn]->Fill(bMean  [ibn]/bNum[ibn]);
                    fhb_Meanb[ibn]->Fill(bMean_b[ibn]/bNum[ibn]);
                }
            }
        } // End if on number of hits
    } // end main event loop
}
//
// Print them
void LaserConf::PrintBundHist()
{
    for(Int_t i=0; i<fNbundle; i++){
        // Canvases
        TString CbdlId = Form("fCbdl_%d",i);
        TString CbdlName = Form("Bundle #%d",i);
        fCbdl[i] = new TCanvas(CbdlId,CbdlName,10*(i+1),10*(i+1),800,800);
        fCbdl[i]->Divide(2,2);
        // Plots
        fCbdl[i]->cd(1);
        fhb_num [i]->Draw();
        fCbdl[i]->cd(2);
        fhb_Min [i]->SetLineColor(kGreen);
        fhb_Min [i]->Draw();
        fhb_Max [i]->SetLineColor(kRed);
        fhb_Max [i]->Draw("SAME");
        fhb_Mean[i]->SetLineColor(kBlack);
        fhb_Mean[i]->Draw("SAME");
        fCbdl[i]->cd(3);
        fhb_Minb [i]->SetLineColor(kGreen);
        fhb_Minb [i]->Draw();
        fhb_Maxb [i]->SetLineColor(kRed);
        fhb_Maxb [i]->Draw("SAME");
        fhb_Meanb[i]->SetLineColor(kBlack);
        fhb_Meanb[i]->Draw("SAME");
        //fCbdl[i]->cd(4);
    }
}
