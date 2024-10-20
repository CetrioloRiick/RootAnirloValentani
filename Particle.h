#ifndef PARTICLE_H
#define PARTICLE_H
#include "ParticleResonance.h"
#include "ParticleType.h"
#include <vector>

struct PhysVector {
  double x, y, z;
};

class Particle {
public:
  Particle(const std::string &name, const PhysVector impulse);
  int GetIndex() const;
  const PhysVector GetImpulse() const;
  static void AddParticleType(const std::string &name, const double mass,
                              const int charge, const double width = 0.);
  //static std::vector<ParticleType> GetParticleTypes();

  void SetIndex(int index);
  void SetIndex(const std::string &name);

private:
  static int FindParticle(const std::string &name);

  PhysVector impulse_;
  const int index_;
  static const int maxNumParticleTypes_ = 10;
  static int numParticleTypes_;
  static std::vector<ParticleType> particleTypes_;
};

std::ostream &operator<<(std::ostream &os, const PhysVector &vec);
#endif