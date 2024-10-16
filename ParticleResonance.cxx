#include <iostream>
#include "ParticleResonance.h"

ParticleResonance::ParticleResonance(const char* fName, const double fMass, const int fCharge,const double fWidth) : ParticleType(fName,fMass,fCharge), fWidth_(fWidth) {}
    double ParticleResonance::GetParticleWidth() const {return fWidth_;} ;
    void ParticleResonance::PrintData() const {
        ParticleType::PrintData();
        std::cout << "Width:" << fWidth_ << std::endl;
    };
