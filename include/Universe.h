#ifndef UNIVERSE__H
#define UNIVERSE__H

#include <map>

#include "Object.h"


class Universe{

  typedef std::vector<Object> objectContainer;

 public: 
  Universe() = default;

  bool addObject(const Object & aObj);

  void setTimeStep(double dt) {myTimeStep = dt;}

  void advanceTime();

  double getTimeStep() const { return myTimeStep;}

  long int getCurrentTimeStep() const {return myClock;}

  const objectContainer & getObjects() const {return myObjects;}

  void printState() const;

 private:

  Vector3D getForce(double mass, Vector3D position) const;
  void moveObjects();
  void detectCollisions();
  void detectCollisionsWithWalls();
  void bounceFromWall(Object & aObj, unsigned int iCoordinate);

  double myTimeStep = 0;
  long int myClock = 0;
  objectContainer myObjects;
  
};
#endif
