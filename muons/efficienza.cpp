#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <vector>



using namespace std;

void efficienza(){

  vector<double> tensione = {
   1806, 1712, 1604, 1501, 1406, 1304, 1209, 1108 
  }; //double per fare TGraph

  vector<double> countAC = {
    3272, 544, 559, 546, 565, 545, 489, 552
  };

  vector<double> countABC = {
    1928, 339, 335, 342, 363, 126, 19, 3
  };

  vector<double> err_tensione;
  
  vector<double> eff;
  vector<double> err_eff;

  for(int ii=0 ; ii<tensione.size() ; ii++){
    eff.push_back((double)countABC[ii]/countAC[ii]);
    err_eff.push_back(sqrt(eff[ii]*(1-eff[ii])/countAC[ii]));
    err_tensione.push_back(0.0); //aggiungere incertezza tensione!!
  }
  TCanvas *c1 = new TCanvas("c1", "Conteggi AC", 800, 600); 
  TGraph *AC = new TGraph(tensione.size(), &tensione[0], &countAC[0]); //maybe uselessss
  AC->SetTitle("Conteggi AC;Tensione [V];Conteggi AC");
  AC->SetMarkerStyle(20);
  AC->SetMarkerColor(kBlue);
  AC->Draw("AP");


  TCanvas *c2 = new TCanvas("c2", "Conteggi ABC", 800, 600);
  TGraph *ABC = new TGraph(tensione.size(), &tensione[0], &countABC[0]);
  ABC->SetTitle("Conteggi ABC;Tensione [V];Conteggi ABC");
  ABC->SetMarkerStyle(21);
  ABC->SetMarkerColor(kRed);
  ABC->Draw("AP");

  TCanvas *c3 = new TCanvas("c3", "Efficienza", 800, 600);
  TGraphErrors *G_eff = new TGraphErrors(tensione.size(), &tensione[0], &eff[0], &err_tensione[0], &err_eff[0]);
  G_eff->SetTitle("Efficienza;Tensione [V];Efficienza");
  G_eff->SetMarkerStyle(22);
  G_eff->SetMarkerColor(kGreen+2);
  G_eff->Draw("AP");

  c1->Update();
  c2->Update();
  c3->Update();

}
