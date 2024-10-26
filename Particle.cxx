#include "Particle.h"
#include "ParticleType.h"
#include "ResonanceType.h"
#include "TMath.h"
#include "TRandom.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib> //for RAND_MAX
#include <iostream>
#include <numeric>

std::vector<ParticleType *> Particle::particleTypes_;
std::vector<int> Particle::typesProbability_;

PhysVector PhysVector::operator+(const PhysVector &pv) const {
  return {x + pv.x, y + pv.y, z + pv.z};
}

double PhysVector::operator*(const PhysVector &pv) const {
  return x * pv.x + y * pv.y + z * pv.z;
}

PhysVector operator*(double scalar, const PhysVector &pv) {
  return {scalar * pv.x, scalar * pv.y, scalar * pv.z};
}
Particle::Particle() {

  auto generateImpulse = [&]() -> PhysVector {
    double theta = gRandom->TRandom::Uniform(0, TMath::Pi());
    double phi = gRandom->TRandom::Uniform(0, 2 * TMath::Pi());
    double Ptot = gRandom->TRandom::Exp(1.);

    return Ptot *
           PhysVector{cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta)};
  };

  auto generateParticleName = [&]() {
    double x = gRandom->TRandom::Uniform(0, 1000); //Da risolvere questa roba dei mille
    int maxNum{static_cast<int>(particleTypes_.size())};
    int sum{0};
    for (int i{0}; i != maxNum; ++i) {
      sum += typesProbability_[i];
      if (x <= sum) {
        SetIndex(i);
        break;
      }
    }
  };

  SetImpulse(generateImpulse());
  generateParticleName();
};

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
void Particle::SetImpulse(PhysVector pv) { impulse_ = pv; }

void Particle::AddParticleType(const std::string &name, const double mass,
                               const int charge, const double width) {
  if (FindParticle(name) == -1) {
    if (width == 0.) {
      particleTypes_.emplace_back(new ParticleType(name, mass, charge));
    } else {
      particleTypes_.emplace_back(new ResonanceType(name, mass, charge, width));
    }
  } else {
    std::cout << "Particle " << name << " already present" << std::endl;
  }
}

void Particle::SetTypesProbability(const std::vector<int> &typesProbability) {
  typesProbability_ = typesProbability;
  assert(typesProbability_.size() == particleTypes_.size());
  assert(std::accumulate(typesProbability_.begin(), typesProbability_.end(),
                         0) == 1000);
}

void Particle::PrintParticleTypes() {
  auto it = particleTypes_.begin();
  std::for_each(it, particleTypes_.end(),
                [](const ParticleType *pt) { pt->PrintData(); });
}

void Particle::PrintData(char lastChar) const {
  std::cout << "Index: " << index_
            << ", name: " << particleTypes_[index_]->GetName()
            << ", impulse: " << impulse_ << lastChar;
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

int Particle::Decay2body(Particle &dau1, Particle &dau2) const {
  if (GetMass() == 0.0) {
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }

  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if (GetIndex() > -1) { // add width effect

    // gaussian random numbers

    float x1, x2, w, y1;

    double invnum = 1. / RAND_MAX;
    do {
      x1 = 2.0 * rand() * invnum - 1.0;
      x2 = 2.0 * rand() * invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    y1 = x1 * w;

    massMot += particleTypes_[GetIndex()]->GetWidth() * y1;
  }

  if (massMot < massDau1 + massDau2) {
    printf("Decayment cannot be preformed because mass is too low in this "
           "channel\n");
    return 2;
  }

  double pout =
      sqrt(
          (massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
          (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
      massMot * 0.5;

  double norm = 2 * M_PI / RAND_MAX;

  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;
  dau1.SetImpulse({pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
                   pout * cos(theta)});
  dau2.SetImpulse({-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi),
                   -pout * cos(theta)});

  double energy = GetEnergy();

  double bx = impulse_.x / energy;
  double by = impulse_.y / energy;
  double bz = impulse_.z / energy;

  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}

void Particle::Boost(double bx, double by, double bz) {

  double energy = GetEnergy();

  // Boost this Lorentz vector
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * impulse_.x + by * impulse_.y + bz * impulse_.z;
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  impulse_.x += gamma2 * bp * bx + gamma * bx * energy;
  impulse_.y += gamma2 * bp * by + gamma * by * energy;
  impulse_.z += gamma2 * bp * bz + gamma * bz * energy;
}
