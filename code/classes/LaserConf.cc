#include "LaserConf.h"
#include <TStyle.h>
#include <TAxis.h>
#include <TF1.h>
#include <TFitResult.h>
#include <TObjArray.h>
#include <TObjString.h>

LaserConf::LaserConf()
{
    //
    // Just to access configuration data
    //
    InitConf();
}
//
LaserConf::LaserConf(Mu2Edata *data)
{
    //
    fdata = data;
    //
    // Input file
    fName = fdata->GetFileName();
    std::cout<<"LaserConf initialized with file: "<<fName<<std::endl;
    //
    // Setup descriptions
    InitConf();
    //
    // Initialize board/chann to bundles
    TString BundleMap = "./data/BundleMap.csv";
    ReadBundle(BundleMap);
    //
    // Book general plots
    BookGenPlots();
    //
    // Get mean&sigma of each fiber/diode
    GetMeans();
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
    //
    // Printout configuration
    //
    std::cout<<"Current diode configuration:"<<std::endl;
    for(Int_t i=0; i<fNdiode; i++)std::cout<<fDescr[i]<<std::endl;
}
//
// General control histigrams
//
void LaserConf::BookGenPlots()
{
    //
    fh_nHit = new TH1D("fh_nHit","Number of hits",100,0.,4000.);
    fh_nSamp = new TH1D("fh_nSamp","Number of samples",850,0.,85000.);
    //
    fh_nHitLevt = new TH1D("fh_nHitLevt","Number of hits vs. laser event number",10000,0.5,10000.5);
    fh_PevtLevt = new TH1D("fh_PevtLevt","Processed event number vs Laser event number",10000,0.5,10000.5);
    fh_nEvtPevt = new TH1D("fh_nEvtPevt","Stored event number vs Processed event number",10000,0.5,100000.5);
}
//
// Book PIN and diode plots
//
void LaserConf::BookPINplots()
{
    //
    //==============================================================
    //      PIN plots
    //
    // Setup optical board histograms for PIN diodes
    //
    fh_base[0] = new TH1D("fh_base_0","Baseline FW00", 100, 1950., 2250.);
    fh_bRMS[0] = new TH1D("fh_bRMS_0","Baseline RMS FW00", 100, -5., 5.);
    fh_peak[0] = new TH1D("fh_peak_0","Peak value FW00",200, 2100.,4100.);
    fh_peak_bs[0] = new TH1D("fh_peak_bs_0","Peak value FW00 (subtracted)",210, 0.,2100.);
    fh_PkInt[0] = new TH1D("fh_PkInt_0","Peak interpolation FW00",100, 0., 1.);
    fh_PkCum[0] = new TH1D("fh_PkCum_0","Peak interp. cumulative FW00",100, 0.,1.);
    fh_PkRatio[0] = new TH1D("fh_PkRatio_0","Peak ratio FW00/FW01", 100, 0.5, 1.5);
    fh_PkRti[0]   = new TH1D("fh_PkRti_0","Peak over <FW laser>",400,0.,2.);
    fh_PkCor[0]   = new TH1D("fh_PkCor_0","Peak value FW00 (corrected)",210,0.,2100.);
    //
    fh_base[1] = new TH1D("fh_base_1","Baseline FW01", 100, 1950., 2250.);
    fh_bRMS[1] = new TH1D("fh_bRMS_1","Baseline RMS FW01", 100, -5., 5.);
    fh_peak[1] = new TH1D("fh_peak_1","Peak value FW01",200, 2100.,4100.);
    fh_peak_bs[1] = new TH1D("fh_peak_bs_1","Peak value FW01 (subtracted)",210, 0.,2100.);
    fh_PkInt[1] = new TH1D("fh_PkInt_1","Peak interpolation FW01",100, 0., 1.);
    fh_PkCum[1] = new TH1D("fh_PkCum_1","Peak interp. cumulative FW01",100, 0.,1.);
    fh_PkRti[1]   = new TH1D("fh_PkRti_1","Peak over <FW laser>",400,0.,2.);
    fh_PkCor[1]   = new TH1D("fh_PkCor_1","Peak value FW01 (corrected)",210,0.,2100.);
    //
    fh_base[2] = new TH1D("fh_base_2","Baseline FW10", 100, 1950., 2250.);
    fh_bRMS[2] = new TH1D("fh_bRMS_2","Baseline RMS FW10", 100, -5., 5.);
    fh_peak[2] = new TH1D("fh_peak_2","Peak value FW10",200, 2100.,4100.);
    fh_peak_bs[2] = new TH1D("fh_peak_bs_2","Peak value FW10 (subtracted)",210, 0.,2100.);
    fh_PkInt[2] = new TH1D("fh_PkInt_2","Peak interpolation FW10",100, 0., 1.);
    fh_PkCum[2] = new TH1D("fh_PkCum_2","Peak interp. cumulative FW10",100, 0.,1.);
    fh_PkRatio[1] = new TH1D("fh_PkRatio_1","Peak ratio FW10/FW11", 100, 0.5, 1.5);
    fh_PkRti[2]   = new TH1D("fh_PkRti_2","Peak over <FW laser>",400,0.,2.);
    fh_PkCor[2]   = new TH1D("fh_PkCor_2","Peak value FW10 (corrected)",210,0.,2100.);
    //
    fh_base[3] = new TH1D("fh_base_3","Baseline FW11", 100, 1950., 2250.);
    fh_bRMS[3] = new TH1D("fh_bRMS_3","Baseline RMS FW11", 100, -5., 5.);
    fh_peak[3] = new TH1D("fh_peak_3","Peak value FW11",200, 2100.,4100.);
    fh_peak_bs[3] = new TH1D("fh_peak_bs_3","Peak value FW11 (subtracted)",210, 0.,2100.);
    fh_PkInt[3] = new TH1D("fh_PkInt_3","Peak interpolation FW11",100, 0., 1.);
    fh_PkCum[3] = new TH1D("fh_PkCum_3","Peak interp. cumulative FW11",100, 0.,1.);
    fh_PkRti[3]   = new TH1D("fh_PkRti_3","Peak over <FW laser>",400,0.,2.);
    fh_PkCor[3]   = new TH1D("fh_PkCor_3","Peak value FW11 (corrected)",210,0.,2100.);
    //
    // Setup on detector histograms and canvases for on detector PIN diodes
    //
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
        TString hPkRtiID = Form("fh_PkRti_%d",i);
        TString hPkRtiTitle = Form("Peak over laser FW00/01 mean %d, channel %d",fBoard[i], fChann[i]);
        fh_PkRti[i] = new TH1D(hPkRtiID,hPkRtiTitle,400, 0.,2.);
        TString hPkCorID = Form("fh_PkCor_%d",i);
        TString hPkCorTitle = Form("Peak value (corrected) mean %d, channel %d",fBoard[i], fChann[i]);
        fh_PkCor[i] = new TH1D(hPkCorID,hPkCorTitle,210, 0.,2100.);
        //
        if(i%2 == 0){
            Int_t iSphere = i/2;
            TString hPkRatioID = Form("fh_PkRatio_%d",iSphere);
            TString hPkRatioTitle = Form("Peak ratio board %d-ch %d/board %d-ch %d",
                                         fBoard[i],fChann[i],fBoard[i+1],fChann[i+1]);
            fh_PkRatio[iSphere] = new TH1D(hPkRatioID,hPkRatioTitle, 100, 0.5, 1.5);
        }
    }
}
//
// Book undle plots
//
void LaserConf::BookBundlePlots()
{
    //
    //====================================================================================
    //  Bundle plots
    //
    for(Int_t i=0; i<fNbundle; i++){
        //
        // histogram IDs
        TString b_numID = Form("fhb_num_%d",i);
        //
        TString b_MeanID  = Form("fhb_Mean_%d",i);  // Uncorrected
        TString b_MinID  = Form("fhb_Min_%d",i);
        TString b_MaxID  = Form("fhb_Max_%d",i);
        //
        TString b_MeanIDb  = Form("fhb_Mean_b_%d",i);    // Baseline subtracted
        TString b_MinIDb  = Form("fhb_Min_b_%d",i);
        TString b_MaxIDb  = Form("fhb_Max_b_%d",i);
        TString b_FibreIDb  = Form("fhb_Fibreb_%d",i);
        TString b_FibreIDbc  = Form("fhb_Fibrebc_%d",i);
        //
        TString b_MeanIDc    = Form("fhb_Meanbc_%d",i);    // Laser corrected
        TString b_MeanRtiID  = Form("fh_MbRti_%d",i);
        // histogram titles
        TString b_numTit  = Form("Number of fibers fired in bundle %d",i);
        //
        TString b_MeanTit = Form("Mean of fired fibers in bundle %d",i);    // Uncorrected
        TString b_MinTit  = Form("Lowest  fired fiber  in bundle %d",i);
        TString b_MaxTit  = Form("Highest fired fiber  in bundle %d",i);
        //
        TString b_MeanTitb = Form("Mean of fired fibers (baseline subtracted) in bundle %d",i); // Baseline subtracted
        TString b_MinTitb  = Form("Lowest  fired fiber (baseline subtracted) in bundle %d",i);
        TString b_MaxTitb  = Form("Highest fired fiber (baseline subtracted) in bundle %d",i);
        TString b_FibreTitb = Form("All fired fibers (baseline subtracted) in bundle %d",i);
        TString b_MeanTitc    = Form("Laser corrected mean of bundle %d",i);    // Laser corrected
        TString b_MeanRtiTit  = Form("Ratio mean peak/laser in bundle %d",i);
        TString b_FibreTitbc = Form("All fired fibers (corrected) in bundle %d",i);
        // histogram allocation
        fhb_num [i] = new TH1D(b_numID,b_numTit,  200,   0., 200.);
        fhb_Mean[i] = new TH1D(b_MeanID,b_MeanTit,210,2000.,4100.); // Uncorrected
        fhb_Min [i] = new TH1D(b_MinID,b_MinTit,  210,2000.,4100.);
        fhb_Max [i] = new TH1D(b_MaxID,b_MaxTit,  210,2000.,4100.);
        //
        fhb_Meanb[i] = new TH1D(b_MeanIDb,b_MeanTitb,210,0.,2100.); // Baseline subtracted
        fhb_Minb [i] = new TH1D(b_MinIDb,b_MinTitb,  210,0.,2100.);
        fhb_Maxb [i] = new TH1D(b_MaxIDb,b_MaxTitb,  210,0.,2100.);
        fhb_Fibreb[i] = new TH1D(b_FibreIDb,b_FibreTitb,210,0.,2100.);
        //
        fh_MbRti[i] = new TH1D(b_MeanRtiID,b_MeanRtiTit,1000,0.,2.);    // Laser corrected
        fhb_Fibrebc[i] = new TH1D(b_FibreIDbc,b_FibreTitbc,210,0.,2100.);
        fhb_Meanbc[i] = new TH1D(b_MeanIDc, b_MeanTitc,210,0.,2100.);
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
    std::cout<<"LaserConf::ReadBundle: read bundle configuration file"<<std::endl;
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
// Get mean&sigma of each fiber&diode
void::LaserConf::GetMeans()
{
    //
    //
    // Initialize arrays
    for(Int_t ib=0; ib<fNboard; ib++){
        for(Int_t ic=0; ic<fNchann; ic++){
            fBoardChToMean  [ib][ic] = 0.0;     // Peak mean  associated to board/channel
            fBoardChToSigma [ib][ic] = 0.0;     // Peak sigma associated to board/channel
            fBoardChToMeanC [ib][ic] = 0.0;     // Peak mean  associated to board/channel q/L --> corrected
            fBoardChToSigmaC[ib][ic] = 0.0;     // Peak sigma associated to board/channel (q/L)^2 --> corrected
            fBoardChToNum   [ib][ic] = 0.0;     // Nr. of events associated to board/channel
            fBoardChToNumC  [ib][ic] = 0.0;     // Nr. of events associated to board/channel with correction
            // Mark non existent channels
            Int_t nBundle = fBoardChToBundle[ib][ic];
            Int_t nDiode  = GetDiode(ib, ic);
            if(nBundle < 0 && nDiode < 0){
                fBoardChToMean  [ib][ic] = -1.0;
                fBoardChToMeanC [ib][ic] = -1.0;
                fBoardChToNum   [ib][ic] = -1.0;
                fBoardChToNumC  [ib][ic] = -1.0;
            }
        }
    }
    //
    // Main event loop
    //
    TTree *tree = fdata->GetTree();
    Long64_t nentries = (Int_t) tree->GetEntries();
    cout<<"Nentries= "<<nentries<<endl;
    Int_t LaserEvt = 0;                 // Laser event number
    for (Long64_t i = 0; i <nentries; ++i) {
        tree->GetEntry(i);    // Load new entry
        Int_t Nhits = fdata->GetNhits();
        Int_t Nsamp = fdata->GetNsamples();
        fh_nHit ->Fill((Double_t)Nhits);        // Fill general histograms
        fh_nSamp->Fill((Double_t)Nsamp);
        fh_nHitLevt->Fill((Double_t)LaserEvt,(Double_t)Nhits);
        fh_PevtLevt->Fill((Double_t)LaserEvt,(Double_t)i);
        fh_nEvtPevt->Fill((Double_t)i,(Double_t)fdata->GetNevt());
        //
        if(i%5000 == 0)std::cout<<"LaserConf::GetMeans: nev="<<i<<", Nhit= "<<Nhits
            <<", Nsamp= "<<Nsamp<<std::endl;
        //
        Int_t MinHits = 2350;   // Minimum number of hits to select laser events
        Int_t MaxHits = 2600;   // Maximum number of hits to select laser events
        if(Nhits>MinHits && Nhits<MaxHits){      // Laser event
            LaserEvt++;         // Laser event number
            Double_t meanD = 0.0;                        // Initialize mean of box PINs
            Int_t NdR = GetPINref(Nhits, meanD);
            for(Int_t k=0; k<Nhits; k++){      // Scan hits
                Int_t nBoard  = fdata->GetBoardID(k);    // Get board
                Int_t nChann  = fdata->GetChanID(k);     // Get Channel
                //
                // Get baseline for subtraction
                Double_t mBase; Double_t sBase;
                fdata->BaselineCalc(k, mBase, sBase);
                Double_t pk = (Double_t) fdata->GetPeakval(k)-mBase;  // Get peak value
                //
                fBoardChToNum   [nBoard][nChann]++;          // Increment nr events detected
                fBoardChToMean  [nBoard][nChann] += pk;      // Increment peak sum
                fBoardChToSigma [nBoard][nChann] += pk*pk;   // Increment peak^2 sum
                //
                if(NdR > 0){
                    Double_t pkR = pk/meanD;
                    fBoardChToNumC  [nBoard][nChann]++;          // Increment nr events detected w/ correction
                    fBoardChToMeanC [nBoard][nChann] += pkR;     // Increment peak corrected sum
                    fBoardChToSigmaC[nBoard][nChann] += pkR*pkR; // Increment peak^2 corrected sum
                }
                //
            } // End loop on hits
        }
    } // End loop on events
    //
    // Reference mean is mean of diodes 0 and 1
    //
    Int_t B0 = fBoard[0];   // Board of PIN 0
    Int_t B1 = fBoard[1];   // Board of PIN 1
    Int_t C0 = fChann[0];   // Channel of PIN 0
    Int_t C1 = fChann[1];   // Channel of PIN 1
    //
    Double_t Nevt = TMath::Max(fBoardChToNum[B0][C0],fBoardChToNum[B1][C1]);
    fRefMean = 0.5*(fBoardChToMean[B0][C0]+fBoardChToMean[B1][C1])/Nevt;
    //
    // Means and sigmas
    //
    for(Int_t ib=0; ib<fNboard; ib++){
        for(Int_t ic=0; ic<fNchann; ic++){
            // No laser correction
            if(fBoardChToNum[ib][ic] > 0.0){
                fBoardChToMean[ib][ic] /= fBoardChToNum[ib][ic];
                Double_t x2 = fBoardChToSigma[ib][ic]/fBoardChToNum[ib][ic];
                fBoardChToSigma [ib][ic] = TMath::Sqrt(x2-TMath::Power(fBoardChToMean[ib][ic],2));
            }
            // with laser correction
            if(fBoardChToNumC[ib][ic] > 0.0){
                fBoardChToMeanC[ib][ic] /= fBoardChToNumC[ib][ic];
                Double_t x2 = fBoardChToSigmaC[ib][ic]/fBoardChToNumC[ib][ic];
                fBoardChToSigmaC[ib][ic]  = TMath::Sqrt(x2-TMath::Power(fBoardChToMeanC[ib][ic],2));
                fBoardChToMeanC [ib][ic] *= fRefMean;
                fBoardChToSigmaC[ib][ic] *= fRefMean;
            }
        }
    }
}
//
// Print means in Excel .csv files with same name.
void LaserConf::PrintMeans()
{
    //
    // Make output name from input name.
    //
    TObjArray* tokens0 = fName.Tokenize(".");
    TString name0 = ((TObjString*)tokens0->At(0))->String();
    delete tokens0;
    TObjArray* tokens = name0.Tokenize("/");
    Int_t last = tokens->GetEntries()-1;
    TString name = ((TObjString*)tokens->At(last))->String();
    delete tokens;
    TString ExName = "./data/"+name+".csv";
    std::cout<<"LaserConf::PrintMeans: Found "<<name<<" writing to "<<ExName<<std::endl;
    //
    // Open file for output
    //
    std::ofstream OutFile;
    OutFile.open (ExName.Data(), std::ofstream::out);
    //
    // Header line
    TString Header = "Board,Channel,Mean,Mean Corr., Sigma,Sigma Corr.,Count,Count Corr.,Bundle,Diode";
    OutFile<<Header<<std::endl;
    for(Int_t ib=0; ib<fNboard; ib++){             // Board loop
        for(Int_t ic=0; ic<fNchann; ic++){          // Channel loop
            if(fBoardChToBundle[ib][ic] >= 0){    // if channel exists in bundle
                TString line = Form("%d,%d,%.2f,%.2f,%.2f,%.2f,%.0f,%.0f,%d",
                                    ib,ic,fBoardChToMean[ib][ic],fBoardChToMeanC[ib][ic],
                                    fBoardChToSigma[ib][ic],fBoardChToSigmaC[ib][ic],
                                    fBoardChToNum[ib][ic],fBoardChToNumC[ib][ic],fBoardChToBundle[ib][ic]);
                OutFile<<line<<std::endl;
            }else {
                if(GetDiode(ib, ic) >= 0){
                    TString lineD = Form("%d,%d,%.2f,%.2f,%.2f,%.2f,%.0f,%.0f,,%d",
                                    ib,ic,fBoardChToMean[ib][ic],fBoardChToMeanC[ib][ic],
                                    fBoardChToSigma[ib][ic],fBoardChToSigmaC[ib][ic],
                                    fBoardChToNum[ib][ic],fBoardChToNumC[ib][ic],GetDiode(ib,ic));
                    OutFile<<lineD<<std::endl;
                }
            }// End if channel exists
        }   // End channel loop
    }   // End board loop
    //
    OutFile.close();
}
//
// Print general histograms
void LaserConf::PrintGenPlots()
{
    //
    fC = new TCanvas("fC","Global quantities",0,0,800,800);
    fC->Divide(3,2);
    fC->cd(1);
    fh_nHit->Draw();
    fC->cd(2);
    fh_nSamp->Draw();
    fC->cd(3);
    fh_PevtLevt->Draw("HIST");
    fC->cd(5);
    fh_nHitLevt->Draw("HIST");
    fC->cd(6);
    fh_nEvtPevt->Draw("HIST");
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
// Get mean of PIN diodes before the FW for calibration
//
Double_t LaserConf::GetPINref(Int_t Nhits, Double_t &meanD)
{
    //
    // Get mean of reference diodes first
    Double_t NrD = 0;
    meanD = 0.0;
    for(Int_t k=0; k<Nhits; k++){
        Int_t nBoard  = fdata->GetBoardID(k);    // Get board
        Int_t nChann  = fdata->GetChanID(k);     // Get Channel
        //
        // Process PINs
        //
        Int_t iDiode = GetDiode(nBoard, nChann);      // Get pin diode
        if(iDiode == 0 || iDiode == 1){
            NrD++;
            Double_t mBase; Double_t sBase;
            fdata->BaselineCalc(k, mBase, sBase);
            meanD += (Double_t) fdata->GetPeakval(k)-mBase;
        }
        if(NrD >= 2) break;
    }
    if(NrD > 0) meanD = meanD/NrD;
    //
    return NrD;
}
//
// Fill histograms
//
void LaserConf::FillPINhist()
{
    //
    // Book PIN/Diode plots
    BookPINplots();
    //
    //
    // Main event loop
    //
    TTree *tree = fdata->GetTree();
    Long64_t nentries = (Int_t) tree->GetEntries();
    cout<<"LaserConf::FillPINhist: Nentries= "<<nentries<<endl;
    for (Long64_t i = 0; i <nentries; ++i) {
        tree->GetEntry(i);    // Load new entry
        Int_t Nhits = fdata->GetNhits();
        Int_t Nsamp = fdata->GetNsamples();
        if(i%1000 == 0)std::cout<<"LasrConf::FillPINhist: nev="<<i<<", Nhit= "<<Nhits
            <<", Nsamp= "<<Nsamp<<std::endl;
        TVectorD Peak(fNdiode); Peak.Zero();    // Store peak values
        TVectorD PeakB(fNdiode); PeakB.Zero();  // Store peak values (subtracted)
        //
        // Get laser reference correction
        Double_t meanD = 0.;    // Mean of diodes before FW
        Double_t NrD   = 0.;    // Nr. of found diodes before the FW
        NrD = GetPINref(Nhits, meanD);
        //
        // Main loop on hits
        for(Int_t k=0; k<Nhits; k++){
            Int_t nBoard = fdata->GetBoardID(k);            // Get board
            Int_t nChann = fdata->GetChanID(k);             // Get Channel
            Int_t iDiode = GetDiode(nBoard, nChann);        // Get pin diode
            Int_t Sphere = -1;
            if(iDiode >= 0){
                // Found diode
                //std::cout<<"Hit= "<<k<<", Board= "<<nBoard<<", Channel= "<<nChann
                //<<", Diode = "<<iDiode<<std::endl;
                Sphere = iDiode/2;   // Get Sphere
                Double_t Pk0 = (Double_t) fdata->GetPeakval(k);
                Peak(iDiode)  = Pk0;    // Store peak value
                Int_t tMax   = fdata->GetPeakpos(k);                // Peak position
                fh_peak[iDiode]->Fill(Pk0);
                //
                Double_t BaseV1; Double_t BaseRMS;
                fdata->BaselineCalc(k, BaseV1, BaseRMS);
                PeakB(iDiode) = Pk0-BaseV1;
                fh_base[iDiode]->Fill(BaseV1);
                fh_bRMS[iDiode]->Fill(BaseRMS);
                fh_peak_bs[iDiode]->Fill(Pk0-BaseV1);
                //
                // Get waveform data
                Int_t First  = fdata->GetFirstsample(k);     // Wave start
                Int_t Length = fdata->GetNofsamples(k);      // Wave length
                //
                // Peak interpolation
                Double_t PkMin = (Double_t) fdata->GetADC(First + tMax-1);
                Double_t PkMax = (Double_t) fdata->GetADC(First + tMax+1);
                Double_t PkInt = 2.*TMath::ATan((Pk0-PkMin)/(Pk0-PkMax))/TMath::Pi();
                fh_PkInt[iDiode]->Fill(PkInt);
                //
            }  // end if(iDiode) >= 0)
        }   // end hit loop
        //std::cout<<"End of hit loop"<<std::endl;
        //
        //
        // Fill peak ratios in same sphere if available and plot correction ratios
        Int_t iSphere = 0;
        // Peak over box laser
        //
        for(Int_t iD=0; iD<fNdiode; iD++){
            if(meanD>0.){
                Double_t R = PeakB(iD)/meanD;
                //std::cout<<"NrD= "<<NrD<<", MeanD = "<<meanD<<", R= "<<R<<std::endl;
                if(PeakB(iD)>0.){
                    fh_PkRti[iD]->Fill(R);
                    fh_PkCor[iD]->Fill(PeakB(iD)*fRefMean/meanD);
                }
            }
            if(iD%2 == 0){
                if(Peak(iD)*Peak(iD+1)>0.)fh_PkRatio[iSphere]->Fill(PeakB(iD)/PeakB(iD+1));
                iSphere++;
            }
        }
        //std::cout<<"End event "<<i<<std::endl;
    } // end event loop
    //std::cout<<"End event loop"<<std::endl;
}
//
// Laser correction without re-running over data
// Currently NOT used
//
void LaserConf::LaserCorrection(TH1D *hRatio, TH1D *hPeakBs, TH1D *hCorr){
        //
        // Correct peak histogram for laser fluctuations
        // while maintaining the same mean
        // Input:
        //      hRatio   = plot of peak/mean FW00/FE01
        //      hPeak_bs = plot of peak baseline subtracted
        //      hCorr    = plot of peak corrected for laser fluctuations
        //
        Int_t binR = hRatio->GetNbinsX();       // # bin in ratio histogram
        //Int_t binC = fh_PkCor[i]->GetNbinsX();
        Double_t meanQ = hPeakBs->GetMean();    // Uncorrected peak mean
        Double_t meanR = hRatio ->GetMean();    // Mean of ratio histogram
        TAxis *R_Axis  = hRatio ->GetXaxis();
        for(Int_t k=1; k<=binR; k++){
            Double_t Cont = (Double_t) hRatio->GetBinContent(k);
            Double_t xR = R_Axis->GetBinCenter(k);
            Double_t xQcor = xR*meanQ/meanR;
            hCorr->Fill(xQcor, Cont);
        }
}
//
// Display histograms
//
void LaserConf::PrintPINhist(Bool_t Prt)
{
    //
    // Display two canvases per diode
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
        gStyle->SetOptStat(111111);
        fCnv[i]->Divide(2,2);
        fCnv[i]->cd(1);
        fh_base[i]->Draw();
        fCnv[i]->cd(2);
        fh_bRMS[i]->Draw();
        fCnv[i]->cd(3);
        fh_peak[i]->Draw();
        fCnv[i]->cd(4);
        //
        // Build corrected histogram
        //LaserCorrection(fh_PkRti[i], fh_peak_bs[i], fh_PkCor[i]);
        fh_PkCor[i]->SetLineColor(kRed);
        //fh_PkRti[i]->Draw();
        fh_PkCor[i]->Draw("HIST");
        fh_peak_bs[i]->Draw("SAME");
    }
    //
    // Display ratio of diodes in each sphere
    //
    TCanvas *Csph0 = new TCanvas("Csph0","First 4 spheres",300,300,900,900);
    Csph0->Divide(2,2);
    for(Int_t i=0; i<4; i++){
        Csph0->cd(i+1);
        fh_PkRatio[i]->Draw();
    }
    TCanvas *Csph1 = new TCanvas("Csph1","Spheres 5 to 8 ",330,330,900,900);
    Csph1->Divide(2,2);
    for(Int_t i=4; i<8; i++){
        Csph1->cd(i-3);
        fh_PkRatio[i]->Draw();
    }
    TCanvas *Csph2 = new TCanvas("Csph2","Last 2 spheres         ",360,360,900,600);
    Csph2->Divide(2,1);
    for(Int_t i=8; i<10; i++){
        Csph2->cd(i-7);
        fh_PkRatio[i]->Draw();
    }
    //
    // Print all canvases if Prt is set
    //
    if(Prt)TCanvas::SaveAll();
}
//
//===================================================================================
//
// Bundle histogram filling and printing
//
// Fill them
void LaserConf::FillBundHist()
{
    //
    // Book bundle plots
    BookBundlePlots();
    //
    //
    // Main event loop
    //
    TTree *tree = fdata->GetTree();
    Long64_t nentries = (Int_t) tree->GetEntries();
    cout<<"LaserConf::FillBundHist: Nentries= "<<nentries<<endl;
    for (Long64_t i = 0; i <nentries; ++i) {
        tree->GetEntry(i);    // Load new entry
        Int_t Nhits = fdata->GetNhits();
        Int_t Nsamp = fdata->GetNsamples();
        if(i%1000 == 0)std::cout<<"LaserConf::FillBundHist: nev="<<i<<", Nhit= "<<Nhits
            <<", Nsamp= "<<Nsamp<<std::endl;
        //
        Int_t MinHits = 1000;   // Minimum number of hits to select laser events
        Double_t bNum[fNbundle];     // Number of fibers hit
        // Uncorrected
        Double_t bMean[fNbundle];    // Mean of peak values
        Double_t bMin [fNbundle];    // Minimum peak in bundle
        Double_t bMax [fNbundle];    // Maximum peak in bundle
        // Baseline subtracted
        Double_t bMean_b [fNbundle];    // Mean of peak values
        Double_t bMean_bc[fNbundle];    // Mean of peak values (corrected)
        Double_t bMin_b  [fNbundle];    // Minimum peak in bundle
        Double_t bMax_b  [fNbundle];    // Maximum peak in bundle
        for(Int_t ibn=0; ibn<fNbundle; ibn++){
            bNum [ibn]  = 0.;
            bMean[ibn]  = 0.;
            bMin [ibn]  = 10000.;
            bMax [ibn]  = 0.;
            //
            bMean_b [ibn]  = 0.;
            bMean_bc[ibn]  = 0.;
            bMin_b  [ibn]  = 10000.;
            bMax_b  [ibn]  = 0.;
        }
        Double_t meanD = 0.;    // Mean of diodes before FW
        Double_t NrD   = 0.;    // Nr. of found diodes before the FW
        //
        if(Nhits>MinHits){          // Select laser events
            //
            // Get mean of reference diodes first
            NrD = GetPINref(Nhits, meanD);
            //
            // then deal with all bundles
            for(Int_t k=0; k<Nhits; k++){
                Int_t nBoard  = fdata->GetBoardID(k);    // Get board
                Int_t nChann  = fdata->GetChanID(k);     // Get Channel
                Int_t iBundle = fBoardChToBundle[nBoard][nChann];      // Get bundle
                //
                // Process bundles
                //
                if(iBundle >=0){
                    //
                    // Get baseline for subtraction
                    Double_t mBase; Double_t sBase;
                    fdata->BaselineCalc(k, mBase, sBase);
                    //
                    Double_t Pk0 = (Double_t) fdata->GetPeakval(k);
                    fhb_Fibreb [iBundle]->Fill(Pk0-mBase);
                    if(meanD> 0.)fhb_Fibrebc[iBundle]->Fill((Pk0-mBase)*fRefMean/meanD);

                    bNum[iBundle]++;
                    bMean   [iBundle] += Pk0;
                    bMean_b [iBundle] += Pk0-mBase;
                    if(meanD>0.)bMean_bc[iBundle] += (Pk0-mBase)*fRefMean/meanD;
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
            //cout<<"FillBundle: end loop on hits"<<endl;
            //
            for(Int_t ibn=0; ibn<fNbundle; ibn++){
                fhb_num  [ibn]->Fill(bNum  [ibn]);
                fhb_Min  [ibn]->Fill(bMin  [ibn]);
                fhb_Max  [ibn]->Fill(bMax  [ibn]);
                fhb_Minb [ibn]->Fill(bMin_b[ibn]);
                fhb_Maxb [ibn]->Fill(bMax_b[ibn]);
                if(bNum[ibn]>0.){
                    Double_t Mean = bMean_b[ibn]/bNum[ibn];
                    if(NrD>0.){
                        Double_t Rti = Mean/meanD;
                        fh_MbRti[ibn]->Fill(Rti);
                        fhb_Meanbc[ibn]->Fill(bMean_bc[ibn]/bNum[ibn]);
                    }
                    fhb_Mean  [ibn]->Fill(bMean   [ibn]/bNum[ibn]);
                    fhb_Meanb [ibn]->Fill(bMean_b [ibn]/bNum[ibn]);
                }
            }
        } // End if on number of hits
    } // end main event loop
}
//
// Print them
void LaserConf::PrintBundHist(Bool_t Prt)
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
        fhb_Max [i]->SetLineColor(kMagenta);
        fhb_Max [i]->Draw("SAME");
        fhb_Mean[i]->SetLineColor(kBlack);
        fhb_Mean[i]->Draw("SAME");
        fCbdl[i]->cd(3);
        gStyle->SetOptFit();
        //LaserCorrection(fh_MbRti[i], fhb_Meanb[i], fh_MbCor[i]);
        fhb_Meanbc[i]->SetLineColor(kRed);
        fhb_Meanbc[i]->Draw();
        fhb_Meanb[i]->SetLineColor(kBlack);
        fhb_Meanb[i]->Draw("SAME");
        fhb_Minb [i]->SetLineColor(kGreen);
        fhb_Minb [i]->Draw("SAME");
        fhb_Maxb [i]->SetLineColor(kMagenta);
        fhb_Maxb [i]->Draw("SAME");
        fCbdl[i]->cd(4);
        fhb_Fibreb [i]->SetLineColor(kBlue);
        fhb_Fibrebc[i]->SetLineColor(kRed);
        fhb_Fibrebc[i]->Draw();
        fhb_Fibreb [i]->Draw("SAME");
    }
    //
    // Printout mean values of fit
    //
    std::cout<<"Bundle #\tPeak mean\tSigma\tMean Corr.\tSigma Corr."<<std::endl;
    for(Int_t i=0; i<fNbundle; i++){
        TFitResultPtr r = fhb_Meanb[i]->Fit("gaus","SQN");
        Double_t mean = r->Parameter(1);
        Double_t sigma = r->Parameter(2);
        TFitResultPtr rc = fhb_Meanbc[i]->Fit("gaus","SQN");
        Double_t meanc = rc->Parameter(1);
        Double_t sigmac = rc->Parameter(2);
        std::cout<<"\t"<<i<<"\t"<<mean<<"\t\t"<<sigma
        <<"\t\t"<<meanc<<"\t\t"<<sigmac<<std::endl;
    }
    //
    // Printout all canvases if Prt is set
    //
    if(Prt)TCanvas::SaveAll();
}
