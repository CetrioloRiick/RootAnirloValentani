#include "Particle.h"
#include "TMath.h"
#include "TRandom.h"
#include <algorithm>
#include <vector>

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

int main() {
  Particle::AddParticleType("pi+", 0.13957, 1);
  Particle::AddParticleType("pi-", 0.13957, -1);
  Particle::AddParticleType("P+", 0.93827, 1);
  Particle::AddParticleType("P-", 0.93827, -1);
  Particle::AddParticleType("K+", 0.49367, 1);
  Particle::AddParticleType("K-", 0.49367, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.050);
  Particle::SetTypesProbability({400, 400, 50, 50,45, 45, 10});
  Particle::PrintParticleTypes();

  Particle particle2("K*", {1., 0., 3.});

  // particle2.SetImpulse({1, 1, 1});
  const int nGen{100};
  const int N{nGen + 20};

  std::array<Particle, N> EventParticle{};



  // double theta = 0., phi = 0., Ptot;
 /* int j{nGen};

  // Funzione per generare casualmente impulso in direzioni casuali
  auto generateImpulse = [&]() -> PhysVector {
    double theta = gRandom->TRandom::Uniform(0, TMath::Pi());
    double phi = gRandom->TRandom::Uniform(0, 2 * TMath::Pi());
    double Ptot = gRandom->TRandom::Exp(1.);

    return Ptot *
           PhysVector{cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta)};
  };

  // Funzione per determinare l'indice della particella in base a x
  auto generateParticleName = [&](double x) -> std::string {
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

  // Iterazione sugli eventi
  std::for_each_n(EventParticle.begin(), nGen, [&](Particle &p) {
    p.SetImpulse(generateImpulse());

    double x = gRandom->Rndm();
    std::string name = generateParticleName(x);
    p.SetIndex(name);

    if (name == "K*") {
      if (x < 0.995) {
        EventParticle[j].SetIndex("pi+");
        EventParticle[j + 1].SetIndex("K-");
      } else {
        EventParticle[j].SetIndex("K+");
        EventParticle[j + 1].SetIndex("pi-");
      }
      p.Decay2body(EventParticle[j], EventParticle[j + 1]);
      j += 2; // Avanzare il contatore per gli eventi successivi
    }
  });*/

  /*

    std::for_each_n(EventParticle.begin(), nGen,
                    [&](Particle &p) { // Sarebbe meglio mettere generate
                      theta = gRandom->TRandom::Uniform(0, TMath::Pi());
                      phi = gRandom->TRandom::Uniform(0, 2 * TMath::Pi());
                      Ptot = gRandom->TRandom::Exp(1.);

                      p.SetImpulse(Ptot * PhysVector{cos(phi) * sin(theta),
                                                     sin(phi) * sin(theta),
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


  std::for_each_n(EventParticle.begin(), N,
                  [](const Particle &p) { p.PrintData(); });
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
}