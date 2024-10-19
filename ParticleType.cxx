#include "ParticleType.h"
#include <iostream>

ParticleType::ParticleType(const std::string &name, const double mass,
                           const int charge)
    : name_(name), mass_(mass), charge_(charge) {};

const std::string ParticleType::GetParticleName() const { return name_; };
double ParticleType::GetParticleMass() const { return mass_; };
int ParticleType::GetParticleCharge() const { return charge_; };

void ParticleType::PrintData() const {
  std::cout << "Name:" << name_ << std::endl;
  std::cout << "Mass:" << mass_ << std::endl;
  std::cout << "Charge:" << charge_ << std::endl;
};