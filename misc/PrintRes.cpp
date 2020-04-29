void PrintRes (const char* fn, const int eta, const float pt, const char* detector){
  TFile *f = new TFile(fn);
  TTree* tracks = (TTree*)f->Get("tracks");
  tracks->Draw("100*(sqrt(px*px+py*py)/sqrt(gpx*gpx+gpy*gpy)-1)>>h1", "nhits>-9999","goff");
  TH1F* h1 = (TH1F*)gDirectory->Get("h1");
  float ptres = h1->GetRMS();
  float ptres_e = h1->GetRMSError();
  tracks->Draw("100*(sqrt(px*px+py*py+pz*pz)/sqrt(gpx*gpx+gpy*gpy+gpz*gpz)-1)>>h1", "nhits>-9999","goff");
  float pres = h1->GetRMS();
  float pres_e = h1->GetRMSError();
  ofstream myfile;
  TString foutname =Form("log_eta%d_pt%02d.log", eta, (int)pt);
  cout << "Results output to " << foutname << endl;
  myfile.open (foutname.Data(), ios::out | ios::trunc);
  myfile << detector << " ";
  myfile << eta << " " << pt << " ";
  myfile << ptres << " " << ptres_e << " ";
  myfile << pres << " " << pres_e << endl;
  myfile.close();
}
