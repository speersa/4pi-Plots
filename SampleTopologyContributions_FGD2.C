#include <string>
#include <vector>
	
void SampleTopologyContributions_FGD2() {
	gROOT->SetBatch();
	DrawingTools* draw = new DrawingTools("/home/t2k/aspeers/PROD7_validation/testing/MultiPiAnalysis_TEST.root");

	//DataSample mc("/data/aspeers/4pi_Selection/mcp/microTrees/P7_V12_FHC_length_fix_FGD2_MipEMGT0.root");
	DataSample mc("/data/aspeers/4pi_Selection/mcp/microTrees/P6AA_FHC_FGD2_default_settings_OFFICIAL.root");
	
	cout << std::endl <<  "CC0pi0p Fwd" << std::endl;
	draw->PrintPurities(mc, "fgd2topology_ccphoton", "accum_level[0][1][0]>8");
	
	cout << std::endl <<  "CC0piNp Fwd" << std::endl;
	draw->PrintPurities(mc, "fgd2topology_ccphoton", "accum_level[0][1][1]>8");
	
	cout << std::endl << "CC0pi0p Bwd" << std::endl;
	draw->PrintPurities(mc, "fgd2topology_ccphoton", "accum_level[0][1][2]>8");
	
	cout << std::endl << "CC0piNp Bwd" << std::endl;
	draw->PrintPurities(mc, "fgd2topology_ccphoton", "accum_level[0][1][3]>8");
	
	cout << std::endl << "CC0pi0p HAFwd" << std::endl;
	draw->PrintPurities(mc, "fgd2topology_ccphoton", "accum_level[0][1][4]>8");
	
	cout << std::endl << "CC0piNp HAFwd" << std::endl;
	draw->PrintPurities(mc, "fgd2topology_ccphoton", "accum_level[0][1][5]>8");
	
	cout << std::endl << "CC0pi0p HABwd" << std::endl;
	draw->PrintPurities(mc, "fgd2topology_ccphoton", "accum_level[0][1][6]>8");
	
	cout << std::endl << "CC0piNp HABwd" << std::endl;
	draw->PrintPurities(mc, "fgd2topology_ccphoton", "accum_level[0][1][7]>8");
	
	cout << std::endl << "CC1pi" << std::endl;
	draw->PrintPurities(mc, "fgd2topology_ccphoton", "accum_level[0][1][8]>7");
	
	cout << std::endl << "CC1pi HAFwd" << std::endl;
	draw->PrintPurities(mc, "fgd2topology_ccphoton", "accum_level[0][1][9]>7");
	
	cout << std::endl << "CCOther" << std::endl;
	draw->PrintPurities(mc, "fgd2topology_ccphoton", "accum_level[0][1][10]>7");
	
	cout << std::endl << "CC-Photon" << std::endl;
	draw->PrintPurities(mc, "fgd2topology_ccphoton", "accum_level[0][1][11]>6");	
	
	/*
	cout << std::endl <<  "CC0pi0p" << std::endl;
	draw->PrintPurities(mc, "fgd2reaction", "accum_level[0][1][1]>8");
	
	cout << std::endl << "CC0piNp" << std::endl;
	draw->PrintPurities(mc, "fgd2reaction", "accum_level[0][1][2]>8");
	
	cout << std::endl << "CC1pi" << std::endl;
	draw->PrintPurities(mc, "fgd2reaction", "accum_level[0][1][3]>7");
	
	cout << std::endl << "CCOther" << std::endl;
	draw->PrintPurities(mc, "fgd2reaction", "accum_level[0][1][4]>7");
	
	cout << std::endl << "CC-Photon" << std::endl;
	draw->PrintPurities(mc, "fgd2reaction", "accum_level[0][1][0]>6");
	*/
}