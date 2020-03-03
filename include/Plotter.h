#ifndef PLOTTER__H
#define PLOTTER__H

#include "Universe.h"

class Plotter{

 public:

  Plotter() = default;
  ~Plotter() {};

  void plotBalls2D(const Universe::objectContainer & aContainer, unsigned int timeStep) const;

  void makeAnimation() const;

 private:
  
};


#endif
