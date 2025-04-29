// UserDefine.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 10月 20 16:16:28 2017 (+0800)
// Last-Updated: 六 2月 17 13:53:03 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 55
// URL: http://wuhongyi.cn 

// The user needs to modify the parameters in this file.

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef _USERDEFINE_H_
#define _USERDEFINE_H_

//#define WAVEFORM
// #define ENERGYSUM
// #define QDCSUM
// #define EXTERNALTS

//#define Crate0
#define Crate0
// #define Crate2
// #define Crate3



#define ROOTFILEPATH "/home/zhy/Desktop/sort/Ge_Decode/"  //The path to generate the ROOT file
//#define ROOTFILEPATH "/home/ljz/2024_2025/expdata/decodedata/"  //The path to generate the ROOT file
// #define ROOTFILEPATH "/home/nsgzjn3/data_zjn/196Hg/rootfile/"  //The path to generate the ROOT file
#define ROOTFILENAME "data"
#define TimesHist 3600  //单位秒，为了方便查看每个通道计数率随时间的变化，记录的数据中还包括每个通道的直方图，每个 bin 为 1秒。

#define TIMEBUFF 1000000000  //1s
#define PROCESSBUFF 0.9 //(0,1.0]
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#define Crate0RAWFILEPATH "/home/zhy/Desktop/sort/Ge_ExpData/"   //Path to the original binary
//#define Crate0RAWFILEPATH "/home/ljz/2024_2025/"   //Path to the original binary
// #define Crate0RAWFILEPATH "/media/nsgzjn3/G/196Hg/data11/dataer/"   //Path to the original binary
#define Crate0RAWFILENAME "data"                   //The file name of the original file
#define Crate0num 4   //Number of modules used in this crate
const unsigned short Crate0SamplingRate[Crate0num] = {250,250,250,250};//Specify the sampling rate of each modules separately; 100/250/500 sampling rates; 0 to skip the module
const unsigned short Crate0Revision[Crate0num] = {15,15,15,15};//RevD=13, RevF=15, RevH=17


#define Crate1RAWFILEPATH "/home/ljz/2024_2025/expdata/"   //Path to the original binary
#define Crate1RAWFILENAME "data"                   //The file name of the original file
#define Crate1num 8   //Number of modules used in this crate
const unsigned short Crate1SamplingRate[Crate1num] = {100,100,100,100,100,100,250,250};//Specify the sampling rate of each modules separately; 100/250/500 sampling rates; 0 to skip the module
const unsigned short Crate1Revision[Crate1num] = {15,15,15,15,15,15,15,15};


#define Crate2RAWFILEPATH "/home/wuhongyi/data/"   //Path to the original binary
#define Crate2RAWFILENAME "data"                   //The file name of the original file
#define Crate2num 6   //Number of modules used in this crate
const unsigned short Crate2SamplingRate[Crate2num] = {100,100,100,100,100,100};//Specify the sampling rate of each modules separately; 100/250/500 sampling rates; 0 to skip the module
const unsigned short Crate2Revision[Crate2num] = {15,15,15,15,15,15};

#define Crate3RAWFILEPATH "/home/wuhongyi/data/"   //Path to the original binary
#define Crate3RAWFILENAME "data"                   //The file name of the original file
#define Crate3num 6   //Number of modules used in this crate
const unsigned short Crate3SamplingRate[Crate3num] = {100,100,100,100,100,100};//Specify the sampling rate of each modules separately; 100/250/500 sampling rates; 0 to skip the module
const unsigned short Crate3Revision[Crate3num] = {15,15,15,15,15,15};



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Example
// For example, there are 5 100MHz modules

// #define Crate0num 5
// const unsigned short Crate0SamplingRate[Crate0num] = {100,100,100,100,100};
// const unsigned short Crate0Revision[Crate0num] = {15,15,15,15,15};



#endif /* _USERDEFINE_H_ */
// 
// UserDefine.hh ends here
