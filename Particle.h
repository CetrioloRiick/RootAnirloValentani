#ifndef PARTICLE_H
#define PARTICLE_H
#include "ParticleType.h"
#include "ParticleResonance.h"

struct physVector
{
    double Px,Py,Pz;
    physVector(double x=0.,double y=0.,double z=0.);
};

class Particle
{
public:
    Particle(const char* Name, const physVector Impulse);
    int GetIndex();
    const physVector GetImpulse();
    static void AddParticleType(const char* fName,const double fMass,const int fCharge,const double fWidth=0.);
    void SetIndex(int Index);
    void SetIndex(const char* Name);
private:
    const physVector Impulse_;
    int fIndex_;
    static const int fMaxNumParticleType_ = 10;
    static int fNParticleType_;
    static ParticleType *fParticleType_[fMaxNumParticleType_];
    int FindParticle(const char* Name);
};

#endif