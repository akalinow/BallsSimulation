#ifndef PLOTTER__H
#define PLOTTER__H

#include "Universe.h"

class Plotter{

 public:

  Plotter() = default;
  ~Plotter() {};

  void plotBalls2D(const Universe::objectContainer & aContainer, unsigned int timeStep) const;

  void accumulate(const Universe::objectContainer & objects, unsigned int timeStep);

  void makeAnimation() const;

  void plotAccumulated() const;

 private:

  double getTemperature(double energy) const;

  std::vector<double> meanEnergy, meanVelocity, meanVelocity2;
  std::vector<double> meanMomentum;
  const double boltzmann_k = 1.0;
  
};


#endif
