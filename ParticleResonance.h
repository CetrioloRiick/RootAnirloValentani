#ifndef PARTICLERESONANCE_H
#define PARTICLERESONANCE_H
#include "ParticleType.h"

class ParticleResonance : public ParticleType {
public:
  ParticleResonance(const std::string &name, const double mass,
                    const int charge, const double width);
  double GetParticleWidth() const;
  void PrintData() const;

private:
  double width_;
};

#endif