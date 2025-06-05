#include <TROOT.h>
#include <TApplication.h>  // ROOT 应用程序所需的头文件
#include <iostream>
#include <vector>
int run() {
    TCanvas *c1 = new TCanvas;
    // 执行ROOT宏
    int MaxSid =2, MaxCh =4;
    //TCutG *cutg[MaxSid-2][MaxCh] = nullptr;
    std::vector<std::vector<TCutG*>> cutg(MaxSid-1, std::vector<TCutG*>(MaxCh, nullptr));
    for(int sid =2; sid <= MaxSid; sid++)
    {
	    for(int ch =0; ch < MaxCh; ch++)
	    {
   		 TString cutFileName = TString::Format("cut%02d%02d.C", sid, ch);

   		 gROOT->ProcessLine(".L " + cutFileName);
   		 //gROOT->ProcessLine("ctug->Draw()");
   		 cutg[sid-2][ch] = (TCutG*)gROOT->FindObject("CUTG")->Clone(TString::Format("cutg%02d%02d",sid,ch));
   		 if (!cutg[sid-2][ch]) std::cerr << "Error: cutg not found!" << std::endl;
   		 // a[sid-2][ch]->SetLineColor(kRed); 
   		 //cutg[sid-2][ch]->Draw("same"); 
	    }
    }
    c1->Clear();

    // 先创建一个TH2F来设置坐标范围
    TH2F *frame = new TH2F("frame", "Title;X Axis;Y Axis",
                       100, 0, 4000,  // x轴: 100 bins, 范围xmin-xmax
                       100, 0, 16000); // y轴: 100 bins, 范围ymin-ymax
    frame->Draw();  // 先绘制框架


    for(int sid =2; sid <= MaxSid; sid++)
    {
            for(int ch =0; ch < MaxCh; ch++)
            {
		    cutg[sid-2][ch]->Draw("same");
	    }
    }


/*
    gROOT->ProcessLine(".L cut0202.C");
    //gROOT->ProcessLine("ctug->Draw()");
    TCutG *a0202 = (TCutG*)gROOT->FindObject("CUTG")->Clone("cutg0202");
    if (!a0202) std::cerr << "Error: cutg not found!" << std::endl;
    a0202->SetLineColor(3); 
    
    
    gROOT->ProcessLine(".L cut0203.C");
    //gROOT->ProcessLine("ctug->Draw()");
    TCutG *a0203 = (TCutG*)gROOT->FindObject("CUTG")->Clone("cutg0203");
    if (!a0203) std::cerr << "Error: cutg not found!" << std::endl;
    a0203->SetLineColor(30); 
    
    c1->Clear();
    a0000->Draw(); 
    a0202->Draw("same"); 
    a0203->Draw("same"); 
*/
    return 0;
}

