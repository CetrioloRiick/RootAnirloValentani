#include "Particle.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TRandom.h"
#include <TApplication.h>
#include <TFile.h>
#include <TH1.h>
#include <algorithm>
#include <iostream>

/* int main()
{
    ParticleType particleType1("protone", 2.5, 4);
    ResonanceType particleType2("neutrone", 3.43, -1, 0.001);
    particleType1.PrintData();
    particleType2.PrintData();
    ParticleType *test[2];
    test[0]=new ParticleType("pione+",1.7,1);
    test[1]=new ResonanceType("pione0",1.9,0,0.23);
    for(int i=0;i<2;i++)test[i]->PrintData();
    return 0;
} */

int main(int argc, char **argv) {
  TApplication app("app", &argc, argv);

  Particle::AddParticleType("pi+", 0.13957, 1);
  Particle::AddParticleType("pi-", 0.13957, -1);
  Particle::AddParticleType("P+", 0.93827, 1);
  Particle::AddParticleType("P-", 0.93827, -1);
  Particle::AddParticleType("K+", 0.49367, 1);
  Particle::AddParticleType("K-", 0.49367, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.050);
  Particle::PrintParticleTypes();

  Particle particle2("K*", {1., 0., 3.});

  // particle2.SetImpulse({1, 1, 1});
  const int nGen{100};
  const int N{nGen + 50};
  const int nEvents{10000}; // aggiungere 2 zeri
  int j;
  TH1F *hTypes = new TH1F("hTypes", "particle numbers", 7, 0, 7);
  TH2F *hAngles =
      new TH2F("hAngles", "", 100, 0, TMath::Pi(), 100, 0, 2 * TMath::Pi());
  TH1F *hImpulse = new TH1F("hImpulse", "", 1000, 0, 10);
  TH1F *hEnergy = new TH1F("hEnergy", "", 1000, 0, 10);
  TH1F *hTransversImpulse = new TH1F("hTransversImpulse", "", 40, 0, 3);
  TH1F *hInvariantMass = new TH1F("hInvariantMass", "", 500, 0, 10);
  TH1F *hInvariantMassDiscCharge =
      new TH1F("hInvariantMassDiscCharge", "", 100, 0, 2);
 // hInvariantMassDiscCharge->Sumw2();
  TH1F *hInvariantMassConcCharge =
      new TH1F("hInvariantMassConcCharge", "", 100, 0, 2);
 // hInvariantMassConcCharge->Sumw2();
  TH1F *hInvariantMassKPConc = new TH1F("hInvariantMassKPConc", "", 100, 0, 2);
//  hInvariantMassKPConc->Sumw2();
  TH1F *hInvariantMassKPDisc = new TH1F("hInvariantMassKPDisc", "", 100, 0, 2);
//  hInvariantMassKPDisc->Sumw2();
  TH1F *hInvariantMassDecad = new TH1F("hInvariantMassDecad", "", 100, 0, 2);

  gRandom->SetSeed();
  double controllo{0};

  for (int i{nEvents}; i != 0; --i) {

    std::array<Particle, N> EventParticle{};
    // double theta = 0., phi = 0., Ptot;
    j = nGen;

    // Funzione per generare casualmente impulso in direzioni casuali
    auto generateImpulse = [&]() -> PhysVector {
      double theta = gRandom->TRandom::Uniform(0, TMath::Pi());
      double phi = gRandom->TRandom::Uniform(0, 2 * TMath::Pi());
      double Ptot = gRandom->TRandom::Exp(1.);
      hAngles->Fill(theta, phi);
      hImpulse->Fill(Ptot);

      return Ptot * PhysVector{cos(phi) * sin(theta), sin(phi) * sin(theta),
                               cos(theta)};
    };

    // Funzione per determinare l'indice della particella in base a x
    auto generateParticleName = [&](double x) -> std::string {
      if (x < 0.35)
        return "pi+";
      if (x < 0.7)
        return "pi-";
      if (x < 0.75)
        return "K+";
      if (x < 0.8)
        return "K-";
      if (x < 0.85)
        return "P+";
      if (x < 0.9)
        return "P-";
      return "K*";
    };

    // Iterazione sugli eventi
    std::for_each_n(EventParticle.begin(), nGen, [&](Particle &p) {
      p.SetImpulse(generateImpulse());

      double x = gRandom->Rndm();
      std::string name = generateParticleName(x);
      p.SetIndex(name);

      if (name == "K*") {
        if (x < 0.95) {
          EventParticle[j].SetIndex("pi+");
          EventParticle[j + 1].SetIndex("K-");
          // hTypes->Fill(p.GetIndex());

        } else {
          EventParticle[j].SetIndex("K+");
          EventParticle[j + 1].SetIndex("pi-");
          // hTypes->Fill(p.GetIndex());
        }
        p.Decay2body(EventParticle[j], EventParticle[j + 1]);
        hInvariantMassDecad->Fill(
            EventParticle[j].InvMass(EventParticle[j + 1]));

        j += 2; // Avanzare il contatore per gli eventi successivi
      }

      hTypes->Fill(p.GetIndex());

      double It{std::sqrt(std::pow(p.GetImpulse().x, 2) + std::pow(p.GetImpulse().y, 2))};
      hTransversImpulse->Fill(It);

      hEnergy->Fill(p.GetEnergy());
    });

    double papaFrancesco;
    for (int s{0}; s != j - 1; ++s) {
      for (int k{s + 1}; k != j; ++k) {
        controllo++;
        papaFrancesco = EventParticle[s].InvMass(EventParticle[k]);
        // std::cout << s << " - " << k << " " << papaFrancesco << '\n';
        hInvariantMass->Fill(papaFrancesco);
        if (EventParticle[s].GetCharge() * EventParticle[k].GetCharge() == -1) {
          hInvariantMassDiscCharge->Fill(papaFrancesco);
        } else if (EventParticle[s].GetCharge() *
                       EventParticle[k].GetCharge() ==
                   1) {
          hInvariantMassConcCharge->Fill(papaFrancesco);
        }
        if ((EventParticle[s].GetParticleName() == "K+" &&
             EventParticle[k].GetParticleName() == "pi-") ||
            (EventParticle[s].GetParticleName() == "K-" &&
             EventParticle[k].GetParticleName() == "pi+")) {
          hInvariantMassKPDisc->Fill(papaFrancesco);
        }
        if ((EventParticle[s].GetParticleName() == "K+" &&
             EventParticle[k].GetParticleName() == "pi+") ||
            (EventParticle[s].GetParticleName() == "K-" &&
             EventParticle[k].GetParticleName() == "pi-")) {
          hInvariantMassKPConc->Fill(papaFrancesco);
        }
      }
    }
  }
    std::cout << "\n\n\n\n" << controllo << "\n\n\n";

  TCanvas *c1 = new TCanvas("c1", "Generated Particles", 200, 10, 600, 400);
  hTypes->Draw();
  TCanvas *c2 = new TCanvas("c2", "Theta Phi correlation", 200, 10, 600, 400);
  hAngles->Draw("LEGO1");
  TCanvas *c3 = new TCanvas("c3", "Particle Energy", 200, 10, 600, 400);
  hEnergy->Draw();
  TCanvas *c4 = new TCanvas("c4", "Impulse", 200, 10, 600, 400);
  hImpulse->Draw();
  TCanvas *c5 = new TCanvas("c5", "Tranverse Impulse", 200, 10, 600, 400);
  hTransversImpulse->Draw();
  TCanvas *c6 = new TCanvas("c6", "Invariant Mass Total", 200, 10, 600, 400);
  hInvariantMass->Draw();
    TH1F *addDiscConc= new TH1F("addDiscConc", "addDiscConc", 500, 0, 2);
    addDiscConc->Add(hInvariantMassDiscCharge, 1);
    addDiscConc->Add(hInvariantMassConcCharge, 1);
    addDiscConc->Draw("same");
    TH1F *Diff= new TH1F("Diff", "Diff", 500, 0, 10);
    Diff->Add(hInvariantMass, 1);
    Diff->Add(addDiscConc, -1);
    Diff->Draw("same");
  TCanvas *c7 =
      new TCanvas("c7", "Invariant Mass All Discord", 200, 10, 600, 400);
  // Double_t scale = 1/hInvariantMassDiscCharge->Integral();
  // hInvariantMassDiscCharge->Scale(scale);
  hInvariantMassDiscCharge->Draw();
  TCanvas *c8 =
      new TCanvas("c8", "Invariant Mass Alll Concord", 200, 10, 600, 400);
  // scale = 1/hInvariantMassConcCharge->Integral();
  // hInvariantMassConcCharge->Scale(scale);
  hInvariantMassConcCharge->Draw();
  TCanvas *c9 = new TCanvas(
      "c9", "Invariant Mass pione+/Kaone- e pione-/Kaone+", 200, 10, 600, 400);
  // scale = 1/hInvariantMassKPDisc->Integral();
  // hInvariantMassKPDisc->Scale(scale);
  hInvariantMassKPDisc->Draw();
  TCanvas *c10 = new TCanvas(
      "c10", "Invariant Mass pione+/Kaone+ e pione-/Kaone-", 200, 10, 600, 400);
  // scale = 1/hInvariantMassKPConc->Integral();
  // hInvariantMassKPConc->Scale(scale);
  hInvariantMassKPConc->Draw();
  TCanvas *c11 = new TCanvas("c11", "Invariant Mass Decad", 200, 10, 600, 400);
  hInvariantMassDecad->Draw();

  /*

    std::for_each_n(EventParticle.begin(), nGen,
                    [&](Particle &p) { // Sarebbe meglio mettere generate
                      theta = gRandom->TRandom::Uniform(0, TMath::Pi());
                     c1 phi = gRandom->TRandom::Uniform(0, 2 * TMath::Pi());
                      Ptot = gRandom->TRandom::Exp(1.);

                      p.SetImpulse(Ptot * PhysVector{cos(phi) * sin(theta),
                     c1                                sin(phi) * sin(theta),
                                                     cos(theta)});
                      double x = gRandom->Rndm();
                      if (x < 0.4)
                        p.SetIndex("pi+");
                      else if (x < 0.8)
                        p.SetIndex("pi-");
                      else if (x < 0.85)
                        p.SetIndex("K+");
                      else if (x < 0.9)
                        p.SetIndex("K-");
                      else if (x < 0.945)
                        p.SetIndex("P+");
                      else if (x < 0.99)
                        p.SetIndex("P-");
                      else {
                        p.SetIndex("K*");
                        if (x < 0.995) {
                          EventParticle[j].SetIndex("pi+");
                          EventParticle[j + 1].SetIndex("K-");
                        } else {
                          EventParticle[j].SetIndex("K+");
                          EventParticle[j + 1].SetIndex("pi-");
                        }
                        p.Decay2body(EventParticle[j], EventParticle[j + 1]);
                        j += 2;
                      }
                    });

                    */

  /*Particle particle1("K+", {2., 4., 1});
  Particle particle2("K*", {1., 0., 3.});

  std::cout << "Indice  particle1: " << particle1.GetIndex() << std::endl;
  std::cout << "Impulso particle1: " << particle1.GetImpulse() << std::endl;
  std::cout << "Indice  particle2: " << particle2.GetIndex() << std::endl;
  std::cout << "Impulso particle2: " << particle2.GetImpulse() << std::endl;
  // Particle::GetParticleTypes()[0]->PrintData();
  Particle::GetParticleTypes()[1]->PrintData(); */

  /*
    ResonanceType pippo{"K+", 0.493, 1, 0.05};
    auto pluto = Particle::GetParticleTypes();
    auto it=pluto.begin();
    it++;

    */
  // it->->PrintData();
  /*
  ParticleType *pippop{&pippo};
  pippop->PrintData();*/
  /*
    ResonanceType pippo{"K+", 0.493, 1, 0.05};
    ParticleType pluto{"K+", 0.493, 1};
    ParticleType *pippop{&pluto};

    pippop->PrintData();

    pippop = &pippo;

    pippop->PrintData();
  */
  // Particle::GetParticleTypes()[0]->PrintData();
  // Particle::GetParticleTypes()[1]->GetWidth();

  TFile *outputFile = new TFile("output_histograms.root", "RECREATE");
  hTypes->Write();
  hAngles->Write();
  hImpulse->Write();
  hEnergy->Write();
  hTransversImpulse->Write();
  hInvariantMass->Write();
  hInvariantMassDiscCharge->Write();
  hInvariantMassConcCharge->Write();
  hInvariantMassKPConc->Write();
  hInvariantMassKPDisc->Write();
  hInvariantMassDecad->Write();
  outputFile->Close();
  app.Run();
}


