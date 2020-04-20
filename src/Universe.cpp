#include <iostream>
#include <cmath>
#include <random>

#include "Universe.h"

/////////////////////////////
/////////////////////////////
bool Universe::addObject(const Object & aObj){

  myObjects.push_back(aObj);

  return true;
  
}
/////////////////////////////
/////////////////////////////
void Universe::advanceTime(){

  moveObjects();
  detectCollisions();
  resetCollideFlag();
}
/////////////////////////////
/////////////////////////////
Vector3D Universe::getForce(double mass, Vector3D position) const{

  return Vector3D{0,0,0};
}
/////////////////////////////
/////////////////////////////
void Universe::moveObjects(){

  Vector3D newPosition, newSpeed;
  double timeStep = getTimeStep();
  double timeStepSqared = timeStep*timeStep;
  
  for(auto & it: myObjects){
    double mass = it.getMass();
    const Vector3D & position = it.getPosition();
    const Vector3D & speed = it.getSpeed();
    const Vector3D & accelearation = getForce(mass, position);
    newPosition = position + speed*timeStep + accelearation*timeStepSqared*0.5;
    newSpeed = speed + accelearation*timeStep;
    it.setPosition(newPosition);
    it.setSpeed(newSpeed);
  }
}
/////////////////////////////
/////////////////////////////
void Universe::detectCollisionsWithWalls(){

   for(auto & it: myObjects){
     const Vector3D & position = it.getPosition();
     double radius = it.getRadius();
     for(int iDirection=-1;iDirection<=1;iDirection+=2){
       for(unsigned int iCoordinate=0;iCoordinate<3;++iCoordinate){
	 bool hitTheWall = (position.at(iCoordinate)*iDirection + radius>1);
	 if(hitTheWall){
	   Vector3D position = it.getPosition();
	   position.at(iCoordinate)=iDirection*(1-radius);
	   it.setPosition(position);
	   bounceFromWall(it, iCoordinate);
	 }
       }
     }
   }
}
/////////////////////////////
/////////////////////////////
void Universe::detectCollisionsWithBalls(){

  for(auto ball1 = myObjects.begin(); ball1!=myObjects.end();++ball1){
    const Vector3D & position1 = ball1->getPosition();
    double radius1 = ball1->getRadius();
    for(auto ball2 = ball1+1; ball2!=myObjects.end();++ball2){
      if(ball2->getHasCollided()) continue;
      const Vector3D & position2 = ball2->getPosition();
      double radius2 = ball2->getRadius();
      double radiusSum2 = std::pow(radius1 + radius2,2);
      double deltaR2 = (position1 - position2).mag2();
      if(deltaR2<radiusSum2) bounceFromBall(*ball1, *ball2);      
    }
  }
}
/////////////////////////////
/////////////////////////////
Object Universe::drawBallInWall(double temp, unsigned int iCoordinate){

  std::uniform_real_distribution<double> flatDistribution(0.0,1.0);

  double m = 1.0;
  double A = 1.0;
  double omega = 1.0;
  double E = 0.0;
  if(temp>0.0){
    std::exponential_distribution<double> expoDistribution(1.0/temp);
    E = expoDistribution(generator);
  }
  A = sqrt(2.0*E/m)/omega;
  double time = flatDistribution(generator)*2.0*M_PI;
  double v = A*omega*cos(omega*time);
  double vx = 0.0, vy = 0.0, vz = 0.0;
  if(iCoordinate==0) vx = v;
  else if (iCoordinate==1) vy = v;
  else if (iCoordinate==2) vz = v;

  Object aObj;
  aObj.setMass(m);
  aObj.setRadius(0.025);
  aObj.setPosition(0,0,0);
  aObj.setSpeed(vx, vy, vz);
  return aObj;
}
/////////////////////////////
/////////////////////////////
void Universe::bounceFromWall(Object & aObj, unsigned int iCoordinate){

  /*
  double temp = 10.0;
  temp = 0.0;
  Object aObjInWall = drawBallInWall(temp, iCoordinate);
  bounceFromBall(aObj, aObjInWall);
  */
  
  Vector3D speed = aObj.getSpeed();
  speed.at(iCoordinate)*=-1;
  aObj.setSpeed(speed);
  
}
/////////////////////////////
/////////////////////////////
void Universe::bounceFromBall(Object & aObj1, Object & aObj2){

  double reducedMass = aObj1.getMass()*aObj2.getMass()/(aObj1.getMass() + aObj2.getMass());
  Vector3D impactVector = aObj1.getPosition() -aObj2.getPosition();
  double impactParameter2 = impactVector.mag2();
  Vector3D q = impactVector*((aObj1.getSpeed() - aObj2.getSpeed())*impactVector);
  q = q/impactParameter2;
  q = q*(-2.0)*reducedMass;

  aObj1.setHasCollided(true);
  aObj1.setSpeed(aObj1.getSpeed() + q/aObj1.getMass());

  aObj2.setHasCollided(true);
  aObj2.setSpeed(aObj2.getSpeed() - q/aObj2.getMass());
}
/////////////////////////////
/////////////////////////////
void Universe::detectCollisions(){

  detectCollisionsWithBalls();
  detectCollisionsWithWalls();

}
/////////////////////////////
/////////////////////////////
void Universe::resetCollideFlag(){

   for(auto & it: myObjects){
     it.setHasCollided(false);
   }  
}
/////////////////////////////
/////////////////////////////
std::ostream& operator<<(std::ostream& os, const Universe& aUniverse){

  for(auto it: aUniverse.getObjects()){
     os<<it<<std::endl;
   }
  return os;
}
/////////////////////////////
/////////////////////////////
