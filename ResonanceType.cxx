#include "ResonanceType.h"
#include "ParticleType.h"
#include <iostream>

ResonanceType::ResonanceType(const std::string &name, const double mass,
                             const int charge, const double width)
    : ParticleType(name, mass, charge), width_(width) {}

double ResonanceType::GetWidth() const { return width_; };

void ResonanceType::PrintData() const { std::cout << "pippo"; }

std::ostream &operator<<(std::ostream &os, const ResonanceType &rt) {
  os << "ResonanceType(name: " << rt.GetName() << ", mass: " << rt.GetMass()
     << ", charge: " << rt.GetCharge() << ", width: " << rt.GetWidth() << ')'
     << std::endl;
  return os;
}