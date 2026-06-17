# Mu2E
Code development for Mu2E calorimeter studies

The following is included at present:
code/classes/Mu2Edata.cc class to unpack root data file information
code/SimplePlot.C   example on how to plot some data
code/WavePlot.C     example on display of waveforms
code/WavetoRoot.C   Fit waveform with spline and store results in root file
code/PlotFitData.C  Read stored fit results and plots them

Time fitting procedure:
- Operate from main directory ~/Mu2E/Mu2E
- Input data files in ../data/timing
  example: ../data/timing/caloDTC2_Laser_ROC_0503_D1P1F2_fw06.root
- Output files in operating directory ~/Mu2E/Mu2E
  example: ~/Mu2E/Mu2E/Fit_D1P1F2_fw06.root
- Use just one spline to fit
  extract from spline file ../data/splines/laser_splines_caloDTC2_Laser_ROC_0503_D1P0F1_fw04.root
    // Select spline for board 160/channel 4
    TString Spline_Name = "spline_160_4";
    // Load spline
    fTemplate_spline = (TSpline3*)template_file.Get(Spline_Name.Data());
1) Generate rootple with fits
ROOT>
ROOT>.L code/classes/Mu2Edata.cc+
ROOT>.L code/WaveToRoot.C+
ROOT>WaveToRoot("InputFile.root","OutputFile.root")
example:
ROOT>WaveToRoot("../data/timing/caloDTC2_Laser_ROC_0503_D1P1F2_fw06.root","Fit_D1P1F2_fw06.root")
2) Plot results
ROOT>.L code/PlotFitData.C+
ROOT>PlotFitData("OutputFile.root")
example:
ROOT>PlotFitData("Fit_D1P1F2_fw06.root")
