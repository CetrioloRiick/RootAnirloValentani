

bool inRange(double start, double stop, double value){
    if(value >= start && value <= stop){
        std::cout << "Dentro range\n";
        return true;
    }else{
        std::cout << "Fouri range\n";
        return false;
    }
}

void macro(){
    TFile *inputFile= new TFile("CHIAMAMI-COSI.root");

    TH1F *hTypes=(TH1F*)inputFile->Get("hTypes");
    TCanvas *c0 = new TCanvas("c0", "aaa", 200, 10, 600, 400);
    hTypes->Draw();
    int totalePartGen = hTypes->GetEntries();
    if(totalePartGen < 1E7 || totalePartGen > 1.1E7){
        cout << "Non sono state generate il numero corretto di particelle\n";
    }
    vector<double> percentuali{0, 0.4, 0.4, 0.045, 0.045, 0.05, 0.05, 0.01};
    for(int i{1}; hTypes->GetBinContent(i)!=0; ++i){
        double error{2*(hTypes->GetBinError(i))};
        double mean{hTypes->GetBinContent(i)};
        cout << "di quante sigma siamo fuori " <<  (hTypes->GetBinContent(i)- percentuali[i]*1E7)/hTypes->GetBinError(i) <<'\n';
        cout << mean-error<<"   -   ";
        cout << mean+error<<'\n';
        cout <<"   "<<percentuali[i]*1E7<<'\n';
        inRange(mean-error, mean+error, percentuali[i]*1E7);
        cout<<"\n\n\n";

    }
 // PUNTO 2
 /*Sommo tutti quelli con lo stesso x fillandoli un bin, prendendo gli stessi bin del grafico a 2d, per le x è theta
 Rifaccio la stessa cosa per le y, tra zero e 2pi
 faccio il fit con una funzione costante in entrambe e faccio stampare il chiquadro ridotto e la probabilità del fit*/
    TH2F *hAngles=(TH2F*)inputFile->Get("hAngles");
    TH1F *hTheta = new TH1F("hTheta", "hTheta", 100, 0., TMath::Pi());
    TH1F *hPhi = new TH1F("hPhi", "hPhi", 100, 0., 2*TMath::Pi());
    Int_t binsX=hAngles->GetNbinsX();
    cout << "numero di binX " << binsX << '\n';
    Int_t binsY=hAngles->GetNbinsY();
    cout << "numero di binY " << binsY << '\n';

    TF1 *fTheta = new TF1("fTheta", "[0]", 0., TMath::Pi());
    TF1 *fPhi = new TF1("fPhi", "[0]", 0., 2*TMath::Pi());

    TCanvas *c1 = new TCanvas("c1", "bbb", 200, 10, 600, 400);
    hAngles->Draw("LEGO1");
    for(int i{0}; i!=binsX+1; ++i){
        for(int o{0}; o!=binsY+1; ++o){
             //   sleep(0.1);

           double temp{hAngles->GetBinContent(i, o)};
           hTheta->AddBinContent(i, temp);
           hPhi->AddBinContent(o, temp);
        }
    }

    TCanvas *c2 = new TCanvas("c2", "ccc", 200, 10, 600, 400);
    hTheta->Draw();
    hTheta->Fit(fTheta);
    for (Int_t i = 0; i < 1; i++){
        cout << "par[" << i << "] :" << fTheta->GetParameter(i) << " +/- "
         << fTheta->GetParError(i) << endl;
         }
    cout << " Chiquadro ridotto: " << fTheta->GetChisquare() / fTheta->GetNDF() << endl;
    cout << "Probababilità fit: "<< fTheta->GetProb() << endl;

    TCanvas *c3 = new TCanvas("c3", "ddd", 200, 10, 600, 400);
    hPhi->Draw();
    hPhi->Fit(fPhi);
    for (Int_t i = 0; i < 1; i++){
        cout << "par[" << i << "] :" << fPhi->GetParameter(i) << " +/- "
         << fPhi->GetParError(i) << endl;
         }
    cout << " Chiquadro ridotto: " << fPhi->GetChisquare() / fPhi->GetNDF() << endl;
    cout << "Probababilità fit: "<< fPhi->GetProb() << endl;
    
    /* TCanvas *c1 = new TCanvas("c1", "", 200, 10, 600, 400);
    hTheta->Draw();
    TCanvas *c2 = new TCanvas("c2", "", 200, 10, 600, 400);
    hPhi->Draw(); */
    //TF1* fTheta = new TF1("f", "[0]", 0., TMath::Pi());

// PUNTO 3
/*Fare un fit con una funzione esponenziale per il grafico dell'impulso, e^-[0]x,
Stampare a schermo i valori dei parametri chiesti*/
    TH1F *hImpulse=(TH1F*)inputFile->Get("hImpulse");
    TF1 *impulseFit= new TF1("impulseFit", "expo(0)", 0, 10);
    TCanvas *c4 = new TCanvas("c4", "eee", 200, 10, 600, 400);
    hImpulse->Draw();
    hImpulse->Fit(impulseFit);
    for (Int_t i = 0; i < 2; i++){
        cout << "par[" << i << "] :" << impulseFit->GetParameter(i) << " +/- "
         << impulseFit->GetParError(i) << endl;
         }
    cout << " Chiquadro ridotto: " << impulseFit->GetChisquare() / impulseFit->GetNDF() << endl;
    cout << "Probababilità fit: "<< impulseFit->GetProb() << endl;

// PUNTO 4
    TH1F *h1=(TH1F*)inputFile->Get("hInvariantMassDiscCharge");
    TH1F *h2=(TH1F*)inputFile->Get("hInvariantMassConcCharge");
    TH1F *h3=(TH1F*)inputFile->Get("hInvariantMassKPDisc");
    TH1F *h4=(TH1F*)inputFile->Get("hInvariantMassKPConc");
    TH1F *h5=(TH1F*)inputFile->Get("hInvariantMassDecad");
    

    TH1F *sub12= new TH1F("sub12", "sub12", 1000, 0, 10);
    sub12->Add(h1, 1);
    sub12->Add(h2, -1);

    TCanvas *c5 = new TCanvas("c5", "fff", 200, 10, 600, 400);
    sub12->Draw();



    TH1F *sub34= new TH1F("sub34", "sub34", 1000, 0, 10);
    sub34->Add(h3, 1);
    sub34->Add(h4, -1);

    TCanvas *c6 = new TCanvas("c6", "ggg", 200, 10, 600, 400);
    sub34->Draw();

    TCanvas *c7 = new TCanvas("c7", "hhh", 200, 10, 600, 400);
    h5->Draw();
}
