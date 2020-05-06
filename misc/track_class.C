#define track_class_cxx
#include "track_class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TVector3.h>

void track_class::Loop()
{
//   In a ROOT session, you can do:
//      root> .L track_class.C
//      root> track_class t
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

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (Cut(ientry) < 0) continue;
      TVector3 gP(gpx, gpy, gpz);
      double gPhi = gP.Phi();
      double gTheta = gP.Theta();
      TVector3 P(px, py, pz);
      double Phi = P.Phi();
      double Theta = P.Theta();
      hphi->Fill(Phi-gPhi);
      htheta->Fill(Theta-gTheta);
   }
   
   double phi_res = hphi->GetRMS();
   double phi_resE = hphi->GetRMSError();
   double theta_res = htheta->GetRMS();
   double theta_resE = htheta->GetRMSError();
   
   cout << phi_res << " " << phi_resE << " ";
   cout << theta_res << " " << theta_resE << endl;
}

void GetAngularRes(const char* dir, const char* det, const int eta, const int pt){
  TString name = Form("%s/G4EICDetector.root_g4tracking_eval_%s_eta%d_%02d.root", dir, det, eta, pt);
  TFile* f = new TFile(name.Data());
  TTree* tr = (TTree*)f->Get("tracks");
  track_class* t = new track_class(tr);
  cout << det << " " << eta << " " << pt << " ";
  t->Loop();
  f->Close();
  delete t;
}

void RunAll(){
  const char* dir = "/local/home/qh261761/CEA/EIC/EICsim/MM_EIC_work_output/work";
  const char* det[5] = {
  "MM_6_3x2_1D", "MM_6_3x2_2D", "MM_6_eq_1D", "MM_6_eq_2D", "TPC"
  };
  const int eta[3] = {0,1,3};
  const int pt[14] = {1,2,3,4,5,6,7,8,9,10,20,30,40,50};
  cout << "detector eta pt phi_res phi_resE theta_res theta_resE" << endl;
  for (int i=0; i<5; i++)
    for (int j=0; j<3; j++)
      for (int k=0; k<14; k++)
        GetAngularRes(dir, det[i], eta[j], pt[k]);
}
