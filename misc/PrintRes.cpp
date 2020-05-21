TF1* getFitFunc(TH1F* h);

void PrintRes (const char* fn, const float eta, const float pt, const char* detector){
  TFile *f = new TFile(fn);
  TTree* tracks = (TTree*)f->Get("tracks");
  tracks->Draw("100*(sqrt(px*px+py*py)/sqrt(gpx*gpx+gpy*gpy)-1)>>h1(5000)", "nhits>-9999 && abs(sqrt(px*px+py*py)/sqrt(gpx*gpx+gpy*gpy)-1)<1","goff");
  TH1F* h1 = (TH1F*)gDirectory->Get("h1");
  TF1* f1 = getFitFunc(h1);
  float ptres = f1->GetParameter(2);
  float ptres_e = f1->GetParError(2);
  tracks->Draw("100*(sqrt(px*px+py*py+pz*pz)/sqrt(gpx*gpx+gpy*gpy+gpz*gpz)-1)>>h2(5000)", "nhits>-9999 && abs(sqrt(px*px+py*py+pz*pz)/sqrt(gpx*gpx+gpy*gpy+gpz*gpz)-1)<1","goff");
  TH1F* h2 = (TH1F*)gDirectory->Get("h2");
  TF1* f2 = getFitFunc(h2);
  float pres = f2->GetParameter(2);
  float pres_e = f2->GetParError(2);
  ofstream myfile;
  //TString foutname =Form("log_eta%d_pt%02d.log", eta, (int)pt);
  TString foutname =Form("output.log");
  cout << "Results output to " << foutname << endl;
  myfile.open (foutname.Data(), ios::out | ios::trunc);
  myfile << detector << " ";
  myfile << eta << " " << pt << " ";
  myfile << ptres << " " << ptres_e << " ";
  myfile << pres << " " << pres_e << endl;
  myfile.close();
}

TF1* getFitFunc(TH1F* h){
  h->Fit("gaus","0");
  return (TF1*)h->GetFunction("gaus");
}
