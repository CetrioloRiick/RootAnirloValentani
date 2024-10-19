#include "Particle.h"
#include "ParticleType.h"
#include <algorithm>
#include <iostream>

int Particle::numParticleTypes_ = 0;

std::vector<ParticleType> Particle::particleTypes_;

Particle::Particle(const std::string &name, PhysVector impulse)
    : impulse_(impulse) {
  index_ = FindParticle(name);
}

int Particle::FindParticle(const std::string &name) {
  auto firstType = particleTypes_.begin();
  auto endType = particleTypes_.end();
  auto it = std::find_if(firstType, endType, [&](const ParticleType &pt) {
    return name == pt.GetParticleName();
  });

  if (it != endType) {
    return std::distance(firstType, it);
  } else {
    std::cout << "No correspondence with existing type" << std::endl;
    return -1;
  }
}

int Particle::GetIndex() const { return index_; }
const PhysVector Particle::GetImpulse() const { return impulse_; }
void Particle::AddParticleType(const std::string &name, const double mass,
                               const int charge, const double width) {
  if (numParticleTypes_ == maxNumParticleTypes_) {
    std::cout << "Max number of type reached" << std::endl;
  } else {
    for (int i = 0; i < numParticleTypes_; i++) {
      if (name == particleTypes_[i].GetParticleName()) {
        std::cout << "Particle" << name << "already present" << std::endl;
      } else {
        numParticleTypes_++;
        if (width == 0) {
          // particleTypes_[numParticleTypes_] = ParticleType(name, mass,
          // charge);
        } else {
          // particleTypes_[numParticleTypes_] =              new
          // ParticleResonance(name, mass, charge, width);
        }
      }
    }
  }
}

void Particle::SetIndex(int index) { index_ = index; }

void Particle::SetIndex(const std::string &name) {
  index_ = FindParticle(name);
}
