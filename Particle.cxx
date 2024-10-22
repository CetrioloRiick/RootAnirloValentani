#include "Particle.h"
#include "ResonanceType.h"
#include "ParticleType.h"
#include <algorithm>
#include <iostream>

int Particle::numParticleTypes_ = 0;
std::vector<ParticleType*> Particle::particleTypes_;

Particle::Particle(const std::string &name, PhysVector impulse)
    : index_(FindParticle(name)), impulse_(impulse) {}

int Particle::FindParticle(const std::string &name) {
  auto firstType = particleTypes_.begin();
  auto endType = particleTypes_.end();

  auto it = std::find_if(firstType, endType, [&](const ParticleType* pt) {
    return name == pt->GetName();
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
  } else if (FindParticle(name) == -1) {
    if (width == 0.) {
      particleTypes_.push_back(new ParticleType(name, mass, charge));
    } else {
      particleTypes_.push_back(new ResonanceType(name, mass, charge, width));
    }
    numParticleTypes_++;
  } else {
    std::cout << "Particle" << name << "already present" << std::endl;
  }
}
std::vector<ParticleType*> Particle::GetParticleTypes() {
  return particleTypes_;
}

/*
void Particle::SetIndex(int index) { index_ = index; }

void Particle::SetIndex(const std::string &name) {
  index_ = FindParticle(name);
}*/

std::ostream &operator<<(std::ostream &os, const PhysVector &vec) {
  os << "PhysVector(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}
