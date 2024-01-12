#include <string>
#include <vector>

void fourpi_plots_entries() {
	
    gROOT->SetBatch(); //Stops it from spamming windows when drawing
	DrawingTools* draw = new DrawingTools("/home/t2k/aspeers/PROD7_validation/testing/MultiPiAnalysis_TEST.root"); //Initialises DrawingTools with a random .root file
	//draw->SetStackFillStyle(3254);

	// Create an experiment with name "nd280"
    Experiment exp("nd280");

	DataSample* prod_7 = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P7_V12_FHC_HL3.11_FHC.root");
	//DataSample* prod_7 = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P6AA_FHC_FGD1_default_settings.root");
    SampleGroup p_7("p_7");
    p_7.AddMCSample("magnet", prod_7);
	exp.AddSampleGroup("p_7", p_7);
	
	DataSample* prod_6 = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P6AA_FHC_FGD1_default_settings_OFFICIAL.root");
    p_7.AddDataSample(prod_6);
    exp.AddSampleGroup("p_7", p_7); 
	
	//Create a seperate experiment for eff&pur for P6
	Experiment p6("nd280_p6");
  
	DataSample* P6_4a = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P6AA_FHC_FGD1_default_settings_OFFICIAL.root");
	SampleGroup run4a_p6("run4a_p6");
	run4a_p6.AddMCSample("magnet", P6_4a);
	p6.AddSampleGroup("run4a_p6", run4a_p6);
	
    float win_scale = 0.75;
    int n_wide(2);
    int n_high(2);

    const char * sample_names[12] = {"Fwd_CC0Pi0p","Fwd_CC0PiNp","Bwd_CC0Pi0p","Bwd_CC0PiNp","HAFwd_CC0Pi0p","HAFwd_CC0PiNp","HABwd_CC0Pi0p","HABwd_CC0PiNp","Fwd_CC1Pi","HAFwd_CC1Pi","Fwd_CCOther","CCPhoton"};
    const char * accum_levels[12] = {   "[0]>8"   ,   "[1]>8"   ,   "[2]>8"   ,   "[3]>8"   ,    "[4]>6"    ,    "[5]>6"    ,   "[6]>8"     ,   "[7]>8"     ,  "[8]>7"  ,   "[9]>7"   ,   "[10]>7"  , "[11]>6" };
	const int * topology_branch[12]={       0     ,      0      ,      0      ,      0      ,      0        ,      0        ,      0        ,      0        ,      1    ,      1      ,       2     ,    13    };
    const char * categories[2] = {"distribution", "effpurity"};
	
	TCanvas* canvas = new TCanvas("canvas", "canvas", 750*n_wide*win_scale, 500*n_high*win_scale);
	//canvas->Print("Plots.pdf[");
	
	plotMomCos(exp, p6, accum_levels, sample_names, categories, topology_branch);
	
	
	
	//canvas->Print("Plots.pdf]");
}

void plotMomCos(Experiment exp, Experiment p6, const char * accum_levels[], const char * sample_names[], const char * categories[], const int * topology_branch[]) {
	
	DrawingTools* draw = new DrawingTools("/home/t2k/aspeers/PROD7_validation/testing/MultiPiAnalysis_TEST.root");
	const char * variables[2] = {"mom","costheta"};
	const char * FGDs[1] = {"FGD1"};
	
	int f = 1; //FGD Number (keep at 1)
	
	for(int j = 0; j<1; j++){ // loop over distribution and efficiency&purity
		for(int i = 0; i<1; i++){ // loop over mom,cos
			for(int k = 0; k<12; k++){ // loop over samples
	
	if(j==0){ //Distributions
	if(i==0){ //Momentum
		draw->SetLegendPos("tr");
		draw->SetTitleX("Reconstructed p_{#mu}");
		draw->SetTitleY("Events");
		draw->SetTitle("TEST");
		//draw->SetTitle(Form("%s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		
		draw->Draw(exp,"all","magnet","selmu_mom",50,0,5000,"topology_ccphoton",Form("accum_level[0]%s",accum_levels[k]),"","OVER NOAUTOLABELS");
		}

		draw->ChangeLegendEntry(0, "P6AA","");
	}

		//canvas->SaveAs(Form("%s_%s_%s_%s.png",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		//canvas->Print("Plots.pdf");
		
		HistoStack* stack = NULL;
		stack = (HistoStack*)draw->GetLastStack();

		stack->Draw();
		
		TH1* CC0pi = stack->GetHisto1D(0);
		TH1* CC1pi = stack->GetHisto1D(1);
		TH1* CCOther = stack->GetHisto1D(2);
		TH1* CCPhoton = stack->GetHisto1D(3);
		TH1* BKG = stack->GetHisto1D(4);
		TH1* outFV = stack->GetHisto1D(5);
		
		double TotalEntries = CC0pi->GetEntries() + CC1pi->GetEntries() + CCOther->GetEntries() + CCPhoton->GetEntries() + BKG->GetEntries() + outFV->GetEntries();
		
		cout << "Sample: " << Form("%s", sample_names[k]) << std::endl
			<< "Total Entries: " << TotalEntries << std::endl
			<< "CC0pi Entries: " << CC0pi->GetEntries() << ", " << 100*CC0pi->GetEntries()/TotalEntries << "%"  << std::endl
			<< "CC1pi Entries: " << CC1pi->GetEntries() << ", " << 100*CC1pi->GetEntries()/TotalEntries << "%" << std::endl
			<< "CCOther Entries: " << CCOther->GetEntries() << ", " << 100*CCOther->GetEntries()/TotalEntries << "%" << std::endl
			<< "CCPhoton Entries: " << CCPhoton->GetEntries() << ", " << 100*CCPhoton->GetEntries()/TotalEntries << "%" << std::endl
			<< "BKG Entries: " << BKG->GetEntries() << ", " << 100*BKG->GetEntries()/TotalEntries << "%" << std::endl
			<< "outFV Entries: " << outFV->GetEntries() << ", " << 100*outFV->GetEntries()/TotalEntries << "%" << std::endl;
			}
		}
	}
	
}

