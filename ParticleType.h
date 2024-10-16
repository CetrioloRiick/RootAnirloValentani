#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H
class ParticleType
{
public:
    ParticleType(const char* fName, const double fMass, const int fCharge);
    const char* GetParticleName() const; 
    double GetParticleMass() const;
    int GetParticleCharge() const;
    virtual void PrintData() const;

private:
    const char* fName_;
    const double fMass_;
    const int fCharge_;
};

#endif