#include <iostream>
#include <random>
#include <chrono>

#include "SimulationSetup.h"

///////////////////////////////////////////////
///////////////////////////////////////////////
std::map<std::string, std::string> parseCmdLineArguments(int argc, char *argv[]){

  std::map<std::string, std::string> parsedArgs = { { "-nSteps","100"}, {"-dt", "0.1"}, {"-nBalls","2"}, { "-input","random"} };

  for(int iArg=1;iArg<argc;++iArg){
    for(auto & it: parsedArgs){
      if(std::string(argv[iArg])==it.first && argc>iArg+1){
	it.second = std::string(argv[iArg+1]);
      }
    }
  }

  std::cout<<"Parsed command line arguments: "<<std::endl;
  for(auto it: parsedArgs){
    std::cout<<it.first<<" "<<it.second<<std::endl;
   }
  return parsedArgs;
}
///////////////////////////////////////////////
///////////////////////////////////////////////
//FIX ME move to class, or use good seed
std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0,1.0);

Object drawBall(){

  Object aObj;
  aObj.setMass(1.0);
  aObj.setRadius(0.01);
  aObj.setPosition(distribution(generator), distribution(generator), distribution(generator));
  aObj.setSpeed(distribution(generator), distribution(generator), distribution(generator));
  return aObj;
}
///////////////////////////////////////////////
///////////////////////////////////////////////
