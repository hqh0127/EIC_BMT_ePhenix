//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 20 15:55:02 2020 by ROOT version 6.18/04
// from TTree dirc/FastSim Eval => dirc
// found on file: G4EICDetector.root_g4tracking_eval_TPC_eta0.9316316147538235_10.root
//////////////////////////////////////////////////////////

#ifndef dirc_class_h
#define dirc_class_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>

// Header file for the classes stored in the TTree if any.

class dirc_class {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           event;
   Int_t           gtrackID;
   Int_t           gflavor;
   Float_t         gpx;
   Float_t         gpy;
   Float_t         gpz;
   Float_t         ghx;
   Float_t         ghy;
   Float_t         ghz;
   Float_t         ght;
   Int_t           trackID;
   Int_t           charge;
   Int_t           nhits;
   Float_t         px;
   Float_t         py;
   Float_t         pz;
   Float_t         phx;
   Float_t         phy;
   Float_t         phz;
   Float_t         dca;

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_gtrackID;   //!
   TBranch        *b_gflavor;   //!
   TBranch        *b_gpx;   //!
   TBranch        *b_gpy;   //!
   TBranch        *b_gpz;   //!
   TBranch        *b_ghx;   //!
   TBranch        *b_ghy;   //!
   TBranch        *b_ghz;   //!
   TBranch        *b_ght;   //!
   TBranch        *b_trackID;   //!
   TBranch        *b_charge;   //!
   TBranch        *b_nhits;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_phx;   //!
   TBranch        *b_phy;   //!
   TBranch        *b_phz;   //!
   TBranch        *b_dca;   //!

   dirc_class(TTree *tree=0);
   virtual ~dirc_class();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   TCanvas* c1;
   TCanvas* c2;
};

#endif

#ifdef dirc_class_cxx
dirc_class::dirc_class(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("G4EICDetector.root_g4tracking_eval_TPC_eta0.9316316147538235_10.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("G4EICDetector.root_g4tracking_eval_TPC_eta0.9316316147538235_10.root");
      }
      f->GetObject("dirc",tree);

   }
   Init(tree);
   c1 = nullptr;
   c2 = nullptr;
}

dirc_class::~dirc_class()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t dirc_class::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t dirc_class::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void dirc_class::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("gtrackID", &gtrackID, &b_gtrackID);
   fChain->SetBranchAddress("gflavor", &gflavor, &b_gflavor);
   fChain->SetBranchAddress("gpx", &gpx, &b_gpx);
   fChain->SetBranchAddress("gpy", &gpy, &b_gpy);
   fChain->SetBranchAddress("gpz", &gpz, &b_gpz);
   fChain->SetBranchAddress("ghx", &ghx, &b_ghx);
   fChain->SetBranchAddress("ghy", &ghy, &b_ghy);
   fChain->SetBranchAddress("ghz", &ghz, &b_ghz);
   fChain->SetBranchAddress("ght", &ght, &b_ght);
   fChain->SetBranchAddress("trackID", &trackID, &b_trackID);
   fChain->SetBranchAddress("charge", &charge, &b_charge);
   fChain->SetBranchAddress("nhits", &nhits, &b_nhits);
   fChain->SetBranchAddress("px", &px, &b_px);
   fChain->SetBranchAddress("py", &py, &b_py);
   fChain->SetBranchAddress("pz", &pz, &b_pz);
   fChain->SetBranchAddress("phx", &phx, &b_phx);
   fChain->SetBranchAddress("phy", &phy, &b_phy);
   fChain->SetBranchAddress("phz", &phz, &b_phz);
   fChain->SetBranchAddress("dca", &dca, &b_dca);
   Notify();
}

Bool_t dirc_class::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void dirc_class::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t dirc_class::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   if (nhits > -9999)
      return 1;
   else
      return -1;
}
#endif // #ifdef dirc_class_cxx
