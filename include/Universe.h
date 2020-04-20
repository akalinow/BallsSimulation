#ifndef UNIVERSE__H
#define UNIVERSE__H

#include <ostream>
#include <map>
#include <random>

#include "Object.h"


class Universe{

 public:

  typedef std::vector<Object> objectContainer;
  
  Universe() = default;

  bool addObject(const Object & aObj);

  void setTimeStep(double dt) {myTimeStep = dt;}

  void advanceTime();

  double getTimeStep() const { return myTimeStep;}

  long int getCurrentTimeStep() const {return myClock;}

  const objectContainer & getObjects() const {return myObjects;}

 private:

  Vector3D getForce(double mass, Vector3D position) const;
  void moveObjects();
  void detectCollisions();
  void detectCollisionsWithWalls();
  void detectCollisionsWithBalls();
  void resetCollideFlag();
  Object drawBallInWall(double t, unsigned int iCoordinate);
  void bounceFromWall(Object & aObj, unsigned int iCoordinate);
  void bounceFromBall(Object & aObj1, Object & aObj2);

  double myTimeStep = 0;
  long int myClock = 0;
  objectContainer myObjects;

  std::default_random_engine generator;
  
};

std::ostream& operator<<(std::ostream& os, const Universe& aUniverse);
#endif
