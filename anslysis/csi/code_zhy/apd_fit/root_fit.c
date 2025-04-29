/*=======================================================*/
#define NSHAPE     5  //number of trial functions for waveform fit

#define CSI_BASELINE_RANGE 55 //baseline range in channels
#define FILTER 4 //integration region for noise reduction (in samples)
#define NOISE_LEVEL_CSI 100 //noise level for CsI with RF

#define apd_Range  160
#define Fit_Length  160////////////fit_Fit_Length
#define sipm_Range  500
#define PARA 6000

#include "TString.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <stdio.h>
#include <string.h>
//For ROOT
#include "TApplication.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
#include "endian.h"
#include "TFile.h"
//#include "TString.h"
#include "TTree.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "TChain.h" 
#include "TROOT.h"
#include "TObject.h"
#include<stdlib.h>
#include<TSpectrum.h>
#include<TGraph.h>
#include<TF1.h>
using namespace std;

int check_pileup(double *waveform)
{
  double a=0.0;
  int pileup_flag=0;

  for(int i=80;i<160;i++)
  {
    a=waveform[i]-waveform[i-2];
    if(a>600)  pileup_flag=1;
  }
  return pileup_flag;
}


double finmax(double *a)  /// max amplitude
{
  double max=a[50];
  for(int i=60;i<160;i++)
  {
    if(a[i]>max)  
      {max=a[i];}
  }
  return max;
}

double finmax_sipm(double *a)
{
  double max=a[50];
  for(int i=40;i<500;i++)
  {
    if(a[i]>max)  
      {max=a[i];}
  }
  return max;
}

int finmaxtime(double *a)
{
  double max=a[50];
  int tmax=50;
  for(int i=40;i<160;i++)
  {
    if(a[i]>max)  
      {
        max=a[i];
        tmax=i;
      }
  }
  return tmax;
}

int check_t0(UShort_t* data)   /// maybe need change
{  
  int a=CSI_BASELINE_RANGE;
  for(int i=10;i<CSI_BASELINE_RANGE;i++)
  {
    if(data[i+1]-data[i]>300)  
    {
      a=i;
      break;
    }
  }
  if(a<CSI_BASELINE_RANGE)  a=a-5;
  else a=CSI_BASELINE_RANGE;
  
  return a;
  
}

int check_sipm_t0(UShort_t* data)
{  
  int a=140;
  for(int i=50;i<140;i++)
  {
    if(data[i+1]-data[i]>300)  
    {
      a=i;
      break;
    }
  }
  if(a<140)  a=a-5;
  else a=140;
  
  return a;
  
}




double CsIfun(double *x, double *par)
{
  double tauf = 0.7;
  double taus = 3.3;
  //double taurc = double(PARA)/100.;
  // par[0] t0, par[1] Af, par[2] As , par[3] RC constant
  if(x[0] <= par[0] || x[0]>apd_Range) return 0;
  else //if (x[0] > par[0] && x[0]<=apd_Range)
  {
    //return par[1]*(1-TMath::Exp(-(x[0]-par[0])*0.16/tauf))*TMath::Exp(-(x[0]-par[0])*0.16/taurc)+par[2]*(1-TMath::Exp(-(x[0]-par[0])*0.16/taus))*TMath::Exp(-(x[0]-par[0])*0.16/taurc);
    return par[1]*(1-TMath::Exp(-(x[0]-par[0])*0.16/tauf))*TMath::Exp(-(x[0]-par[0])*0.16/par[3])+par[2]*(1-TMath::Exp(-(x[0]-par[0])*0.16/taus))*TMath::Exp(-(x[0]-par[0])*0.16/par[3]);
  }
}





double CsIfun_sipm(double *x, double *par)
{
  double ts=8./3300.;
  double tf=8./700.;
  //return 
  

  if(x[0] <= par[0]) return 0;
  else  
    //return par[1]*(-TMath::Exp(-(x[0]-par[0])*tf))+par[2]*(-TMath::Exp(-(x[0]-par[0])*ts))+par[3];
    return par[1]*TMath::Exp(-(x[0]-par[0])*tf)+par[2]*TMath::Exp(-(x[0]-par[0])*ts);
}

/*

void show(int k)
{
  TFile *rootfile=new TFile("/home/xujh/9Be+187Re_data/Ge_CsI_wave/data_C2_2063_2063_wave.root");
  //"/home/xujh/Ge_CsI_data1/data_C2_3375_3375_wave.root"
  if (rootfile->IsZombie()) {
   cout << "Error opening file" << endl;
   exit(-1);
  }
  rootfile->cd();
  TTree *tree=(TTree*)rootfile->Get("tree");
  Long64_t nentries=tree->GetEntries();
   Short_t         sr;
   Bool_t          pileup;
   Bool_t          outofr;
   Short_t         cid;
   Short_t         sid;
   Short_t         ch;
   UShort_t        evte;
   Long64_t        ts;
   Short_t         cfd;
   Bool_t          cfdft;
   Short_t         cfds;
   UShort_t        ltra;
   UShort_t        data[500];
   tree->SetBranchAddress("sr", &sr);
   tree->SetBranchAddress("pileup", &pileup);
   tree->SetBranchAddress("outofr", &outofr);
   tree->SetBranchAddress("cid", &cid);
   tree->SetBranchAddress("sid", &sid);
   tree->SetBranchAddress("ch", &ch);
   tree->SetBranchAddress("evte", &evte);
   tree->SetBranchAddress("ts", &ts);
   tree->SetBranchAddress("cfd", &cfd);
   tree->SetBranchAddress("cfdft", &cfdft);
   tree->SetBranchAddress("cfds", &cfds);
   tree->SetBranchAddress("ltra", &ltra);
   tree->SetBranchAddress("data", data);
   
   tree->GetEntry(k);
   
   if(cid==1 && ltra==160 && outofr==0)
   {
    double *waveform=new double[160];
    int t0=check_t0(data);
    double sum_thitak=0.0,sum_thitaksquare=0.0,sum_y=0.0,sum_y_T_thitak=0.0;
    double a=0.0,b=0.0;
    double para=double(PARA)/16.;
    double x[160]={0.};
    for (int i=0;i<t0;i++)
    {
     sum_thitak+=exp(-floor(i)/para);
     sum_thitaksquare+=exp(-floor(i)/para)*exp(-floor(i)/para);
     sum_y+=double(data[i]);
     sum_y_T_thitak+=double(data[i])*exp(-floor(i)/para);
     
    }
    //for (int i=0;i<t0;i++)  baseline += double(waveform[i]);
    a = (sum_thitaksquare*sum_y - sum_thitak*sum_y_T_thitak)/(double(t0)*sum_thitaksquare - sum_thitak*sum_thitak);
    b = (sum_thitak*sum_y - double(t0)*sum_y_T_thitak)/(sum_thitak*sum_thitak - double(t0)*sum_thitaksquare);
    for(int i=0;i<apd_Range;i++)  
    {
      waveform[i] = double(data[i])-(a + b*exp(-(floor(i))/para));
      x[i]=double(i);
    }
    
    TGraph *ggga = new TGraph(ltra,x,waveform);
    //for(int i=0;i<apd_Range;i++)  ggga->SetPoint(i,i,waveform[i]);
    double max=finmax(waveform);
    TF1 *fcsi;
    if(sid==2 && (ch==1 || ch==3 || ch==6))
    {
      fcsi = new TF1("fcsi",CsIfun_gagg, 0,apd_Range,3);////////////////////
    }
    else
    {
      fcsi = new TF1("fcsi",CsIfun, 0,apd_Range,3);
    }
    
    fcsi->SetParameters(60.,0.,0.);
    ggga->Fit("fcsi","Q");
 	  // = fcsi->GetParameter(0);
    double f = fcsi->GetParameter(1);
    double s = fcsi->GetParameter(2);  
   cout<<"sid="<<sid<<" "<<"ch="<<ch<<endl;
   cout<<"f="<<f<<endl;
   cout<<"s="<<s<<endl;
   ggga->Draw();
   fcsi->Draw("same");
  }
  else
  {
    cout<<"please enter a new Entry"<<endl;
  }
   
   
}







*/


//int main ()///root .L
int main (int argc, char *argv[])////make
//int root_fit (int argc, char *argv[])
{

  if(argc != 2)
    {
      std::cout<<"error(argc != 2)      "<<argv[0]<<"  [RunNnumber]"<<std::endl;
      return 1;
    }

  TString RunNumber(argv[1]);
  int  runnumber = RunNumber.Atoi();
//////////tree ����

  //char filename[127];
  //sprintf(filename,"/home/xujh/7Li+186W_code/CsI_data/data_C1_%d_wave.root",number);
  cout<<1<<endl;
  //int number=3320;
  //TFile *rootfile=new TFile("/home/ljz/2024_2025/decode/data_C1_1009_wave.root");
  //TFile *rootfile=new TFile(TString::Format("/home/ljz/2024_2025/decode/data_C1_%04d_wave.root",runnumber).Data()); 
  TFile *rootfile=new TFile(TString::Format("/home/zhy/Desktop/sort/CsI_Decode/data_C1_%04d_wave.root",runnumber).Data()); 
  
  if (rootfile->IsZombie()) {
   cout << "Error opening file" << endl;
   exit(-1);
  }
  rootfile->cd();
  TTree *tree=(TTree*)rootfile->Get("tree");
  Long64_t nentries=tree->GetEntries();
   Short_t         sr;
   Bool_t          pileup;
   Bool_t          outofr;
   Short_t         cid;
   Short_t         sid;
   Short_t         ch;
   UShort_t        evte;
   Long64_t        ts;
   Short_t         cfd;
   Bool_t          cfdft;
   Short_t         cfds;
   UShort_t        ltra;
   UShort_t        data[500];
   tree->SetBranchAddress("sr", &sr);
   tree->SetBranchAddress("pileup", &pileup);
   tree->SetBranchAddress("outofr", &outofr);
   tree->SetBranchAddress("cid", &cid);
   tree->SetBranchAddress("sid", &sid);
   tree->SetBranchAddress("ch", &ch);
   tree->SetBranchAddress("evte", &evte);
   tree->SetBranchAddress("ts", &ts);
   tree->SetBranchAddress("cfd", &cfd);
   tree->SetBranchAddress("cfdft", &cfdft);
   tree->SetBranchAddress("cfds", &cfds);
   tree->SetBranchAddress("ltra", &ltra);
   tree->SetBranchAddress("data", data);
  

   // List of branches
   ////////tree ����
   
   ///////outfile
   //TFile *opf = new TFile("./fit_csi_1009.root","RECREATE");
   TFile *opf = new TFile(TString::Format("./fit_Result/fit_csi_%04d_2.root",runnumber).Data(),"RECREATE");
   TTree *opt = new TTree("tree","Tree");
   /*
     Short_t sr1=0;
    Bool_t  pileup1=0;
    Bool_t  outofr1=0;
    Short_t cid1=0;
    Short_t sid1=0;
    Short_t ch1=0;
    UShort_t evte1=0;
    Long64_t ts1=0;
    Short_t cfd1=0;
    Bool_t cfdft1=0;
    Short_t cfds1=0;
    UShort_t ltra1;
    //CSI的拟合后的信�?
    Double_t max1=0;
    Double_t f1=0;
    Double_t s1=0;
    Short_t sign1=0;
    
    //opt->Branch("sign",&sign1);
    opt->Branch("sr",&sr1);
    opt->Branch("pileup",&pileup1);
    opt->Branch("outofr",&outofr1);
    opt->Branch("cid",&cid1);
    opt->Branch("sid",&sid1);
    opt->Branch("ch",&ch1);
    opt->Branch("evte",&evte1);
    opt->Branch("ts",&ts1);
    opt->Branch("cfd",&cfd1);
    opt->Branch("cfdft",&cfdft1);
    opt->Branch("ltra",&ltra1);
    opt->Branch("cfds",&cfds1);
    opt->Branch("max",&max1);
    opt->Branch("f",&f1);
    opt->Branch("s",&s1);
*/
    Double_t f=0.;
    Double_t s=0.;
    Double_t trc=0.;
    Double_t max=0;
  
    opt->Branch("sr",&sr,"sr/S");
    opt->Branch("pileup",&pileup,"pileup/O");
    opt->Branch("outofr",&outofr,"outofr/O");
    opt->Branch("cid",&cid,"cid/S");
    opt->Branch("sid",&sid,"sid/S");
    opt->Branch("ch",&ch,"ch/S");
    opt->Branch("evte",&evte,"evte/s");
    opt->Branch("ts",&ts,"ts/L");
    opt->Branch("cfd",&cfd,"cfd/S");
    opt->Branch("cfdft",&cfdft,"cfdft/O");
    opt->Branch("ltra",&ltra,"ltra/s");
    opt->Branch("cfds",&cfds,"cfds/S");
    opt->Branch("max",&max,"max/D");
    opt->Branch("f",&f,"f/D");
    opt->Branch("s",&s,"s/D");
    opt->Branch("trc",&trc,"trc/D");

/*
      sr1=sr;
      pileup1=pileup;
      outofr1=outofr;
      cid1=cid;
      sid1=sid;
      ch1=ch;
      evte1=evte;
      ts1=ts;
      cfd1=cfd;
      cfdft1=cfdft;
      cfds1=cfds;
     //csils
     */
    int pileup_flag=0;
    int flow_flag=0;
    TGraph *ggga=NULL;
    TF1 *fcsi=NULL;
    
  // for(Long64_t i=0;i<nentries;i++){///////////////////////////////////loop start   nentries10000000nentries
  for(Long64_t i=0;i<100000;i++){///////////////////////////////////loop start   nentries10000000nentries
  //sprintf(strtest,"e%i",i+1);

  if(i%10000 == 0)  //std::cout << i<<" / 10000" <<std::endl;
  {
    std::cout<<"\r"<<"Entry: "<<i<<"  |  Event: "<<nentries;
    std::cout << std::flush;
  }
  tree->GetEntry(i);

  max=0.;
  f=0.;
  s=0.;
  
  
  if(cid==0 && sid<=8)
  {
      //sign1=0;
      
      max=-1.;
      f=-1.;
      s=-1.;
      opt->Fill();
      //continue;
  }
  // if(cid==1 && ltra==160 && outofr==0 && pileup == 0 &&(sid ==2|3|4|5|6|7|8))//////apd
  if(cid==1 && ltra==160 && outofr==0 && pileup == 0 &&(sid == 7 && ch==14))//////apd
  {
    double waveform[160]={0.};
    int t0=check_t0(data);
    double sum_thitak=0.0,sum_thitaksquare=0.0,sum_y=0.0,sum_y_T_thitak=0.0;
    double a=0.0,b=0.0;
    double para=double(PARA)/16.;
    double x[160]={0.};
    for (int i=0;i<t0;i++)
    {
     sum_thitak+=exp(-floor(i)/para);
     sum_thitaksquare+=exp(-floor(i)/para)*exp(-floor(i)/para);
     sum_y+=double(data[i]);
     sum_y_T_thitak+=double(data[i])*exp(-floor(i)/para);
     
    }
    //for (int i=0;i<t0;i++)  baseline += double(waveform[i]);
    a = (sum_thitaksquare*sum_y - sum_thitak*sum_y_T_thitak)/(double(t0)*sum_thitaksquare - sum_thitak*sum_thitak);
    b = (sum_thitak*sum_y - double(t0)*sum_y_T_thitak)/(sum_thitak*sum_thitak - double(t0)*sum_thitaksquare);
    for(int i=0;i<apd_Range;i++)  
    {
      waveform[i] = double(data[i])-(a + b*exp(-(floor(i))/para));
      x[i]=double(i);
    }
    /*
    ///////////
    int CheckPileup = check_pileup(waveform);   ///// add for checking pileup
    if(CheckPileup !=0) continue;
    ///////////
    */
    fcsi = new TF1("fcsi",CsIfun, 0,apd_Range,4);
    ggga = new TGraph(ltra,x,waveform);
    //for(int i=0;i<apd_Range;i++)  ggga->SetPoint(i,i,waveform[i]);
    max=finmax(waveform);
  
    
    
  
    fcsi->SetParameters(60.,0.,0.,55.);
    ggga->Fit("fcsi","Q");
    // = fcsi->GetParameter(0);
    f = fcsi->GetParameter(1);
    s = fcsi->GetParameter(2);
	  trc = fcsi->GetParameter(3);    
    if(f!=0. && s!=0.)  opt->Fill();


    //////////////////////////////////////////////////////////////////////////show fit result
        // 创建TCanvas来绘制图像
        TCanvas *canvas = new TCanvas("canvas", "Fitting Results", 800, 600);
        
        // 绘制数据点和拟合曲线
        ggga->Draw("AL"); // "A"表示数据点，"P"表示点的样式
        fcsi->Draw("same"); // 在同一张图上绘制拟合曲线
        canvas->Update();
        // 保存图片（可选）
        //cout<<"zhy1"<<endl;
        canvas->SaveAs(TString::Format("./fit_Result/png/wave_%04d_sid_%02d_ch_%02d.png",i,sid,ch).Data());
        //cout<<"zhy2"<<endl;
        
        delete canvas; // 删除canvas
    ////////////////////////////////////////////////////////////////////////

      delete ggga;
      delete fcsi;
      
      //delete waveform;


  }


  

  

}

  /*for (Long64_t i = 0; i < 2000000; i++) { 
    if (i % 10000 == 0) // std::cout GetEntry(i);
        max = 0.;
        f = 0.;
        s = 0.;
        
        
    if (cid == 1 && ltra == 160 && outofr == 0 && (sid == 2 || sid == 3 || sid == 4 || sid == 5 || sid == 6 || sid == 7)) { cout<<2<<endl;
        double waveform[160] = {0.};
        int t0 = check_t0(data);
        double sumthitak = 0.0, sumthitaksquare = 0.0, sumy = 0.0, sumyTthitak = 0.0;
        double a = 0.0, b = 0.0;
        double para = double(PARA) / 16.;
        double x[160] = {0.};
        cout<<2<<endl;
        
        // 计算波形
        for (int i = 0; i < t0; i++) {
            sumthitak += exp(-floor(i) / para);
            sumthitaksquare += exp(-floor(i) / para) * exp(-floor(i) / para);
            sumy += double(data[i]);
            sumyTthitak += double(data[i]) * exp(-floor(i) / para);
        }
        
        // 拟合计算a和b
        a = (sumthitaksquare * sumy - sumthitak * sumyTthitak) / (double(t0) * sumthitaksquare - sumthitak * sumthitak);
        b = (sumthitak * sumy - double(t0) * sumyTthitak) / (sumthitak * sumthitak - double(t0) * sumthitaksquare);
        
        // 计算调整后的波形
        for (int i = 0; i < apd_Range; i++) {
            waveform[i] = double(data[i]) - (a + b * exp(-(floor(i)) / para));
            x[i] = double(i);
        }
        
        // 创建TF1拟合函数和TGraph对象
        TF1 *fcsi = new TF1("fcsi", CsIfun, 0, apd_Range, 4);
        TGraph *ggga = new TGraph(ltra, x, waveform);
        
        // 设置拟合函数的参数
        fcsi->SetParameters(60., 0., 0., 55.);
        
        // 拟合
        ggga->Fit("fcsi", "Q");
        
        // 获取拟合参数
        f = fcsi->GetParameter(1);
        s = fcsi->GetParameter(2);
        trc = fcsi->GetParameter(3); 
        
        // 如果拟合参数有效，填充opt
        if (f != 0. && s != 0.) {
            opt->Fill();
        }
        //
        // 创建TCanvas来绘制图像
        TCanvas *canvas = new TCanvas("canvas", "Fitting Results", 800, 600);
        
        // 绘制数据点和拟合曲线
        ggga->Draw("AP"); // "A"表示数据点，"P"表示点的样式
        fcsi->Draw("same"); // 在同一张图上绘制拟合曲线
        canvas->Update();
        // 保存图片（可选）
        cout<<"zhy1"<<endl;
        canvas->SaveAs("fit_results.png");
        cout<<"zhy2"<<endl;
        // 删除对象
        delete ggga;
        delete fcsi;
        //delete canvas; // 删除canvas
    }
}
*/
  opt->Write();
  opf->Write();
  opf->Close();
    
  rootfile->Close();
  //cout<<1<<endl;
  return 0;

}




