#include <iostream>
#include "ParticleType.h"
ParticleType::ParticleType(const char* fName, const double fMass, const int fCharge) : fName_(fName), fMass_(fMass), fCharge_(fCharge) {};
const char* ParticleType::GetParticleName() const { return fName_; };
double ParticleType::GetParticleMass() const { return fMass_; };
int ParticleType::GetParticleCharge() const { return fCharge_; };
void ParticleType::PrintData() const
{
    std::cout << "Name:" << fName_ << std::endl;
    std::cout << "Mass:" << fMass_ << std::endl;
    std::cout << "Charge:" << fCharge_ << std::endl;
};