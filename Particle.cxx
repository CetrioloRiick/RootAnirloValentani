#include <iostream>
#include "Particle.h"

physVector::physVector(double x, double y, double z) : Px(x), Py(y), Pz(z) {};

int Particle::fNParticleType_ = 0;
ParticleType *Particle::fParticleType_[Particle::fMaxNumParticleType_];

int Particle::FindParticle(const char *Name)
{
    for (int i = 0; i < fNParticleType_; i++)
    {
        const char *typeName = fParticleType_[i]->GetParticleName();
        if (typeName == Name)
        {
            return i;
        }
        else
        {
            std::cout << "No correspondence with existing type" << std::endl;
        }
    }
    return -1;
}

Particle::Particle(const char *Name, physVector Impulse) : Impulse_(Impulse)
{
    fIndex_ = FindParticle(Name);
}

int Particle::GetIndex() { return fIndex_; }
const physVector Particle::GetImpulse() { return Impulse_; }
void Particle::AddParticleType(const char *fName, const double fMass, const int fCharge, const double fWidth)
{
    if (fNParticleType_ == fMaxNumParticleType_)
    {
        std::cout << "Max number of type reached" << std::endl;
    }
    else
    {
        for (int i = 0; i < fNParticleType_; i++)
        {
            if (fName == fParticleType_[i]->GetParticleName())
            {
                std::cout << "Particle" << fName << "already present" << std::endl;
            }
            else
            {
                fNParticleType_++;
                if (fWidth == 0)
                {
                    fParticleType_[fNParticleType_] = new ParticleType(fName, fMass, fCharge);
                }
                else
                {
                    fParticleType_[fNParticleType_] = new ParticleResonance(fName, fMass, fCharge, fWidth);
                }
            }
        }
    }
}

void Particle::SetIndex(int index) { fIndex_ = index; }

void Particle::SetIndex(const char *Name)
{
    fIndex_ = FindParticle(Name);
}
