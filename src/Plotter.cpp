#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>

#include "matplotlibcpp.h"
#include "Plotter.h"

namespace plt = matplotlibcpp;
///////////////////////////////////////////////
///////////////////////////////////////////////
void Plotter::plotBalls2D(const Universe::objectContainer & objects, unsigned int timeStep) const{

  double radiusToPixel = 1000;
  double xLimHist = 1.0;
  double yLimHist = 1.0;
  int frameNumberWidth = 4;

  std::vector<double> x, y;
  for(auto it: objects){
    x.push_back(it.getPosition().x());
    y.push_back(it.getPosition().y());    
  }
  double radius = objects.front().getRadius()*radiusToPixel;
  double circleArea = std::pow(radius, 2);

  //plt::figure(); 
  plt::xlim(-xLimHist,  xLimHist);
  plt::ylim(-yLimHist, yLimHist);
  plt::xlabel("x");
  plt::ylabel("y");
  
  plt::scatter(x, y, circleArea);
  plt::show(false);

  //std::string fileName = "frame_"+std::to_string(timeStep)+".png";
  std::ostringstream ostr;
  ostr<< "frame_"<< std::setfill('0') << std::setw(frameNumberWidth) <<timeStep<<".png";
  plt::savefig(ostr.str());
  plt::close();
}
///////////////////////////////////////////////
///////////////////////////////////////////////
void Plotter::makeAnimation() const{

  std::cout<<"Plotter: making animation"<<std::endl;
  std::string command = "convert -delay 0.01 -loop 0 frame_*.png animation.gif";
  system(command.c_str());
  std::cout<<"Done."<<std::endl;
  
}
///////////////////////////////////////////////
///////////////////////////////////////////////
