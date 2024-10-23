#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H
#include "ParticleType.h"

class ResonanceType : public ParticleType {
public:
  ResonanceType(const std::string &name, const double mass,
                    const int charge, const double width);
  double GetWidth() const;
  void PrintData() const override;

private:
  const double width_;
};

//std::ostream &operator<<(std::ostream &os, const ResonanceType &rt);


#endif