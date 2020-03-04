#ifndef SIMULATION_SETUP__H
#define SIMULATION_SETUP__H

#include <map>
#include <string>

#include "Object.h"

std::map<std::string, std::string> parseCmdLineArguments(int argc, char *argv[]);

Object drawBall();

Object putBall(unsigned int iBall);

#endif
