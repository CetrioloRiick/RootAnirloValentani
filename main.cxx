#include "Particle.h"
#include <iostream>
#include "TRandom.h"
#include "TMath.h"

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

int main()
{
  Particle::AddParticleType("pi+", 0.13957, 1);
  Particle::AddParticleType("pi-", 0.13957, -1);
  Particle::AddParticleType("P+", 0.93827, 1);
  Particle::AddParticleType("P-", 0.93827, -1);
  Particle::AddParticleType("K+", 0.49367, 1);
  Particle::AddParticleType("K-", 0.49367, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.050);
  Particle::PrintParticleTypes();

  const int nGen{10};
  const int N{nGen + 6};

  std::array<Particle, N> EventParticle{};
  double theta = 0., phi = 0., Ptot;
  int j{nGen};

  for (int i = 0; i < nGen; i++)
  {
    theta = gRandom->TRandom::Uniform() * TMath::Pi();
    phi = gRandom->TRandom::Uniform() * 2 * TMath::Pi();
    Ptot = gRandom->TRandom::Exp(1.);

    EventParticle[i].SetImpulse({Ptot * cos(phi) * sin(theta), Ptot * sin(phi) * sin(theta), Ptot * cos(theta)});
    double x = gRandom->Rndm();
    if (x < 0.4)
      EventParticle[i].SetIndex("pi+");
    else if (x < 0.8)
      EventParticle[i].SetIndex("pi-");
    else if (x < 0.85)
      EventParticle[i].SetIndex("K+");
    else if (x < 0.9)
      EventParticle[i].SetIndex("K-");
    else if (x < 0.945)
      EventParticle[i].SetIndex("P+");
    else if (x < 0.99)
      EventParticle[i].SetIndex("P-");
    else
    {
      EventParticle[i].SetIndex("K*");
      EventParticle[i].Decay2body(EventParticle[j], EventParticle[j + 1]);
      if (x < 0.995)
      {
        EventParticle[j].SetIndex("pi+");
        EventParticle[j + 1].SetIndex("K-");
      }
      else
      {
        EventParticle[j].SetIndex("K+");
        EventParticle[j + 1].SetIndex("pi-");
      }
      j += 2;
    }
  }

  std::for_each(EventParticle.begin(), EventParticle.end(), [](const Particle &p)
                { p.PrintData(); });
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