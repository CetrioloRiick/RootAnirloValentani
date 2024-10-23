#ifndef PARTICLE_H
#define PARTICLE_H
#include "ParticleType.h"
#include "ResonanceType.h"
#include <vector>

struct PhysVector {
  double x, y, z;

  PhysVector operator+(const PhysVector &pv) const;
  double operator*(const PhysVector &pv) const;
};
PhysVector operator*(double scalar, const PhysVector &pv);

class Particle {
public:
  Particle();
  Particle(const std::string &name, const PhysVector impulse);

  int GetIndex() const;
  PhysVector GetImpulse() const;
  static std::vector<ParticleType *> GetParticleTypes();
  double GetMass() const;
  double GetEnergy() const;

  void SetIndex(int index);
  void SetIndex(const std::string &name);
  void SetImpulse(PhysVector pv);

  static void PrintParticleTypes();
  void PrintData(char lastChar='\n') const;

  static void AddParticleType(const std::string &name, const double mass,
                              const int charge, const double width = 0.);

  double InvMass(Particle &p) const;

  int Decay2body(Particle &dau1,Particle &dau2) const;

private:
  static int FindParticle(const std::string &name);

  int index_;
  PhysVector impulse_;
  static std::vector<ParticleType *> particleTypes_;
  void Boost(double bx, double by, double bz);
};

std::ostream &operator<<(std::ostream &os, const PhysVector &pv);
std::ostream &operator<<(std::ostream &os,
                         const std::vector<ParticleType> &vec);
#endif