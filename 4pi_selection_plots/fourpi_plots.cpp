#include <string>
#include <vector>

void fourpi_plots() {
	
    gROOT->SetBatch(); //Stops it from spamming windows when drawing
	DrawingTools* draw = new DrawingTools("/home/t2k/aspeers/PROD7_validation/testing/MultiPiAnalysis_TEST.root",4); //Initialises DrawingTools with a random .root file

	// Create an experiment with name "nd280"
    Experiment exp("nd280");

	DataSample* prod_7 = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P7_V12_FHC_FGD1_NHitsGT4_MipEmGT0.root");
    SampleGroup p_7("p_7");
    p_7.AddMCSample("magnet", prod_7);
	//exp.AddSampleGroup("p_7", p_7);
	
	DataSample* prod_6 = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P6AA_FHC_FGD1_default_settings.root");
    p_7.AddDataSample(prod_6);
    exp.AddSampleGroup("p_7", p_7); 
	
	//Create a seperate experiment for eff&pur for P6
	Experiment p6("nd280_p6");
  
	DataSample* P6_4a = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P6AA_FHC_FGD1_default_settings.root");
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
	canvas->Print("Plots.pdf[");
	
	plotMomCos(exp, p6, accum_levels, sample_names, categories, topology_branch);
	
	canvas->Print("Plots.pdf]");
}

void plotMomCos(Experiment exp, Experiment p6, const char * accum_levels[], const char * sample_names[], const char * categories[], const int * topology_branch[]) {
	
	DrawingTools* draw = new DrawingTools("/home/t2k/aspeers/PROD7_validation/testing/MultiPiAnalysis_TEST.root",4);
	const char * variables[2] = {"mom","costheta"};
	const char * FGDs[1] = {"FGD1"};
	
	int f = 1; //FGD Number (keep at 1)
	
	for(int j = 0; j<2; j++){ // loop over distribution and efficiency&purity
		for(int i = 0; i<2; i++){ // loop over mom,cos
			for(int k = 0; k<12; k++){ // loop over samples
	
	if(j==0){ //Distributions
	if(i==0){ //Momentum
		draw->SetLegendPos("tr");
		draw->SetTitleX(Form("Reconstructed p_{#mu} [MeV/c] %s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		draw->SetTitleY("Events");
		draw->SetTitle(Form("%s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		
		draw->Draw(exp,"all","magnet","selmu_mom",50,0,5000,"topology_ccphoton",Form("accum_level[0]%s",accum_levels[k]),"","OVER NOAUTOLABELS");
		}
	if(i==1){ //cos(theta)
		if(k==2||k==3||k==6||k==7){draw->SetLegendPos("tr");}
		else {draw->SetLegendPos("tl");}
		draw->SetTitleX(Form("Reconstructed cos#theta_{#mu} %s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		draw->SetTitleY("Events");
		draw->SetTitle(Form("%s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		
		draw->Draw(exp,"all","magnet","selmu_costheta",50, -1, 1,"topology_ccphoton",Form("accum_level[0]%s",accum_levels[k]),"","UNDER NOAUTOLABELS");
		}
		draw->ChangeLegendEntry(0, "P6AA","");
	}
	
	else if(j==1){ //Efficiency and Purity
	exp.SetCurrentTree("truth"); //Sets the tree for true values to be used
	p6.SetCurrentTree("truth");
	if(i==0){ //Momentum
		//draw->SetLegendPos("tl");
		if(k>7){auto legend = new TLegend(0.6,0.7,0.9,0.9);}
		else {auto legend = new TLegend(0.6,0.2,0.9,0.4);}
		draw->SetTitleY("Efficiency & Purity");
		//draw->SetTitleX("True p_{#mu} [MeV/c]");
		draw->SetTitleX(Form("True p_{#mu} [MeV/c] %s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		
		draw->DrawEff(p6,false,"truelepton_mom",50,0,5000,Form("accum_level[0]%s",accum_levels[k]),Form("topology_ccphoton==%d", topology_branch[k]),"","OVER NOLEG","P6 Eff");
		graph1 = (TGraphAsymmErrors*)draw->GetLastGraph();
		legend -> AddEntry(graph1,"P6 Eff","ep");
		graph1 -> SetLineColor(kBlack);
		graph1 -> SetMarkerColor(kBlack);
		draw->DrawEff(exp,false,"truelepton_mom",50,0,5000,Form("accum_level[0]%s",accum_levels[k]),Form("topology_ccphoton==%d", topology_branch[k]),"same","OVER NOLEG","P7 Eff");
		graph1 = (TGraphAsymmErrors*)draw->GetLastGraph();
		legend -> AddEntry(graph1,"P7 Eff","ep");
		graph1 -> SetLineColor(kRed);
		graph1 -> SetMarkerColor(kRed);
		
		draw->DrawPur(p6,"truelepton_mom",50,0,5000,Form("topology_ccphoton==%d", topology_branch[k]),Form("accum_level[0]%s",accum_levels[k]),"same","OVER NOLEG","P6 Pur");
		graph1 = (TGraphAsymmErrors*)draw->GetLastGraph();
		legend -> AddEntry(graph1,"P6 Pur","ep");
		graph1 -> SetLineColor(kGreen);
		graph1 -> SetMarkerColor(kGreen);
		draw->DrawPur(exp,"truelepton_mom",50,0,5000,Form("topology_ccphoton==%d", topology_branch[k]),Form("accum_level[0]%s",accum_levels[k]),"same","OVER NOLEG","P7 Pur");
		graph1 = (TGraphAsymmErrors*)draw->GetLastGraph();
		legend -> AddEntry(graph1,"P7 Pur","ep");
		graph1 -> SetLineColor(kBlue);
		graph1 -> SetMarkerColor(kBlue);
		
		legend -> Draw("same");
		}	
		
	else if(i==1){ //cos(theta)
		draw->SetLegendPos("tl");
		//draw->SetTitleX("True cos(#theta)");
		draw->SetTitleY("Efficiency & Purity");
		draw->SetTitleX(Form("True cos#theta_{#mu} %s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		
		draw->DrawEff(p6,false,"truelepton_costheta",50, -1, 1,Form("accum_level[0]%s",accum_levels[k]),Form("topology_ccphoton==%d", topology_branch[k]),"","UNDER","P6 Eff");
		draw->DrawEff(exp,false,"truelepton_costheta",50, -1, 1,Form("accum_level[0]%s",accum_levels[k]),Form("topology_ccphoton==%d", topology_branch[k]),"same","UNDER","P7 Eff");
		
		draw->DrawPur(p6,"truelepton_costheta",50, -1, 1,Form("topology_ccphoton==%d", topology_branch[k]),Form("accum_level[0]%s",accum_levels[k]),"same","UNDER","P6 Pur");		
		draw->DrawPur(exp,"truelepton_costheta",50, -1, 1,Form("topology_ccphoton==%d", topology_branch[k]),Form("accum_level[0]%s",accum_levels[k]),"same","UNDER","P7 Pur");
		}
	}
		//canvas->SaveAs(Form("Plots/%s_%s_%s_%s.pdf",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		canvas->Print("Plots.pdf");
			}
		}
	}
	
}

