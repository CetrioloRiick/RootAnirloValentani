#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H
#include <string>

class ParticleType {
public:
  ParticleType(const std::string &name, const double mass, const int charge);
  const std::string GetParticleName() const;
  double GetParticleMass() const;
  int GetParticleCharge() const;
  virtual void PrintData() const;

private:
  const std::string name_;
  const double mass_;
  const int charge_;
};

#endif