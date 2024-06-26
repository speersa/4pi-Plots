#include <string>
#include <vector>

void plotMomCos(Experiment exp, Experiment p6, const char * accum_levels[], const char * sample_names[], const char * categories[], const int topology_branch[], TCanvas* canvas) {
	
	DrawingTools* draw = new DrawingTools("/data/aspeers/4pi_Selection/mcp/microTrees/P7E_FHC_run4.root");
	const char * variables[2] = {"mom","costheta"};
	const char * FGDs[1] = {"FGD1"};
	
	int f = 1; //FGD Number (keep at 1)
	
	for(int j = 0; j<2; j++){ // loop over distribution and efficiency&purity
		for(int i = 0; i<2; i++){ // loop over mom,cos
			for(int k = 0; k<12; k++){ // loop over samples
	
	if(j==0){ //Distributions
	if(i==0){ //Momentum
	
		draw->SetLegendPos("tr");
		draw->SetTitleX("Reconstructed p_{#mu}");
		draw->SetTitleY("Events");
		//draw->SetTitle("TEST");
		draw->SetTitle(Form("%s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		
		if(k==4||k==5||k==6||k==7){
			draw->Draw(exp,"all","magnet","selmu_mom_range_oarecon",50,0,5000,"topology_ccphoton",Form("accum_level[0]%s",accum_levels[k]),"","OVER NOAUTOLABELS");}
			
			else {draw->Draw(exp,"all","magnet","selmu_mom",50,0,5000,"topology_ccphoton",Form("accum_level[0]%s",accum_levels[k]),"","OVER NOAUTOLABELS");}

		}
	if(i==1){ //cos(theta)
		if(k==2||k==3||k==6||k==7){draw->SetLegendPos("tr");}
		else {draw->SetLegendPos("tl");}
		//draw->SetTitleX(Form("Reconstructed cos#theta_{#mu} %s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		draw->SetTitleX("Reconstructed cos#theta_{#mu}");
		draw->SetTitleY("Events");
		draw->SetTitle(Form("%s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		
		draw->Draw(exp,"all","magnet","selmu_costheta",50, -1, 1,"topology_ccphoton",Form("accum_level[0]%s",accum_levels[k]),"","UNDER NOAUTOLABELS");
		}
		draw->ChangeLegendEntry(0, "P6AA","");
		
		TH1D* histo1 = NULL;
		histo1 = (TH1D*)draw->GetLastHisto();
		cout << Form("%s_%s_%s_%s Integral: ",FGDs[f-1],sample_names[k],variables[i],categories[j]) << histo1->Integral();
		/*
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
		*/
	}
	
	else if(j==1){ //Efficiency and Purity
	exp.SetCurrentTree("truth"); //Sets the tree for true values to be used
	p6.SetCurrentTree("truth");
	if(i==0){ //Momentum
		//TLegend* legend = NULL;
		auto legend = new TLegend(0.6,0.7,0.9,0.9);
		TGraphAsymmErrors* graph1 = NULL;
		if(k>7){auto legend = new TLegend(0.6,0.7,0.9,0.9);}
		else {auto legend = new TLegend(0.6,0.2,0.9,0.4);}
		draw->SetTitleY("Efficiency & Purity");
		draw->SetTitleX("True p_{#mu} [MeV/c]");
		draw->SetTitle(Form("%s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		//draw->SetTitleX(Form("True p_{#mu} [MeV/c] %s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		
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
		draw->SetTitleX("True cos(#theta)");
		draw->SetTitleY("Efficiency & Purity");
		draw->SetTitle(Form("%s_%s_%s_%s",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		
		draw->DrawEff(p6,false,"truelepton_costheta",50, -1, 1,Form("accum_level[0]%s",accum_levels[k]),Form("topology_ccphoton==%d", topology_branch[k]),"","UNDER","P6 Eff");
		draw->DrawEff(exp,false,"truelepton_costheta",50, -1, 1,Form("accum_level[0]%s",accum_levels[k]),Form("topology_ccphoton==%d", topology_branch[k]),"same","UNDER","P7 Eff");
		
		draw->DrawPur(p6,"truelepton_costheta",50, -1, 1,Form("topology_ccphoton==%d", topology_branch[k]),Form("accum_level[0]%s",accum_levels[k]),"same","UNDER","P6 Pur");		
		draw->DrawPur(exp,"truelepton_costheta",50, -1, 1,Form("topology_ccphoton==%d", topology_branch[k]),Form("accum_level[0]%s",accum_levels[k]),"same","UNDER","P7 Pur");
		}
	}
	
		canvas->SaveAs(Form("%s %s %s %s.png",FGDs[f-1],sample_names[k],variables[i],categories[j]));
		canvas->Print("Plots.pdf");
			}
		}
	}
}

void fourpi_plots() {
	
    gROOT->SetBatch(); //Stops it from spamming windows when drawing
	DrawingTools* draw = new DrawingTools("/data/aspeers/4pi_Selection/mcp/microTrees/P7_V12_HL3.11_FHC_run4_air.root"); //Initialises DrawingTools with a random .root file
	//draw->SetStackFillStyle(3254);

	// Create an experiment with name "nd280"
    Experiment exp("nd280");

	DataSample* prod_7 = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P7_V12_HL3.11_FHC_run4_air.root");
	//DataSample* prod_7 = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P6AA_FHC_FGD1_default_settings.root");
    SampleGroup p_7("p_7");
    p_7.AddMCSample("magnet", prod_7);
	//exp.AddSampleGroup("p_7", p_7);
	
	DataSample* prod_6 = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P6AA_FHC_HL3.11_FHC.root");
	//DataSample* prod_6 = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P7E_FHC_run8_water.root");
    p_7.AddDataSample(prod_6);
    exp.AddSampleGroup("p_7", p_7); 
	
	//Create a seperate experiment for eff&pur for P6
	Experiment p6("nd280_p6");
  
	DataSample* P6_4a = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P6AA_FHC_HL3.11_FHC.root");
	//DataSample* P6_4a = new DataSample("/data/aspeers/4pi_Selection/mcp/microTrees/P7E_FHC_run8_water.root");
	SampleGroup run4a_p6("run4a_p6");
	run4a_p6.AddMCSample("magnet", P6_4a);
	p6.AddSampleGroup("run4a_p6", run4a_p6);


    const char * sample_names[12] = {"Fwd_CC0Pi0p","Fwd_CC0PiNp","Bwd_CC0Pi0p","Bwd_CC0PiNp","HAFwd_CC0Pi0p","HAFwd_CC0PiNp","HABwd_CC0Pi0p","HABwd_CC0PiNp","Fwd_CC1Pi","HAFwd_CC1Pi","Fwd_CCOther","CCPhoton"};
    const char * accum_levels[12] = {   "[0]>8"   ,   "[1]>8"   ,   "[2]>8"   ,   "[3]>8"   ,    "[4]>6"    ,    "[5]>6"    ,   "[6]>8"     ,   "[7]>8"     ,  "[8]>7"  ,   "[9]>7"   ,   "[10]>7"  , "[11]>6" };
	const int topology_branch[12]={       0     ,      0      ,      0      ,      0      ,      0        ,      0        ,      0        ,      0        ,      1    ,      1      ,       2     ,    13    };
    const char * categories[2] = {"distribution", "effpurity"};
	
	float win_scale = 0.75;
    int n_wide(2);
    int n_high(2);
	
	TCanvas* canvas = new TCanvas("canvas", "canvas", 750*n_wide*win_scale, 500*n_high*win_scale);
	canvas->Print("Plots.pdf[");
	
	plotMomCos(exp, p6, accum_levels, sample_names, categories, topology_branch, canvas);
	
	canvas->Print("Plots.pdf]");
	
}



