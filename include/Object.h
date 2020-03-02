#include <vector>

class Object{

 public:

  typedef std::vector<double> Vector3D;

  Object() = default;
  ~Object(){};


  void setPosition(double x, double y, double z);
    
  void setMomentum(double px, double py, double pz);

  const Vector3D & getPosition() const { return myPosition; }
  
  const Vector3D & getMomentum() const { return myMomentum; }

  double getMass() const { return myMass; }

  double getRadius() const { return myRadius; }
  
 private:

  Vector3D myPosition;
  Vector3D myMomentum;
  double myMass;
  double myRadius;
  
};
