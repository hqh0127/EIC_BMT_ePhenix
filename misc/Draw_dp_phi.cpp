#include "dirc_class.C"
#include "track_class.C"
#include <map>
#include <algorithm>
TGraph** Draw_graphs(int deg, int p, const char* detector){
  TGraph** gr = new TGraph* [2];
  gr[0] = nullptr;
  gr[1] = nullptr;
  string folder = "/local/home/qh261761/CEA/EIC/EICsim/MM_EIC_work_output/work_dirc/";
  std::map<int, std::string> deg2eta;
  deg2eta[43] = std::string("0.9316316147538235");
  deg2eta[66] = std::string("0.4316947267462241");
  deg2eta[89] = std::string("0.017454178683585186");

  string filename = folder + "G4EICDetector.root_g4tracking_eval_" + std::string(detector) + "_eta" + deg2eta[deg] + std::string(Form("_%02d.root", p));

  TFile *f = new TFile(filename.c_str());
  TTree* dirc = (TTree*)f->Get("dirc");
  TTree* track = (TTree*)f->Get("tracks");

  dirc_class dirc_c(dirc);
  track_class track_c(track);

  float *dp = new float [dirc->GetEntries()];
  float *phi = new float [dirc->GetEntries()];

  for (Long64_t jentry=0; jentry< dirc->GetEntries();jentry++) {
    dirc->GetEntry(jentry);
    float gpx = dirc_c.gpx;
    float gpy = dirc_c.gpy;
    float gpz = dirc_c.gpz;
    float px = dirc_c.px;
    float py = dirc_c.py;
    float pz = dirc_c.pz;
    TVector3 gP(gpx, gpy, gpz);
    double gPhi = gP.Phi();
    TVector3 P(px, py, pz);
    dp[jentry] = (P.Mag()/gP.Mag()-1);
    phi[jentry] = gPhi>0?gPhi:gPhi+2*TMath::Pi();
  }
  //cout << phi[100] << " " << dp[100] <<endl;

  gr[0] = new TGraph(dirc->GetEntries(), phi, dp);

  delete [] dp;
  delete [] phi;

  dp = new float [track->GetEntries()];
  phi = new float [track->GetEntries()];

  for (Long64_t jentry=0; jentry< track->GetEntries();jentry++) {
    track->GetEntry(jentry);
    float gpx = track_c.gpx;
    float gpy = track_c.gpy;
    float gpz = track_c.gpz;
    float px = track_c.px;
    float py = track_c.py;
    float pz = track_c.pz;
    TVector3 gP(gpx, gpy, gpz);
    double gPhi = gP.Phi();
    TVector3 P(px, py, pz);
    dp[jentry] = (P.Mag()/gP.Mag()-1);
    phi[jentry] = gPhi>0?gPhi:gPhi+2*TMath::Pi();
  }
  //cout << phi[100] << " " << dp[100] <<endl;

  gr[1] = new TGraph(track->GetEntries(), phi, dp);

  delete [] dp;
  delete [] phi;

  return gr;
}
TProfile** Draw_profiles(int deg, int p, const char* detector){
  double maxaccp = 1.;
  TProfile** gr = new TProfile* [2];
  gr[0] = nullptr;
  gr[1] = nullptr;
  string folder = "/local/home/qh261761/CEA/EIC/EICsim/MM_EIC_work_output/work_dirc/";
  std::map<int, std::string> deg2eta;
  deg2eta[43] = std::string("0.9316316147538235");
  deg2eta[66] = std::string("0.4316947267462241");
  deg2eta[89] = std::string("0.017454178683585186");

  string filename = folder + "G4EICDetector.root_g4tracking_eval_" + std::string(detector) + "_eta" + deg2eta[deg] + std::string(Form("_%02d.root", p));

  TFile *f = new TFile(filename.c_str());
  TTree* dirc = (TTree*)f->Get("dirc");
  TTree* track = (TTree*)f->Get("tracks");

  dirc_class* dirc_c = new dirc_class(dirc);
  track_class* track_c = new track_class(track);

  float *dp = new float [dirc->GetEntries()];
  float *phi = new float [dirc->GetEntries()];

  for (Long64_t jentry=0; jentry< dirc->GetEntries();jentry++) {
    dirc->GetEntry(jentry);
    float &gpx = dirc_c->gpx;
    float &gpy = dirc_c->gpy;
    float &gpz = dirc_c->gpz;
    float &px = dirc_c->px;
    float &py = dirc_c->py;
    float &pz = dirc_c->pz;
    TVector3 gP(gpx, gpy, gpz);
    double gPhi = gP.Phi();
    TVector3 P(px, py, pz);
    dp[jentry] = (P.Mag()/gP.Mag()-1);
    phi[jentry] = gPhi>0?gPhi:gPhi+2*TMath::Pi();
  }

  gr[0] = new TProfile("hprof_dirc", ";;", 80, 0, 2*TMath::Pi(), -maxaccp, maxaccp, "s");
  for (int i=0; i<dirc->GetEntries(); i++){
    //if (TMath::Abs(dp[i])<1)
    gr[0]->Fill(phi[i], dp[i]);
  }

  delete [] dp;
  delete [] phi;

  dp = new float [track->GetEntries()];
  phi = new float [track->GetEntries()];

  for (Long64_t jentry=0; jentry< track->GetEntries();jentry++) {
    track->GetEntry(jentry);
    float &gpx = track_c->gpx;
    float &gpy = track_c->gpy;
    float &gpz = track_c->gpz;
    float &px = track_c->px;
    float &py = track_c->py;
    float &pz = track_c->pz;
    TVector3 gP(gpx, gpy, gpz);
    double gPhi = gP.Phi();
    TVector3 P(px, py, pz);
    dp[jentry] = (P.Mag()/gP.Mag()-1);
    phi[jentry] = gPhi>0?gPhi:gPhi+2*TMath::Pi();
  }

  gr[1] = new TProfile("hprof_vtx", ";;", 100, 0, 2*TMath::Pi(), -maxaccp, maxaccp, "s");
  for (int i=0; i<track->GetEntries(); i++){
  //  //cout << phi[i] << " " << dp[i] << endl;
    //if (TMath::Abs(dp[i])<1)
    gr[1]->Fill(phi[i], dp[i]);
  }

  delete [] dp;
  delete [] phi;

  return gr;
}
void Draw_dp_phi(int deg=43, int p=1, const char* det="MM_6_3x2_2D"){
  /*
  int deg=43, p=1;
  const char* det = "MM_6_3x2_2D";
  */

  /*
  int deg=89, p=1;
  const char* det = "MM_6_eq_2D";
  */

  /*
  int deg=43, p=5;
  const char* det = "MM_6_3x2_2D";
  */

  /*
  int deg=89, p=1;
  const char* det = "MM_6_3x2_2D";
  */

  TCanvas* c1 = new TCanvas("c1");
  c1->cd();
  TH2D* h = new TH2D("h0", ";#phi;#Deltap/p",1000,0, 2*TMath::Pi(), 1000, -1,1);
  h->SetStats(kFALSE);
  h->Draw("AXIS");

  TGraph** gr = Draw_graphs(deg,p,det);
  gr[0]->Draw("P same");
  gr[1]->SetMarkerColor(kRed);
  gr[1]->Draw("P same");

  TCanvas* c2 = new TCanvas("c2");
  c2->cd();
  h->Draw("AXIS");
  TProfile** pf = Draw_profiles(deg,p,det);
  pf[0]->Draw("same");
  pf[1]->SetMarkerColor(kRed);
  pf[1]->SetLineColor(kRed);
  pf[1]->Draw("same");

  auto legend = new TLegend(0.1,0.7,0.48,0.9);
  legend->AddEntry(pf[0],"At DIRC","lep");
  legend->AddEntry(pf[1],"At Center","lep");
  legend->Draw();
  TPaveText *pt = new TPaveText(.05,.3,.95,.6);
  pt->AddText(Form("deg: %d#circ", deg));
  pt->AddText(Form("p_{T}: %d GeV", p));
  pt->AddText(Form("Detector: %s", det));
  pt->Draw();
  
  Float_t small = 1e-5;
  TCanvas* c3 = new TCanvas("c3","c3",0,0,600,600);
  c3->Divide(1,2, small, small);
  c3->cd(1);
  c3->cd(1)->SetBottomMargin(small);
  h =(TH2D*) h->Clone();
  h->GetYaxis()->SetTitle("#LT#Deltap/p#GT");
  h->GetYaxis()->CenterTitle();
  h->Draw("AXIS");
  
  gPad->Update();
  gPad->Modified();
  
  
  double pfx[80], pfm[80], pfm_e[80];
  for (int i=0; i<80; i++){
    pfx[i] = pf[0]-> GetXaxis()-> GetBinCenter( i+1 );
    pfm[i] = pf[0]->GetBinContent(i+1);
    pfm_e[i] = pf[0]->GetBinError(i+1);
  }
  TGraph* gr_pfm = new TGraph(80, pfx, pfm);
  gr_pfm->SetMarkerStyle(8);
  gr_pfm->SetMarkerSize(1);
  gr_pfm->Draw("PL same");
  double minpfm = *min_element (pfm, pfm+80);
  double maxpfm = *max_element (pfm, pfm+80);
  double margin = maxpfm/0.9 - maxpfm;
  //h->GetYaxis()->SetRangeUser(minpfm-margin, maxpfm/0.9);
  h->GetYaxis()->SetRangeUser(-0.004, .02);
  
  c3->cd(2);
  c3->cd(2)->SetTopMargin(small);
  c3->cd(2)->SetTickx();
  h =(TH2D*) h->Clone();
  h->GetYaxis()->SetTitle("#sigma(#Deltap/p)");
  h->Draw("AXIS");
  
  gPad->Update();
  gPad->Modified();
  gr_pfm = new TGraph(80, pfx, pfm_e);
  gr_pfm->SetMarkerStyle(8);
  gr_pfm->SetMarkerSize(1);
  gr_pfm->Draw("PL same");
  minpfm = *min_element (pfm_e, pfm_e+80);
  maxpfm = *max_element (pfm_e, pfm_e+80);
  margin = maxpfm/0.9 - maxpfm;
  //h->GetYaxis()->SetRangeUser(minpfm-margin, maxpfm/0.9);
  h->GetYaxis()->SetRangeUser(0, .08);
  
  c3->cd(1);
  pt = new TPaveText(0.56689097, 0.68750750, 0.89298445, 0.88195973, "NDC NB");
  pt->AddText(Form("deg: %d#circ", deg));
  pt->AddText(Form("p_{T}: %d GeV", p));
  pt->AddText(Form("Detector: %s", det));
  pt->SetFillStyle(0);
  pt->Draw();
  cout << pt << endl;
  
  int deg2, p2;
  deg2 = 89;
  p2 = p;
  pf = Draw_profiles(deg2,p2,det);
  c3->cd(1);
  
  gPad->Update();
  gPad->Modified();
  
  for (int i=0; i<80; i++){
    pfx[i] = pf[0]-> GetXaxis()-> GetBinCenter( i+1 );
    pfm[i] = pf[0]->GetBinContent(i+1);
    pfm_e[i] = pf[0]->GetBinError(i+1);
  }
  gr_pfm = new TGraph(80, pfx, pfm);
  gr_pfm->SetMarkerStyle(8);
  gr_pfm->SetMarkerSize(1);
  gr_pfm->SetMarkerColor(2);
  gr_pfm->SetLineColor(2);
  gr_pfm->Draw("PL same");
  
  c3->cd(2);
  c3->cd(2)->SetTickx();
  
  gPad->Update();
  gPad->Modified();
  gr_pfm = new TGraph(80, pfx, pfm_e);
  gr_pfm->SetMarkerStyle(8);
  gr_pfm->SetMarkerSize(1);
  gr_pfm->SetMarkerColor(2);
  gr_pfm->SetLineColor(2);
  gr_pfm->Draw("PL same");
  
  c3->cd(1);
  //pt = new TPaveText(0.15885605, 0.083316666, 0.48494953, 0.27776889, "NDC NB");
  pt = new TPaveText(0.56689097, 0.48263819, 0.89298445, 0.67709042, "NDC NB");
  pt->AddText(Form("deg: %d#circ", deg2))->SetTextColor(kRed);
  pt->AddText(Form("p_{T}: %d GeV", p2))->SetTextColor(kRed);
  pt->AddText(Form("Detector: %s", det))->SetTextColor(kRed);
  pt->SetFillStyle(0);
  //pt->SetBorderSize(0);
  pt->SetLineColor(2);
  pt->Draw();
  cout << pt << endl;
}
