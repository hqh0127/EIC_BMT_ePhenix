void DrawMatScan(const char* name="svtx"){

  std::map<TString, TString> labels;
  labels[TString("svtx")] = TString("TPC");
  labels[TString("BMT_1D_equalspace")] = TString("1D BMT equally spaced");
  //labels[TString("BMT_2D_equalspace")] = TString("2D BMT equally spaced");
  labels[TString("BMT_2D_equalspace")] = TString("6-layer MPGD Tracker (2D RO)");
  labels[TString("BMT_1D_gap_15mm")] = TString("1D BMT 3#times2 w/ 15mm");
  labels[TString("BMT_2D_gap_15mm")] = TString("2D BMT 3#times2 w/ 15mm");

	TString hname = "pipe_" + TString(name) + "_new_ave_theta";
	TFile* f = new TFile("materialscan.root");
	TH1F* h0 = (TH1F*)f->Get("pipe_only_new_ave_theta");
	TH1F* h1 = (TH1F*)f->Get("pipe_mvtx_new_ave_theta");
	TH1F* h2 = (TH1F*)f->Get(hname.Data());
	h1->SetFillColor(kGray);
	h2->SetFillColor(kGreen);
	TCanvas* c = new TCanvas("c1","c1");
	c->SetLeftMargin(0.12);
	h2->Draw();
	h2->GetYaxis()->SetRangeUser(0,0.08);
	h2->GetXaxis()->SetRangeUser(-3,3);
	h1->Draw("same");
	h0->Draw("same");
	TLegend* leg = new TLegend(0.36, 0.72, 0.66, 0.87);
	leg->AddEntry(h0, "Beampipe", "f");
	leg->AddEntry(h1, "Si Vertex Detector", "f");
	leg->AddEntry(h2, labels[TString(name)].Data(), "f");
	//leg->SetFillStyle(0);
	//leg->Draw();
  c->Update();
	TLine *l1 = new TLine(c->GetUxmin(),0.05,c->GetUxmax(),0.05);
	l1->SetLineColor(kRed);
	l1->SetLineStyle(9);
	l1->SetLineWidth(2);
	l1->Draw();
	l1 = new TLine(-1,0,-1,h2->GetMaximum());
	l1->SetLineColor(kBlack);
	l1->SetLineStyle(2);
	l1->SetLineWidth(2);
	l1->Draw();
	l1 = new TLine(1,0,1,h2->GetMaximum());
	l1->SetLineColor(kBlack);
	l1->SetLineStyle(2);
	l1->SetLineWidth(2);
	l1->Draw();
	leg->Draw();
}
