#include "Particle.h"
#include "ParticleResonance.h"
#include "ParticleType.h"
#include <iostream>

/* int main()
{
    ParticleType particleType1("protone", 2.5, 4);
    ParticleResonance particleType2("neutrone", 3.43, -1, 0.001);
    particleType1.PrintData();
    particleType2.PrintData();
    ParticleType *test[2];
    test[0]=new ParticleType("pione+",1.7,1);
    test[1]=new ParticleResonance("pione0",1.9,0,0.23);
    for(int i=0;i<2;i++)test[i]->PrintData();
    return 0;
} */

int main() {
  Particle::AddParticleType("K+", 0.493, 1);
  Particle::AddParticleType("K*", 0.892, 0, 0.05);
  Particle particle1("K+", {2., 4., 1});
  Particle particle2("K*", {1., 0., 3.});
  std::cout << "Indice particle1: " << particle1.GetIndex() << std::endl;
  std::cout << "Indice particle2 : " << particle2.GetIndex() << std::endl;
}