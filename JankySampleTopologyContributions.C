#include <string>
#include <vector>

//FHCNumuCC0Pi0p
int FHCNumuCC0Pi_0p_Mom_NBin = 26;
double FHCNumuCC0Pi_0p_Mom_Bin[27] = {0., 200., 300., 350., 400., 450., 500., 550., 600., 650.,
                                      700., 750, 800., 850., 900., 950., 1000., 1100., 1200.,
                                      1300., 1500., 1750., 2000., 2500., 3000., 5000., 6000.};
int FHCNumuCC0Pi_0p_Cos_NBin = 25;
double FHCNumuCC0Pi_0p_Cos_Bin[26] = {0.4, 0.5, 0.6, 0.68, 0.72, 0.76, 0.82, 0.84, 0.86, 0.88,
                                      0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.955, 0.96, 0.965,
                                      0.97, 0.975,0.98, 0.985, 0.99, 0.995, 1.0};
//FHCNumuCC0PiNp
int FHCNumuCC0Pi_Np_Mom_NBin = 22;
double FHCNumuCC0Pi_Np_Mom_Bin[23] = {0., 250., 350., 400., 450., 500., 550., 600., 650., 700.,
                                      800., 900., 1000., 1100., 1200., 1300., 1500., 1600.,
                                      1750., 2000., 2750., 5000., 6000.};
int FHCNumuCC0Pi_Np_Cos_NBin = 16;
double FHCNumuCC0Pi_Np_Cos_Bin[17] = {0.45, 0.55, 0.65, 0.75, 0.8, 0.85, 0.88, 0.9, 0.92,
                                      0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.988, 1.0};
//FHCNumuCC1Pi
int FHCNumuCC1Pi_Mom_NBin = 17;
double FHCNumuCC1Pi_Mom_Bin[18] = {0., 300., 350., 400., 500., 600., 650., 700.,
                                   750., 800., 900., 1000., 1100., 1200., 1500.,
                                   2000., 5000., 6000.};
int FHCNumuCC1Pi_Cos_NBin = 16;
double FHCNumuCC1Pi_Cos_Bin[17] = {0.5, 0.6, 0.68, 0.74, 0.79, 0.85, 0.9, 0.91, 0.92, 0.93,
                                   0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1.0};
//FHCNumuCCOth
int FHCNumuCCOth_Mom_NBin = 14;
double FHCNumuCCOth_Mom_Bin[15] = {0., 350., 500., 600., 650., 700., 800., 900.,
                                   1000., 1150., 1250., 1500., 2000., 5000., 6000.};
int FHCNumuCCOth_Cos_NBin = 11;
double FHCNumuCCOth_Cos_Bin[12] = {0.5, 0.6, 0.7, 0.8, 0.85, 0.88, 0.9, 0.92, 0.94,
                                   0.96, 0.98, 1.0};
//FHCNumuCCPhoton
int FHCNumuCCPhoton_Mom_NBin = 20;
double FHCNumuCCPhoton_Mom_Bin[21] = {0., 300., 400., 500., 600., 650., 700., 750.,
                                      800., 900., 1000., 1100., 1250., 1500., 1600., 1750.,
                                      2000., 2500., 3000., 5000., 6000.};
int FHCNumuCCPhoton_Cos_NBin = 20;
double FHCNumuCCPhoton_Cos_Bin[21] = {0.5, 0.6, 0.7, 0.76, 0.8, 0.84, 0.86, 0.88, 0.89,
                                      0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97,
                                      0.98, 0.99, 0.995, 1.0};

void JankySampleTopologyContributions() {
	//gROOT->SetBatch();
	DrawingTools* draw = new DrawingTools("/home/t2k/aspeers/PROD7_validation/testing/MultiPiAnalysis_TEST.root");
	
	Experiment exp("nd280");
		DataSample* neut_4a = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P6AA_FHC_FGD1_default_settings.root");
		SampleGroup run4a_n("run4a_n");
		run4a_n.AddMCSample("magnet", neut_4a);
		exp.AddSampleGroup("run4a_n", run4a_n);

	//draw->SetStackFillStyle(3254); //No idea what this does
	
	float win_scale = 0.75;
	int n_wide(2);
	int n_high(2);
	
	//FGD1:
	draw->Draw(exp, "all","magnet", "selmu_mom",50, 0 , 6000,"topology_ccphoton","accum_level[][0]>8","","OVER");
	//draw->Draw(exp,"selmu_mom",FHCNumuCC0Pi_Np_Mom_NBin,FHCNumuCC0Pi_Np_Mom_Bin,"topology_ccphoton","accum_level[0][0][2]>8","","OVER");
	//draw->Draw(exp,"selmu_mom",FHCNumuCC1Pi_Mom_NBin,FHCNumuCC1Pi_Mom_Bin,"topology_ccphoton","accum_level[0][0][3]>7","","OVER");
	//draw->Draw(exp,"selmu_mom",FHCNumuCCOth_Mom_NBin,FHCNumuCCOth_Mom_Bin,"topology_ccphoton","accum_level[0][0][4]>7","","OVER");
	//draw->Draw(exp,"selmu_mom",FHCNumuCCPhoton_Mom_NBin,FHCNumuCCPhoton_Mom_Bin,"topology_ccphoton","accum_level[0][0][0]>6","","OVER");
	
	//FGD2:
	//draw->Draw(exp,"selmu_mom",FHCNumuCC0Pi_0p_Mom_NBin,FHCNumuCC0Pi_0p_Mom_Bin,"fgd2topology_ccphoton","accum_level[0][1][1]>8","","OVER");
	//draw->Draw(exp,"selmu_mom",FHCNumuCC0Pi_Np_Mom_NBin,FHCNumuCC0Pi_Np_Mom_Bin,"fgd2topology_ccphoton","accum_level[0][1][2]>8","","OVER");
	//draw->Draw(exp,"selmu_mom",FHCNumuCC1Pi_Mom_NBin,FHCNumuCC1Pi_Mom_Bin,"fgd2topology_ccphoton","accum_level[0][1][3]>7","","OVER");
	//draw->Draw(exp,"selmu_mom",FHCNumuCCOth_Mom_NBin,FHCNumuCCOth_Mom_Bin,"fgd2topology_ccphoton","accum_level[0][1][4]>7","","OVER");
	//draw->Draw(exp,"selmu_mom",FHCNumuCCPhoton_Mom_NBin,FHCNumuCCPhoton_Mom_Bin,"fgd2topology_ccphoton","accum_level[0][1][0]>6","","OVER");
	
	HistoStack* stack = NULL;
	stack = (HistoStack*)draw->GetLastStack();

	stack->Draw();
	
	TH1* CC0pi = stack->GetHisto1D(0);
	TH1* CC1pi = stack->GetHisto1D(1);
	TH1* CCOther = stack->GetHisto1D(2);
	TH1* CCPhoton = stack->GetHisto1D(3);
	TH1* BKG = stack->GetHisto1D(4);
	TH1* outFV = stack->GetHisto1D(5);
	
	double TotalIntegral = CC0pi->Integral(0, 27) + CC1pi->Integral(0, 27) + CCOther->Integral(0, 27) + CCPhoton->Integral(0, 27) + BKG->Integral(0, 27) + outFV->Integral(0, 27);
	
	cout << "Total Integral: " << TotalIntegral << std::endl
		<< "CC0pi Integral: " << CC0pi->Integral(0, 27) << ", " << 100*CC0pi->Integral(0, 27)/TotalIntegral << "%"  << std::endl
		<< "CC1pi Integral: " << CC1pi->Integral(0,27) << ", " << 100*CC1pi->Integral(0, 27)/TotalIntegral << "%" << std::endl
		<< "CCOther Integral: " << CCOther->Integral(0,27) << ", " << 100*CCOther->Integral(0, 27)/TotalIntegral << "%" << std::endl
		<< "CCPhoton Integral: " << CCPhoton->Integral(0,27) << ", " << 100*CCPhoton->Integral(0, 27)/TotalIntegral << "%" << std::endl
		<< "BKG Integral: " << BKG->Integral(0,27) << ", " << 100*BKG->Integral(0, 27)/TotalIntegral << "%" << std::endl
		<< "outFV Integral: " << outFV->Integral(0,27) << ", " << 100*outFV->Integral(0, 27)/TotalIntegral << "%" << std::endl;
	
}