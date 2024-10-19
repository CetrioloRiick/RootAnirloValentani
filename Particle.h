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
  void SetIndex(int index);
  void SetIndex(const std::string &name);

private:
  int FindParticle(const std::string &name);

  const PhysVector impulse_;
  int index_;
  static const int maxNumParticleTypes_ = 10;
  static int numParticleTypes_;
  static std::vector<ParticleType> particleTypes_;
};

#endif