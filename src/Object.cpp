#include <iomanip>


#include "Object.h"
///////////////////////////////////////////////
///////////////////////////////////////////////
Object::Object(){

  setMass(1000.0);
  setRadius(0.025);
  setHasCollided(false);    
  setPosition(0.0, 0.0, 0.0);
  setSpeed(0.0, 0.0, 0.0);
  
}
///////////////////////////////////////////////
///////////////////////////////////////////////
void Object::setRadius(double r) { myRadius = r;}
///////////////////////////////////////////////
///////////////////////////////////////////////
void Object::setMass(double m){ myMass = m;}
///////////////////////////////////////////////
///////////////////////////////////////////////
void Object::setPosition(double x, double y, double z){

  myPosition.at(0) = x;
  myPosition.at(1) = y;
  myPosition.at(2) = z;
  
}
///////////////////////////////////////////////
///////////////////////////////////////////////
void Object::setSpeed(double px, double py, double pz){

  mySpeed.at(0) = px;
  mySpeed.at(1) = py;
  mySpeed.at(2) = pz;
  
}
///////////////////////////////////////////////
///////////////////////////////////////////////
ostream& operator<<(ostream& os, const Vector3D& aVec){
  os <<"("<<aVec.x()<<", "<<aVec.y()<<", "<<aVec.z()<<")";
  return os;
}
///////////////////////////////////////////////
///////////////////////////////////////////////
ostream& operator<<(ostream& os, const Object& aObj){
  os <<std::setw(10)<<aObj.getPosition()<<",\t"<<aObj.getSpeed();
  return os;
}
///////////////////////////////////////////////
///////////////////////////////////////////////
