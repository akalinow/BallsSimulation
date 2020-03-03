#ifndef OBJECT__H
#define OBJECT__H

#include <ostream>
#include <vector>

using namespace std;
  
class Vector3D : public std::vector<double>{

  using vector::vector;

 public:
  
  Vector3D(){ this->resize(3);};

  double x() const { return this->at(0);}
  double y() const { return this->at(1);}
  double z() const { return this->at(2);}
  
  Vector3D operator+(const Vector3D& v) const {
    return Vector3D{this->at(0)+v.at(0),
		    this->at(1)+v.at(1),
		    this->at(2)+v.at(2)};   
  }

  Vector3D operator-(const Vector3D& v) const {
    return Vector3D{this->at(0)-v.at(0),
		    this->at(1)-v.at(1),
		    this->at(2)-v.at(2)};       
  }

  Vector3D operator*(const double& a) const {
    return Vector3D{this->at(0)*a,
		    this->at(1)*a,
		    this->at(2)*a};    
  }

 
  
};

class Object{

 public:

  Object() = default;
  ~Object(){};

  void setRadius(double r);

  void setMass(double m);

  void setPosition(double x, double y, double z);

  void setPosition(const Vector3D & p) {myPosition = p;};
    
  void setSpeed(double px, double py, double pz);

  void setSpeed(const Vector3D & v) {mySpeed = v;};

  const Vector3D & getPosition() const { return myPosition; }
  
  const Vector3D & getSpeed() const { return mySpeed; }

  double getMass() const { return myMass; }

  double getRadius() const { return myRadius; }

 private:

  Vector3D myPosition;
  Vector3D mySpeed;
  double myMass;
  double myRadius;
  
};

ostream& operator<<(ostream& os, const Vector3D& aVec);
ostream& operator<<(ostream& os, const Object& aObj);

#endif
