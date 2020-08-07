
void ThermalFit(TString DataFile = "datafile.csv"){
  
  TGraphErrors *Ts_eVsQ2;
  Ts_eVsQ2 = new TGraphErrors(DataFile,"%lg,%lg");

  Ts_eVsQ2->SetTitle("Ts_{e} Vs Q^{2};Ts_{e};Q^{2}");
  

  TCanvas *histocanvas;
  histocanvas = new TCanvas("fit", "Fit Function",5);

  histocanvas->cd();

    
  Ts_eVsQ2->SetMarkerSize(0.7);
  Ts_eVsQ2->SetMarkerStyle(34);
  Ts_eVsQ2->SetMarkerColor(2);
  Ts_eVsQ2->GetYaxis()->SetRangeUser(-1,25);
    
  Ts_eVsQ2->Draw("AP");

  // Fit    
  // Expo: f(x) = exp(p0+p1*x)
  // Range 19,63
  TF1 *FitFunc = new TF1("FitFunc","expo",19,63);

  // Fit Style
  FitFunc->SetLineColor(4);
  FitFunc->SetLineStyle(2);

  // Fit Options
  Ts_eVsQ2->Fit(FitFunc,"R"); // R from do the fit in the range

  // How to get the parameters
  double par_a    = FitFunc->GetParameter(0);
  double par_aErr = FitFunc->GetParError(0);
  double par_b    = FitFunc->GetParameter(1);
  double par_bErr = FitFunc->GetParError(1);
  double par_Xi2  = FitFunc->GetChisquare();
  double par_NdF  = FitFunc->GetNDF();
    
  TLegend *leg;
  leg = new TLegend(0.15,0.85,0.6,0.4);
  leg->SetFillColor(0);
  leg->SetLineWidth(0.);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);

    
    
  leg->AddEntry(Ts_eVsQ2,"Data","P");
  leg->AddEntry(FitFunc, "Fit", "L");
  leg->AddEntry((TObject*)0,"","");
  leg->AddEntry((TObject*)0,"Fit Par: e^{a+b Ts_{e}}","");
  leg->AddEntry((TObject*)0,TString::Format("a = %.3f #pm %.4f",par_a,par_aErr),"");
  leg->AddEntry((TObject*)0,TString::Format("b = %.3f #pm %.4f",par_b,par_bErr),"");
  leg->AddEntry((TObject*)0,TString::Format("#chi^{2} = %.3f",par_Xi2),"");
  leg->AddEntry((TObject*)0,TString::Format("NdF = %.f",par_NdF),"");

    
  leg->Draw("SAME");

  histocanvas->SaveAs("Fit-Ts_eVsQ2.pdf");

}
