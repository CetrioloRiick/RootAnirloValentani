#include "Particle.h"
#include "ParticleType.h"
#include "ResonanceType.h"
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

int main() {
  Particle::AddParticleType("K+", 0.493, 1);
  Particle::AddParticleType("K*", 0.892, 0, 0.05);
  Particle particle1("K+", {2., 4., 1});
  Particle particle2("K*", {1., 0., 3.});

  std::cout << "Indice  particle1: " << particle1.GetIndex() << std::endl;
  std::cout << "Impulso particle1: " << particle1.GetImpulse() << std::endl;
  std::cout << "Indice  particle2: " << particle2.GetIndex() << std::endl;
  std::cout << "Impulso particle2: " << particle2.GetImpulse() << std::endl;
  // Particle::GetParticleTypes()[0]->PrintData();
  // Particle::GetParticleTypes()[1]->PrintData();

  Particle::PrintParticleTypes();
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