  
  void effpur(){
  
  DrawingTools* draw = new DrawingTools("/home/t2k/aspeers/PROD7_validation/testing/MultiPiAnalysis_TEST.root");
  // draw->SetStackFillStyle(3254);
  // gStyle->SetPadTickY(0);

  const int Nsamples = 12;
  TString cut_samplefgd[Nsamples] = {"accum_level[][0]>9", "accum_level[][1]>9", "accum_level[][2]>9", "accum_level[][3]>9", "accum_level[][4]>9", "accum_level[][5]>9", "accum_level[][6]>9", "accum_level[][7]>9", "accum_level[][8]>8", "accum_level[][9]>8", "accum_level[][10]>8", "accum_level[][11]>7"};
  TString cut_truth[Nsamples] = {"accum_level[0]>9", "accum_level[1]>9", "accum_level[2]>9", "accum_level[3]>9", "accum_level[4]>9", "accum_level[5]>9", "accum_level[6]>9", "accum_level[7]>9", "accum_level[8]>8", "accum_level[9]>8", "accum_level[10]>8", "accum_level[11]>7"};
  TString cut_topo[Nsamples] = {"topology_ccphoton == 0", "topology_ccphoton == 0", "topology_ccphoton == 0", "topology_ccphoton == 0", "topology_ccphoton == 0", "topology_ccphoton == 0", "topology_ccphoton == 0", "topology_ccphoton == 0", "topology_ccphoton == 1", "topology_ccphoton == 1", "topology_ccphoton == 2", "topology_ccphoton == 13"};
  TString sample_name[Nsamples] = {"FWD_CC0Pion_0Proton", "FWD_CC0Pion_NProtons", "BWD_CC0Pion_0Proton", "BWD_CC0Pion_NProton","HAFWD_CC0Pion_0Proton","HAFWD_CC0Pion_NProton", "HABWD_CC0Pion_0Proton","HABWD_CC0Pion_NProton","FWD_CC1Pion","HAFWD_CC1Pion","FWD_CCOther","FWD_CCPhoton"};

  DataSample* magnet_mc_run2a  = new DataSample("/data/aspeers/PROD7/V12/P7_V12_MultiPi_MipEm_0.root");
  TTree *default = magnet_mc_run2a->GetTree("default");


  draw->DrawEff(default,"selmu_costheta",1,-1,1,cut_topo[branch].Data(),cut_samplefgd[branch].Data());
  gPad->Print("/home/t2k/aspeers/4pi_selection/purx_cc0pi.png");




  TH1D* h1 = new TH1D("h1","h1",1,-1,1);
  TH1D* h2 = new TH1D("h2","h2",1,-1,1);
  TH1D* h3 = new TH1D("h3","h3",1,-1,1);
  TH1D* h4 = new TH1D("h4","h4",1,-1,1);

  TFile* microtree = TFile::Open(microtree_file.c_str());
  TTree* truth = new TTree;
  TTree* default = new TTree;
  microtree->GetObject("truth", truth);
  microtree->GetObject("default", default);

  Float_t costheta;
  default->SetBranchAddress("selmu_costheta", &costheta);
  Int_t topology_ccphoton, accum_level;
  default->SetBranchAddress("topology_ccphoton", &topology_ccphoton);
  default->SetBranchAddress("accum_level[0]", &accum_level);


  Int_t nentries = (Int_t)default->GetEntries();
  for (Int_t i=0; i<nentries; i++) {
      default->GetEntry(i);
      h1->Fill(costheta);
      std::cout << accum_level << std::endl;
   }
  int number = h1->GetBinContent()
  std::cout << "The purity of branch " << branch << " " << number << std::endl;

}