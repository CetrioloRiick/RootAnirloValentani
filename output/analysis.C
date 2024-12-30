

#include <RtypesCore.h>
bool inRange(Double_t start, Double_t stop, Double_t value) {
  if (value >= start && value <= stop) {
    std::cout << "Dentro range\n";
    return true;
  } else {
    std::cout << "Fouri range\n";
    return false;
  }
}

void analysis() {
  TFile *inputFile = new TFile("histograms.root");

  // PUNTO 1
  TH1F *hTypes = (TH1F *)inputFile->Get("hTypes");
  TCanvas *c0 = new TCanvas("c0", "Generated Particles", 200, 10, 600, 400);
  hTypes->Draw();
  Int_t totPartGen = hTypes->GetEntries();
  if (totPartGen < 1E7 || totPartGen > 1.1E7) {
    cout << "Non sono state generate il numero corretto di particelle\n\n";
  }
  vector<Double_t> percentuali{0, 0.4, 0.4, 0.045, 0.045, 0.05, 0.05, 0.01};
  for (Int_t i{1}; hTypes->GetBinContent(i) != 0; ++i) {
    Double_t error{2 * (hTypes->GetBinError(i))};
    Double_t mean{hTypes->GetBinContent(i)};
    Double_t sigma{hTypes->GetBinError(i)};

    cout << i << " \nRange: " << mean - error << "   -   " << mean + error
         << '\n'
         << "Valore atteso: " << percentuali[i] * totPartGen << '\n'
         << "Distanza in sigma dalla media: "
         << (mean - percentuali[i] * totPartGen) / sigma << '\n';
    inRange(mean - error, mean + error, percentuali[i] * totPartGen);
    cout << "\n\n";
  }

  // PUNTO 2
  // Riempio 2 TH1F, aggiungo ad ogni bin di hTheta il valore di ogni bin di
  // hAngles con la stessa x, analogamente con le y in hPhi
  TH2F *hAngles = (TH2F *)inputFile->Get("hAngles");
  TH1F *hTheta = new TH1F("hTheta", "hTheta", 100, 0., TMath::Pi());
  TH1F *hPhi = new TH1F("hPhi", "hPhi", 100, 0., 2 * TMath::Pi());
  Int_t binsX = hAngles->GetNbinsX();
  Int_t binsY = hAngles->GetNbinsY();

  // Funzioni per il fit dei 2 istogrammi
  TF1 *fTheta = new TF1("fTheta", "[0]", 0., TMath::Pi());
  TF1 *fPhi = new TF1("fPhi", "[0]", 0., 2 * TMath::Pi());

  TCanvas *c1 =
      new TCanvas("c1", "Theta and Phi correlation", 200, 10, 600, 400);
  hAngles->Draw("LEGO1");

  //"Fill" dei 2 istogrammi
  for (Int_t i{0}; i != binsX + 1; ++i) {
    for (Int_t o{0}; o != binsY + 1; ++o) {
      Double_t temp{hAngles->GetBinContent(i, o)};
      hTheta->AddBinContent(i, temp);
      hPhi->AddBinContent(o, temp);
    }
  }

  auto printPar = [](TF1 *func, Int_t numPar) {
    for (Int_t i = 0; i != numPar; i++) {
      cout << "par[" << i << "] :" << func->GetParameter(i) << " +/- "
           << func->GetParError(i) << endl;
    }
    cout << "Chiquadro ridotto: " << func->GetChisquare() / func->GetNDF()
         << "\nProbababilità fit: " << func->GetProb() << '\n';
  };

  TCanvas *c2 = new TCanvas("c2", "Theta correlation", 200, 10, 600, 400);
  hTheta->Draw();
  hTheta->Fit(fTheta);
  printPar(fTheta, 1);

  TCanvas *c3 = new TCanvas("c3", "Phi correlation", 200, 10, 600, 400);
  hPhi->Draw();
  hPhi->Fit(fPhi);
  printPar(fPhi, 1);

  // PUNTO 3
  TH1F *hImpulse = (TH1F *)inputFile->Get("hImpulse");
  TF1 *fImpulse = new TF1("fImpulse", "expo(0)", 0, 10);
  TCanvas *c4 = new TCanvas("c4", "Impulse", 200, 10, 600, 400);
  hImpulse->Draw();
  hImpulse->Fit(fImpulse);
  printPar(fImpulse, 1);

  // PUNTO 4
  TH1F *h1 = (TH1F *)inputFile->Get("hInvariantMassDiscCharge");
  TH1F *h2 = (TH1F *)inputFile->Get("hInvariantMassConcCharge");
  TH1F *h3 = (TH1F *)inputFile->Get("hInvariantMassKPDisc");
  TH1F *h4 = (TH1F *)inputFile->Get("hInvariantMassKPConc");
  TH1F *h5 = (TH1F *)inputFile->Get("hInvariantMassDecad");

  TH1F *sub12 = new TH1F("sub12", "sub12", 100, 0, 2);
  sub12->Add(h1, 1);
  sub12->Add(h2, -1);
  TCanvas *c5 = new TCanvas("c5", "Subtraction 1 - 2", 200, 10, 600, 400);
  sub12->Draw();

  TH1F *sub34 = new TH1F("sub34", "sub34", 100, 0, 2);
  sub34->Add(h3, 1);
  sub34->Add(h4, -1);
  TCanvas *c6 = new TCanvas("c6", "Subtraction 3 - 4", 200, 10, 600, 400);
  sub34->Draw();

  TCanvas *c7 = new TCanvas("c7", "Invariant Mass Decad", 200, 10, 600, 400);
  h5->Draw();
}
