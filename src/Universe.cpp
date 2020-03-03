#include <iostream>

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
  detectCollisionsWithWalls();
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
	 if(hitTheWall) bounceFromWall(it, iCoordinate);
       }
     }
   }
}
/////////////////////////////
/////////////////////////////
void Universe::bounceFromWall(Object & aObj, unsigned int iCoordinate){

  Vector3D speed = aObj.getSpeed();
  speed.at(iCoordinate)*=-1;
  aObj.setSpeed(speed);
}
/////////////////////////////
/////////////////////////////
void Universe::detectCollisions(){

  //detectCollisionsWithBalls();
  detectCollisionsWithWalls();

}
/////////////////////////////
/////////////////////////////
void Universe::printState() const{

   for(auto it: myObjects){
     std::cout<<it<<std::endl;
   }  
}
/////////////////////////////
/////////////////////////////
