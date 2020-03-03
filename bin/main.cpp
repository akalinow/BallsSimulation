#include <iostream>
#include <iomanip>
#include <map>

#include "SimulationSetup.h"
#include "Universe.h"
#include "Plotter.h"

int  main(int argc, char *argv[]){

  unsigned int nSteps = 100;
  unsigned int nBalls = 2;
  double dt = 0.1;
  std::map<string, string> parsedArgs = parseCmdLineArguments(argc, argv);
  if(parsedArgs.find("-nSteps")!=parsedArgs.end()) nSteps = atoi(parsedArgs.find("-nSteps")->second.c_str());
  if(parsedArgs.find("-nBalls")!=parsedArgs.end()) nBalls = atoi(parsedArgs.find("-nBalls")->second.c_str());
  if(parsedArgs.find("-dt")!=parsedArgs.end()) dt = stof(parsedArgs.find("-dt")->second.c_str());

  Universe myUniverse;
  myUniverse.setTimeStep(dt);
  for(unsigned int iBall=0;iBall<nBalls;++iBall){
    myUniverse.addObject(drawBall());
  }  


  Plotter myPlotter;
  std::cout<<"Time step \t Position:\tSpeed:"<<std::endl;
  for(unsigned int iStep=0;iStep<nSteps;++iStep){
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
