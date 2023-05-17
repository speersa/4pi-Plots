#include <string>
#include <vector>
#include <vector>

void NEW_fourpi_plots(){
	
	//gROOT->SetBatch(); //Stops it from spamming windows when drawing
	DrawingTools draw("/home/t2k/aspeers/PROD7_validation/testing/MultiPiAnalysis_TEST.root",4); //Initialises DrawingTools with a random .root file
	
	// Create an experiment with name "nd280"
    Experiment exp("nd280");

	DataSample* prod_7 = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P7_V12_FHC_length_fix_default_settings.root");
    SampleGroup p_7("p_7");
    p_7.AddMCSample("magnet", prod_7);
    exp.AddSampleGroup("p_7", p_7); 

	float win_scale = 0.75;
    int n_wide(2);
    int n_high(2);
	
	TCanvas* cCC0pi = new TCanvas("cCC0pi", "cCC0pi", 500*n_wide*win_scale, 400*n_high*win_scale);
	draw.SetTitle("CC0#pi");
	draw.SetTitleX("muon candidate momentum (MeV/c)"); 
	draw.SetLegendPos("tr");
	draw.Draw(exp,"all","selmu_mom",50,0,5000,"topology_ccphoton","accum_level[][1]>8","","OVER");
	cCC0pi->SaveAs("CC0Pi.png"); 
	
}