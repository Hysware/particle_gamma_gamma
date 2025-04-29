#ifndef ANALYSIS_H_
#define ANALYSIS_H_

#include "set.h"

#include "TBenchmark.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include <vector>
#include <map>
#include <iostream>

#include "raw.h"

//
class analysis
{
public:
  analysis() = default;
  analysis(const std::string &filename_in, const std::string &filename_out);
  ~analysis();

public:
  void ProcessGevsGe();
  void ProcessCsIvsGe();
  void ProcessLaBr3vsGe();
  // void ProcessScvsGe();

private:
  void InitMapTS();

private:
  std::map<int, std::vector<Long64_t>> map_v_ts;

private:
  TBenchmark *benchmark;

  TFile *file_in;
  TTree *tr_in;

  raw *rd;

  Int_t id_Ge;//the first ge channel with data
  Int_t id_CsI;//the first CsI channel with data
  Int_t id_LaBr3;//the first LaBr3 channel with data
  // Int_t id_Si_ring;//the first Si ring channel with data
  // Int_t id_Si_sector;//the first Si sector channel with data
  TFile *file_out;

  // all compare with sid=2 ch=5
  TH1D *h1[4*16];//Ge vs. Ge
  TH1D *h2[7*16];//CsI vs. Ge
  TH1D *h3[1*16];//LaBr3 vs. Ge
  // TH1D *h2[7*16];//Si vs. Ge
  // TH1D *h3[3*16];//Sc vs. Ge
};

#endif
