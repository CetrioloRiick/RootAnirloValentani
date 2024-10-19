#include "ParticleResonance.h"
#include <iostream>

ParticleResonance::ParticleResonance(const std::string &name, const double mass,
                                     const int charge, const double width)
    : ParticleType(name, mass, charge), width_(width) {}

double ParticleResonance::GetParticleWidth() const { return width_; };

void ParticleResonance::PrintData() const {
  ParticleType::PrintData();
  std::cout << "Width:" << width_ << std::endl;
};
