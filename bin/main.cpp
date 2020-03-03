#include <iostream>

#include "Universe.h"

int  main(int argc, char *argv[]){

  Universe myUniverse;

  Object aObj;
  aObj.setMass(1.0);
  aObj.setRadius(0.01);
  aObj.setPosition(0.0, 0.0, 0.0);
  aObj.setSpeed(1.0, 0.0, 0.0);

  myUniverse.addObject(aObj);
  myUniverse.setTimeStep(0.1);

  std::cout<<"\t      Position: \t \t Speed:"<<std::endl;
  for(unsigned int iStep=0;iStep<50;++iStep){
    std::cout<<"Time step: "<<iStep<<" ";
    myUniverse.advanceTime();
    myUniverse.printState();
  }

  return 0;
  
}
