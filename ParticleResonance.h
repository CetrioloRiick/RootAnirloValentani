#ifndef PARTICLERESONANCE_H
#define PARTICLERESONANCE_H
#include "ParticleType.h"

class ParticleResonance : public ParticleType {
    public:
    ParticleResonance(const char* fName, const double fMass, const int fCharge,const double fWidth);
    double GetParticleWidth() const;
    void PrintData() const;
    private:
    double fWidth_;
};


#endif