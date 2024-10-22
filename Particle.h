#ifndef PARTICLE_H
#define PARTICLE_H
#include "ParticleType.h"
#include "ResonanceType.h"
#include <vector>

struct PhysVector {
  double x, y, z;

  PhysVector operator+(const PhysVector &v) const;
  double operator*(const PhysVector &v) const;
};

class Particle {
public:
  Particle(const std::string &name, const PhysVector impulse);

  int GetIndex() const;
  PhysVector GetImpulse() const;
  static std::vector<ParticleType *> GetParticleTypes();
  double GetMass() const;
  double GetEnergy() const;

  void SetIndex(int index);
  void SetIndex(const std::string &name);
  void SetImpulse(PhysVector &pv);

  static void PrintParticleTypes();
  void PrintData();

  static void AddParticleType(const std::string &name, const double mass,
                              const int charge, const double width = 0.);

  double InvMass(Particle &p) const;

private:
  static int FindParticle(const std::string &name);

  int index_;
  PhysVector impulse_;
  static const int maxNumParticleTypes_ = 10;
  static int numParticleTypes_;
  static std::vector<ParticleType *> particleTypes_;
};

std::ostream &operator<<(std::ostream &os, const PhysVector &pv);
std::ostream &operator<<(std::ostream &os,
                         const std::vector<ParticleType> &vec);
#endif