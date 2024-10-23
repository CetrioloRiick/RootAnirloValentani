#include "ParticleType.h"
#include <iostream>
#include <ostream>

ParticleType::ParticleType(const std::string &name, const double mass,
                           const int charge)
    : name_(name), mass_(mass), charge_(charge) {};

std::string ParticleType::GetName() const { return name_; };
double ParticleType::GetMass() const { return mass_; };
int ParticleType::GetCharge() const { return charge_; };
double ParticleType::GetWidth() const {return -1.0;};

void ParticleType::PrintData() const {
  std::cout << "name: " << name_ << ", mass: " << mass_
            << ", charge: " << charge_<< std::endl;
}

/*
std::ostream &operator<<(std::ostream &os, const ParticleType &pt) {
  os << "ParticleType(name: " << pt.GetName() << ", mass: " << pt.GetMass()
     << ", charge: " << pt.GetCharge() << ')' << std::endl;
  return os;
}*/