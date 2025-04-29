#include "analysis.h"

#include <iostream>
#include <fstream>
#include <assert.h>
#include <stdlib.h>

#include "TString.h"

int main(int argc, char const *argv[])
{
  if(argc != 2){
    std::cout << "need parameter" << std::endl;
    std::cout << "like: analysis 33" << std::endl;
    return -1;
  }

  int run = atoi(argv[1]);
  TString file_in = TString::Format("/home/zhy/Desktop/sort/C2_Decode/data_C2_%04d_%04d_wave.root", run, run);
  std::cout << "analysis " << file_in << std::endl;
  
  TString file_out = TString::Format("./ts_result/data%04d_ts.root", run);

  analysis *ana = new analysis(file_in.Data(), file_out.Data());
  ana->ProcessGevsGe();
  ana->ProcessCsIvsGe();
  // ana->ProcessLaBr3vsGe();

  delete ana;

  return 0;
}
