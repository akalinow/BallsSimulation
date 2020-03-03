#include <iostream>
#include <iomanip>

#include "Universe.h"
#include "Plotter.h"

int  main(int argc, char *argv[]){

  Universe myUniverse;
  Plotter myPlotter;
  
  Object aObj;
  aObj.setMass(1.0);
  aObj.setRadius(0.01);
  aObj.setPosition(0.0, 0.0, 0.0);
  aObj.setSpeed(1.0, 0.5, 0.0);
  myUniverse.addObject(aObj);

  aObj.setPosition(0.0, 0.0, 0.0);
  aObj.setSpeed(-0.2, 0.6, 0.0);
  myUniverse.addObject(aObj);
  
  myUniverse.setTimeStep(0.1);

  std::cout<<"Time step \t Position:\tSpeed:"<<std::endl;
  for(unsigned int iStep=0;iStep<200;++iStep){
    myUniverse.advanceTime();
    myPlotter.plotBalls2D(myUniverse.getObjects(), iStep);
    if(iStep%10==0){
      std::cout<<iStep<<std::endl;
    myUniverse.printState();
    }
  }

  myPlotter.makeAnimation();
  return 0;  
}
