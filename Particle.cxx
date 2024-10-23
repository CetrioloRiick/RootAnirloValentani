#include "Particle.h"
#include "ParticleType.h"
#include "ResonanceType.h"
#include <algorithm>
#include <cmath>
#include <iostream>

int Particle::numParticleTypes_ = 0;
std::vector<ParticleType *> Particle::particleTypes_;

PhysVector PhysVector::operator+(const PhysVector &v) const {
  return {x + v.x, y + v.y, z + v.z};
}
double PhysVector::operator*(const PhysVector &v) const {
  return x * v.x + y * v.y + z * v.z;
}

Particle::Particle(const std::string &name, PhysVector impulse)
    : index_(FindParticle(name)), impulse_(impulse) {}

int Particle::FindParticle(const std::string &name) {
  auto firstType = particleTypes_.begin();
  auto endType = particleTypes_.end();

  auto it = std::find_if(firstType, endType, [name](const ParticleType *pt) {
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
PhysVector Particle::GetImpulse() const { return impulse_; }
std::vector<ParticleType *> Particle::GetParticleTypes() {
  return particleTypes_;
}
double Particle::GetMass() const { return particleTypes_[index_]->GetMass(); }
double Particle::GetEnergy() const {
  return std::sqrt(std::pow(GetMass(), 2) + (impulse_ * impulse_));
}

void Particle::SetIndex(int index) {
  if (index >= 0 && index < static_cast<int>(particleTypes_.size())) {
    index_ = index;
  } else {
    std::cout << "Index out of range";
  }
}
void Particle::SetIndex(const std::string &name) {
  int index{FindParticle(name)};
  if (index != -1) {
    index_ = index;
  }
}
void Particle::SetImpulse(PhysVector &pv) { impulse_ = pv; }

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

void Particle::PrintParticleTypes() {
  auto it = particleTypes_.begin();
  std::for_each(it, particleTypes_.end(),
                [](const ParticleType *pt) { pt->PrintData(); });
}

void Particle::PrintData() {
  std::cout << "Index: " << index_
            << ", name: " << particleTypes_[index_]->GetName()
            << ", impulse: " << impulse_;
}

double Particle::InvMass(Particle &p) const {
  PhysVector impulseSum{impulse_ + p.GetImpulse()};
  return std::sqrt(std::pow(GetEnergy() + p.GetEnergy(), 2) -
                   (impulseSum * impulseSum));
}

std::ostream &operator<<(std::ostream &os, const PhysVector &vec) {
  os << "PhysVector(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}
