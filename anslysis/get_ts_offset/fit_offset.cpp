// Ge vs. Ge
// run Liki:
// .L fit_offset.cpp
// Ge && CsI need to fit different

void fit_offset()
{
  ofstream fo;
  fo.open("ts.offset");
  fo << "sid  ch  ts_offset[ns]  Low_channel High_channel" << endl;
  char str[1024];
  // sprintf(str, "%3d  %3d  %2d  %13.2f  %10.2f", 0, 0, 0, 0., 0.);
  //fo << str << endl;

  int sid, ch;
  double ts, chi2;
 
  // Ge
  TF1 *fg;
  TH1D *h_ge[4*16];
  TCanvas *c_ge[4*16];
  for(int i=2;i<=5;i++){
    for(int j=0;j<16;j++){
      h_ge[(i-2)*16+j] = (TH1D*)gFile->Get(TString::Format("ge_sid%d_ch%02d",i,j).Data());
      if(h_ge[(i-2)*16+j]->GetEntries()==0){
        // sprintf(str, "%3d\t%3d\t%2d\t%13.2f\t%10.2f", 0, i, j, 0., 0.);
        sprintf(str, "%d\t%2d\t%10.2f\t%5d\t%5d", i, j, 0., 0, 65535);
        fo << str << endl;
        continue;
        
      }

      c_ge[(i-2)*16+j] = new TCanvas(TString::Format("c0_%02d_%02d",i,j).Data(), "");
      c_ge[(i-2)*16+j]->cd();
      h_ge[(i-2)*16+j]->Draw();
      double peakMax0 = h_ge[(i-2)*16+j]->GetBinCenter(h_ge[(i-2)*16+j]->GetMaximumBin());
      h_ge[(i-2)*16+j]->Fit("gaus", "", "", peakMax0-100, peakMax0+100);
      h_ge[(i-2)*16+j]->Fit("fg", "R");
      fg = (TF1*)gROOT->GetListOfFunctions()->FindObject("gaus");
    
      ts = fg->GetParameter(1);
      chi2 = fg->GetChisquare();
    
      // sprintf(str, "%3d  %3d  %2d  %13.2f  %10.2f", 0, i, j, ts, chi2);
      sprintf(str, "%d\t%3d\t%10.2f\t%5d\t%5d ",i , j, ts,0,65535);
      fo << str << endl;

      // if(fg) delete fg;
      
    }
  }
 
/***********************************************************************
  // CsI
  TF1 *fg1;
  TH1D *h_csi[7*16];
  TCanvas *c_csi[7*16];
  for(int i=2;i<=8;i++){
    for(int j=0;j<16;j++){
      h_csi[(i-2)*16+j] = (TH1D*)gFile->Get(TString::Format("csi_sid%d_ch%02d",i,j).Data());

      if(h_csi[(i-2)*16+j]->GetEntries()==0){
        // sprintf(str, "%3d  %3d  %2d  %13.2f  %10.2f", 1, i, j, 0., 0.);
        sprintf(str, "%3d  %3d  %3d %5d %5d",i , j, 0 ,0,65535);
	fo << str << endl;
        continue;
      }

      c_csi[(i-2)*16+j] = new TCanvas(TString::Format("c1_%02d_%02d",i,j).Data(), "");
      c_csi[(i-2)*16+j]->cd();
      h_csi[(i-2)*16+j]->Draw();
      double peakMax = h_csi[(i-2)*16+j]->GetBinCenter(h_csi[(i-2)*16+j]->GetMaximumBin());
      h_csi[(i-2)*16+j]->Fit("gaus", "", "", peakMax-150, peakMax+150);
      fg1 = (TF1*)gROOT->GetListOfFunctions()->FindObject("gaus");
    
      ts = fg1->GetParameter(1);
      chi2 = fg1->GetChisquare();
    
      // sprintf(str, "%3d  %3d  %2d  %13.2f  %10.2f", 1, i, j, ts, chi2);
      sprintf(str, "%3d  %3d  %10.2f %5d %5d",i , j, ts ,0,65535);
      fo << str << endl;
            std::cout<<"zhy"<<std::endl;

    }
  }
 *********************************************************************/
/*
  // Sc
  TH1D *h_sc[3*16];
  TCanvas *c_sc[3*16];
  for(int i=9;i<=11;i++){
    for(int j=0;j<16;j++){
      h_sc[(i-9)*16+j] = (TH1D*)gFile->Get(TString::Format("sc_sid%d_ch%02d",i,j).Data());

      if(h_sc[(i-9)*16+j]->GetEntries()==0){
        sprintf(str, "%3d  %3d  %2d  %13.2f  %10.2f", 1, i, j, 0., 0.);
        fo << str << endl;
        continue;
      }

      c_sc[(i-9)*16+j] = new TCanvas(TString::Format("c2_%02d_%02d",i,j).Data(), "");
      c_sc[(i-9)*16+j]->cd();
      h_sc[(i-9)*16+j]->Draw();
      h_sc[(i-9)*16+j]->Fit("gaus", "", "", 200, 800);
      fg = (TF1*)gROOT->GetListOfFunctions()->FindObject("gaus");
    
      ts = fg->GetParameter(1);
      chi2 = fg->GetChisquare();
    
      sprintf(str, "%3d  %3d  %2d  %13.2f  %10.2f", 1, i, j, ts, chi2);
      fo << str << endl;
    }
  }
*/
  fo.close();
}

