#define dirc_class_cxx
#include "dirc_class.h"
#include <TH2.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TVector3.h>

void dirc_class::Loop()
{
//   In a ROOT session, you can do:
//      root> .L dirc_class.C
//      root> dirc_class t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   TH1F* hphi = new TH1F("phi",";#phi;",1000,-0.03,0.03);
   TH1F* htheta = new TH1F("theta",";#theta;",1000,-0.03, 0.03);
   TH1F* hdp0 = new TH1F("dp0",";#Deltap;",1000,-1., 1.);
   TH1F* hdpt0 = new TH1F("dpt0",";#Deltap_{t};",1000,-1., 1.);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (Cut(ientry) < 0) continue;
      TVector3 gP(gpx, gpy, gpz);
      TVector3 gPt(gpx, gpy, 0);
      double gPhi = gP.Phi();
      double gTheta = gP.Theta();
      TVector3 P(px, py, pz);
      TVector3 Pt(px, py, 0);
      double Phi = P.Phi();
      double Theta = P.Theta();
      hphi->Fill(Phi-gPhi);
      htheta->Fill(Theta-gTheta);
      hdp0 ->Fill(P.Mag()/gP.Mag()-1);
      hdpt0 ->Fill(Pt.Mag()/gPt.Mag()-1);
   }

   double phi_res = hphi->GetRMS();
   double phi_resE = hphi->GetRMSError();
   double theta_res = htheta->GetRMS();
   double theta_resE = htheta->GetRMSError();

   double p_res = hdp0->GetRMS();
   double p_resE = hdp0->GetRMSError();
   double pt_res = hdpt0->GetRMS();
   double pt_resE = hdpt0->GetRMSError();

   hdp0->Fit("gaus","0Q");
   TF1* f = (TF1*)hdp0->GetFunction("gaus");
   if (f) {
     p_res = f->GetParameter(2);
     p_resE = f->GetParError(2);
   }

   hdpt0->Fit("gaus","0Q");
   f = (TF1*)hdpt0->GetFunction("gaus");
   if (f) {
     pt_res = f->GetParameter(2);
     pt_resE = f->GetParError(2);
   }

   hphi->Fit("gaus","0Q");
   f = (TF1*)hphi->GetFunction("gaus");
   if (f) {
     phi_res = f->GetParameter(2);
     phi_resE = f->GetParError(2);
   }

   htheta->Fit("gaus","0Q");
   f = (TF1*)htheta->GetFunction("gaus");
   if (f) {
     theta_res = f->GetParameter(2);
     theta_resE = f->GetParError(2);
   }
   /*
   if (!c1){
     c1 = new TCanvas("c1");
     c1->cd();
     hdpt0->Draw();
     c1->Update();
     hdp0->Draw();
     c1->Update();
     c1->Print("testc1.png");
   }
   */

   cout << phi_res << " " << phi_resE << " ";
   cout << theta_res << " " << theta_resE << " ";
   cout << pt_res << " " << pt_resE << " ";
   cout << p_res << " " << p_resE << endl;
}

void GetAngularRes(const char* dir, const char* det, const string eta, const int pt, const int nhit){
  TString name = Form("%s/G4EICDetector.root_g4tracking_eval_%s_eta%s_%02d_nhit%d.root", dir, det, eta.c_str(), pt, nhit);
  TFile* f = new TFile(name.Data());
  TTree* tr = (TTree*)f->Get("dirc");
  dirc_class* t = new dirc_class(tr);
  cout << det << " " << nhit << " " <<  eta << " " << pt << " ";
  t->Loop();
  f->Close();
  delete t;
}

void RunAll(){
  const char* dir = "/local/home/qh261761/CEA/EIC/EICsim/MM_EIC_work_output/work_withsupport";
  /*
  const char* det[2] = {
  "MM_6_3x2_2D", "MM_6_eq_2D"
  };
  const string eta[3] = {string("0.9316316147538235"),string("0.4316947267462241"),string("0.017454178683585186")};
  const int pt[14] = {1,2,3,4,5,6,7,8,9,10};
  const int nhit[4] = {1,2,3,5};
  */
  const char* det[10] = {
  "MM_i2o3_2D", "MM_i0o4_2D", "MM_m2o4_2D", "MM_i0o5_2D", "MM_m2o4_2D_mpgd100um_svtx10um", "MM_6_3x2_2D_mpgd100um_svtx10um", "MM_6_eq_2D_mpgd100um_svtx10um", 
  "MM_m2o3_2D", "MM_m2o3_2D_mpgd100um_svtx10um", "TPC_mpgd100um_svtx10um"
  };
  const string eta[3] = {string("0.9316316147538235"),string("0.4316947267462241"),string("0.017454178683585186")};
  const int pt[14] = {1,2,3,4,5,6,7,8,9,10};
  const int nhit[1] = {1};
  cout << "detector nhit eta pt phi_res phi_resE theta_res theta_resE pt_res pt_resE p_res p_resE" << endl;
  for (int i=0; i<10; i++)
    for (int j=0; j<3; j++)
      for (int k=0; k<10; k++)
      for (int l=0; l<1; l++)
        GetAngularRes(dir, det[i], eta[j], pt[k], nhit[l]);
}
