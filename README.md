# Mu2E
Code development for Mu2E calorimeter studies

The following is included at present:
code/classes/Mu2Edata.cc class to unpack root data file information
code/SimplePlot.C   example on how to plot some data
code/WavePlot.C     example on display of waveforms
code/WavetoRoot.C   Fit waveform with spline and store results in root file
code/PlotFitData.C  Read stored fit results and plots them
//
Additional code to monitor PIN diode performance (handles also Art generated files)
code/LaserView.C
code/classes/LasrConf.cc
//
// Examples
//
Time fitting procedure:
=======================
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
//
Laser PIN diode monitor
=======================
->Description:
Plots baseline and its standard deviation, value, value baseline subtracted and value baseline subtracted and corrected for the mean of the two PIN diodes in the optical box before the filter wheel.
Plots the ratio of the two diodes in every sphere.
-> Instructions:
- Operate from main directory ~/Mu2E/Mu2E
- Input data files in ../data/FWscan
  example: ../data/FWscan/mc2_120719_FW03.root
ROOT>
ROOT>.L code/classes/Mu2Edata.cc+
ROOT>.L code/classes/LaserConf.cc+
ROOT>.L code/LaserView.C+
ROOT>LaserView("../data/FWscan/mc2_120719_FW03.root")

Laser bundle monitor
=======================
->Description:
Plots the number of fibers fired, the mean of all fibers, the lowest and the highest with and without baseline subtraction, and the distribution of all fiber values in each bondle.
After correction for laser fluctuations as in the diode monitor case, the values of all fibers and their mean in every bundle is also displayed.
The bundle means with and without correction are also fit with gaussians and mean values and standard deviations are printed for every bundle.

-> Instructions:
- Operate from main directory ~/Mu2E/Mu2E
- Input data files in ../data/FWscan
  example: ../data/FWscan/mc2_120719_FW03.root
ROOT>
ROOT>.L code/classes/Mu2Edata.cc+
ROOT>.L code/classes/LaserConf.cc+
ROOT>.L code/BundleView.C+
ROOT>BundleView("../data/FWscan/mc2_120719_FW03.root")
