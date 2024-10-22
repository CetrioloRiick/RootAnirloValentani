#include "ParticleType.h"
#include <iostream>

ParticleType::ParticleType(const std::string &name, const double mass,
                           const int charge)
    : name_(name), mass_(mass), charge_(charge) {};

const std::string ParticleType::GetName() const { return name_; };
double ParticleType::GetMass() const { return mass_; };
int ParticleType::GetCharge() const { return charge_; };

void ParticleType::PrintData() const { std::cout << *this; }

std::ostream &operator<<(std::ostream &os, const ParticleType &pt) {
  os << "ParticleType(name: " << pt.GetName() << ", mass: " << pt.GetMass()
     << ", charge: " << pt.GetCharge() << ')' << std::endl;
  return os;
}