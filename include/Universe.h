#include <map>

#include "Object.h"


class Universe{

  typedef std::vector<Object> objectContainer;

 public: 
  Universe() = default;

  bool addObject(const Object & aObj);

  void advanceTime();

  const objectContainer & getObjects() conts { return myObjects;}

 private:

  void moveObjects();
  void detecCollisions();
  
  objectContainer myObjects;
  
};
