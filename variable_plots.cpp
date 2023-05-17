#include <string>
#include <vector>

void variable_plots(){
	
	gROOT->SetBatch();	
	
	DrawingTools* draw = new DrawingTools("/data/aspeers/4pi_Selection/mcp/microTrees/P7_V12_FHC_FGD1_default_settings.root",4); 
	
	Experiment exp("nd280");

	//DataSample* prod_7 = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P6AA_FHC_FGD1_default_settings.root");
	DataSample* prod_7 = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P7_V12_FHC_FGD1_default_settings.root");
    SampleGroup p_7("p_7");
    p_7.AddMCSample("magnet", prod_7);
	//exp.AddSampleGroup("p_7", p_7);
	
	float win_scale = 0.75;
    int n_wide(2);
    int n_high(2);
	
	TCanvas* canvas = new TCanvas("canvas", "canvas", 750*n_wide*win_scale, 500*n_high*win_scale);
	canvas->Print("Variable Plots.pdf[");
	
	draw->SetTitle("P6AA");
	draw->SetTitleX("Length");
	draw->Draw(default,"selmu_ecal_length",50,-50,1000,"topology_ccphoton","accum_level[][]>7");
	//histo=(TH1D*)draw->GetLastHisto();
	//histo->SetTitle("P6AA");
	canvas->Print("Variable Plots.pdf");
	
	draw->SetTitleX("EMenergy");
	draw->Draw(default,"selmu_ecal_EMenergy",50,0,1000,"topology_ccphoton","accum_level[][]>7");
	canvas->Print("Variable Plots.pdf");
	
	draw->SetTitleX("mipem");
	draw->Draw(default,"selmu_ecal_mipem",50,-100,100,"topology_ccphoton","accum_level[][]>7");
	canvas->Print("Variable Plots.pdf");
	
	canvas->Print("Variable Plots.pdf]");
}