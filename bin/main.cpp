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
  std::string inputType = "random";
  std::string doFrames = "true";
  std::map<string, string> parsedArgs = parseCmdLineArguments(argc, argv);
  if(parsedArgs.find("-nSteps")!=parsedArgs.end()) nSteps = atoi(parsedArgs.find("-nSteps")->second.c_str());
  if(parsedArgs.find("-nBalls")!=parsedArgs.end()) nBalls = atoi(parsedArgs.find("-nBalls")->second.c_str());
  if(parsedArgs.find("-dt")!=parsedArgs.end()) dt = stof(parsedArgs.find("-dt")->second.c_str());
  if(parsedArgs.find("-input")!=parsedArgs.end()) inputType = parsedArgs.find("-input")->second.c_str();
  if(parsedArgs.find("-doFrames")!=parsedArgs.end()) doFrames = parsedArgs.find("-doFrames")->second.c_str();

  Universe myUniverse;
  Object aObj;
  myUniverse.setTimeStep(dt);
  for(unsigned int iBall=0;iBall<nBalls;++iBall){
    if(inputType=="random") aObj = drawBall();
    if(inputType=="test") aObj = putBall(iBall);
    myUniverse.addObject(aObj);
  }  


  Plotter myPlotter;
  std::cout<<"Time step \t Position:\tSpeed:"<<std::endl;
  for(unsigned int iStep=0;iStep<nSteps;++iStep){
    if(doFrames=="true") myPlotter.plotBalls2D(myUniverse.getObjects(), iStep);	
    if(iStep%100==0){
      std::cout<<iStep<<std::endl;
      //myUniverse.printState();
    }
    myPlotter.accumulate(myUniverse.getObjects(), iStep);
    myUniverse.advanceTime();	
  }

  if(doFrames=="true") myPlotter.makeAnimation();
  myPlotter.plotAccumulated();
  return 0;  
}
