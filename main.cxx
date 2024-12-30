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

int main(int argc, char **argv) {
  TApplication app("app", &argc, argv);

  // Aggiunta di tutti i tipi di particelle
  Particle::AddParticleType("pi+", 0.13957, 1);
  Particle::AddParticleType("pi-", 0.13957, -1);
  Particle::AddParticleType("P+", 0.93827, 1);
  Particle::AddParticleType("P-", 0.93827, -1);
  Particle::AddParticleType("K+", 0.49367, 1);
  Particle::AddParticleType("K-", 0.49367, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.050);
  Particle::PrintParticleTypes();

  const Int_t nGen{100};    // Particelle generate sicuramente
  const Int_t N{nGen + 20}; // Particelle massime generabili (lunghezza array)
  const Int_t nEvents{10000};
  Int_t j; // Contatore per numero di particelle generate effettive

  // Creazione di tutti gli istogrammi
  TH1F *hTypes = new TH1F("hTypes", "particle numbers", 7, 0, 7);
  TH2F *hAngles =
      new TH2F("hAngles", "", 100, 0, TMath::Pi(), 100, 0, 2 * TMath::Pi());
  TH1F *hImpulse = new TH1F("hImpulse", "", 1000, 0, 10);
  TH1F *hEnergy = new TH1F("hEnergy", "", 1000, 0, 10);
  TH1F *hTransversImpulse = new TH1F("hTransversImpulse", "", 40, 0, 3);
  TH1F *hInvariantMass = new TH1F("hInvariantMass", "", 100, 0, 10);
  TH1F *hInvariantMassDiscCharge =
      new TH1F("hInvariantMassDiscCharge", "", 100, 0, 2);
  hInvariantMassDiscCharge->Sumw2();
  TH1F *hInvariantMassConcCharge =
      new TH1F("hInvariantMassConcCharge", "", 100, 0, 2);
  hInvariantMassConcCharge->Sumw2();
  TH1F *hInvariantMassKPConc = new TH1F("hInvariantMassKPConc", "", 100, 0, 2);
  hInvariantMassKPConc->Sumw2();
  TH1F *hInvariantMassKPDisc = new TH1F("hInvariantMassKPDisc", "", 100, 0, 2);
  hInvariantMassKPDisc->Sumw2();
  TH1F *hInvariantMassDecad = new TH1F("hInvariantMassDecad", "", 100, 0, 2);

  gRandom->SetSeed(); // SetSeed per l'estrazione casuale

  for (Int_t i{nEvents}; i != 0; --i) {
    std::array<Particle, N> EventPart{};
    j = nGen;

    // Funzione lambda per generare casualmente impulso in direzioni casuali
    auto generateImpulse = [&]() -> PhysVector {
      Double_t theta = gRandom->TRandom::Uniform(0, TMath::Pi());
      Double_t phi = gRandom->TRandom::Uniform(0, 2 * TMath::Pi());
      Double_t Ptot = gRandom->TRandom::Exp(1.);
      hAngles->Fill(theta, phi);
      hImpulse->Fill(Ptot);

      return Ptot * PhysVector{cos(phi) * sin(theta), sin(phi) * sin(theta),
                               cos(theta)};
    };

    // Funzione lambda per determinare l'indice della particella in base a x
    auto generateParticleName = [&](Double_t x) -> std::string {
      if (x < 0.4)
        return "pi+";
      if (x < 0.8)
        return "pi-";
      if (x < 0.85)
        return "K+";
      if (x < 0.9)
        return "K-";
      if (x < 0.945)
        return "P+";
      if (x < 0.99)
        return "P-";
      return "K*";
    };

    // Iterazione sugli eventi, attraverso l'algoritmo (come un for) for_each_n
    std::for_each_n(EventPart.begin(), nGen, [&](Particle &p) {
      // p assume in ogni iterazione è una particella "vuota" dell'array
      p.SetImpulse(generateImpulse());

      Double_t x = gRandom->Rndm();
      std::string name = generateParticleName(x);
      p.SetIndex(name);

      // se la particella generata è una K* (vuol dire che x>0.99, perchè è lo
      // stesso x che usiamo nella generazione) la facciamo decadere
      if (name == "K*") {
        if (x < 0.995) {
          EventPart[j].SetIndex("pi+");
          EventPart[j + 1].SetIndex("K-");
        } else {
          EventPart[j].SetIndex("K+");
          EventPart[j + 1].SetIndex("pi-");
        }
        p.Decay2body(EventPart[j], EventPart[j + 1]);
        hInvariantMassDecad->Fill(EventPart[j].InvMass(EventPart[j + 1]));

        j += 2; // Avanzare il contatore per gli eventi successivi
      }

      // Fill di 3 istogrammi
      hTypes->Fill(p.GetIndex());
      Double_t It{std::pow(p.GetImpulse().x, 2) +
                  std::pow(p.GetImpulse().y, 2)};
      hTransversImpulse->Fill(It);
      hEnergy->Fill(p.GetEnergy());
    });

    // Calcolo e Fill degli istogrammi di massa invariante
    Double_t invMass;
    for (Int_t s{0}; s != j; ++s) {
      // Primo ciclo che itera su tutte le particelle
      for (Int_t k{s + 1}; k != j; ++k) {
        // Secondo ciclo che parte dalla particella a cui è arrivato il primo
        // e arriva fino alla fine
        invMass = EventPart[s].InvMass(EventPart[k]);
        hInvariantMass->Fill(invMass);

        // Fill degli istogrammi
        if (EventPart[s].GetCharge() * EventPart[k].GetCharge() == -1) {
          hInvariantMassDiscCharge->Fill(invMass);
        } else if (EventPart[s].GetCharge() * EventPart[k].GetCharge() == 1) {
          hInvariantMassConcCharge->Fill(invMass);
        }
        if ((EventPart[s].GetParticleName() == "K+" &&
             EventPart[k].GetParticleName() == "pi-") ||
            (EventPart[s].GetParticleName() == "K-" &&
             EventPart[k].GetParticleName() == "pi+")) {
          hInvariantMassKPDisc->Fill(invMass);
        }
        if ((EventPart[s].GetParticleName() == "K+" &&
             EventPart[k].GetParticleName() == "pi+") ||
            (EventPart[s].GetParticleName() == "K-" &&
             EventPart[k].GetParticleName() == "pi-")) {
          hInvariantMassKPConc->Fill(invMass);
        }
      }
    }
  }

  // Creazione dei canvas e disegno dei grafici
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
  TCanvas *c7 =
      new TCanvas("c7", "Invariant Mass All Discord", 200, 10, 600, 400);
  hInvariantMassDiscCharge->Draw();
  TCanvas *c8 =
      new TCanvas("c8", "Invariant Mass Alll Concord", 200, 10, 600, 400);
  hInvariantMassConcCharge->Draw();
  TCanvas *c9 = new TCanvas(
      "c9", "Invariant Mass pione+/Kaone- e pione-/Kaone+", 200, 10, 600, 400);
  hInvariantMassKPDisc->Draw();
  TCanvas *c10 = new TCanvas(
      "c10", "Invariant Mass pione+/Kaone+ e pione-/Kaone-", 200, 10, 600, 400);
  hInvariantMassKPConc->Draw();
  TCanvas *c11 = new TCanvas("c11", "Invariant Mass Decad", 200, 10, 600, 400);
  hInvariantMassDecad->Draw();

  // Salvataggio dei grafici sul file root
  TFile *outputFile = new TFile("output/histograms.root", "RECREATE");
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
