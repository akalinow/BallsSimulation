#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>

#include "matplotlibcpp.h"
#include "Plotter.h"

namespace plt = matplotlibcpp;
///////////////////////////////////////////////
///////////////////////////////////////////////
Plotter::Plotter(){
  
  plt::backend("Agg");
 
}
///////////////////////////////////////////////
///////////////////////////////////////////////
void Plotter::plotBalls2D(const Universe::objectContainer & objects, unsigned int timeStep) const{

  //radiusToPixel depends on image size in pixels. Adjusted for figure.figsize   : 6.4, 6.4   ## figure size in inches
  double radiusToPixel = 141;
  double xLimHist = 1.0;
  double yLimHist = 1.0;
  int frameNumberWidth = 4;

  std::string title = "nBalls: "+std::to_string(objects.size()) + " time step: "+std::to_string(timeStep);
  plt::figure(1);
  //plt::xkcd();
  
  double radius = objects.front().getRadius()*radiusToPixel;
  double circleArea = 2.0*M_PI*std::pow(radius, 2);
  std::vector<double> x, y;
  std::vector<double> energy, px, py, pz;
  for(auto it: objects){
    x.push_back(it.getPosition().x());
    y.push_back(it.getPosition().y());
    plt::scatter(x, y, circleArea);
    x.clear();
    y.clear();
    const Vector3D &speed = it.getSpeed();
    double mass = it.getMass();
    energy.push_back(0.5*mass*speed.mag2());
    px.push_back(mass*speed.x());
    py.push_back(mass*speed.y());
    pz.push_back(mass*speed.z());    		     
  }

  plt::title(title);
  plt::xlim(-xLimHist,  xLimHist);
  plt::ylim(-yLimHist, yLimHist);
  plt::xlabel("x");
  plt::ylabel("y");
  std::ostringstream ostr;
  ostr<< "frame_position2D_"<< std::setfill('0') << std::setw(frameNumberWidth) <<timeStep<<".png";
  plt::save(plotsDirectory+ostr.str());
  plt::close();

  plt::figure(2);
  plt::subplot(2, 2, 1);
  plt::title(title);
  plt::hist(energy,20,"sienna");
  plt::xlabel("Energy");
  plt::ylabel("Particle count");

  plt::subplot(2, 2, 2);
  plt::title("");
  plt::hist(px,21,"seagreen");
  plt::xlabel("Momentum X componment");
  plt::ylabel("Particle count");

  plt::subplot(2, 2, 3);
  plt::title("");
  plt::hist(py,21,"seagreen");
  plt::xlabel("Momentum Y componment");
  plt::ylabel("Particle count");

  plt::subplot(2, 2, 4);
  plt::title("");
  plt::hist(pz,21,"seagreen");
  plt::xlabel("Momentum Z componment");
  plt::ylabel("Particle count");
  ostr.str("");
  ostr.clear();
  ostr<< "frame_energy_momentum_"<< std::setfill('0') << std::setw(frameNumberWidth) <<timeStep<<".png";
  plt::save(plotsDirectory+ostr.str());
  plt::close();
}
///////////////////////////////////////////////
///////////////////////////////////////////////
void Plotter::makeAnimation() const{

  std::cout<<"Plotter: making animation"<<std::endl;
  std::string command = "convert -delay 0.01 -loop 0 "+plotsDirectory+"frame_position2D*.png "+ plotsDirectory+"position2D_animation.gif";
  system(command.c_str());

  command = "convert -delay 0.01 -loop 0 "+plotsDirectory+"frame_energy_momentum*.png "+ plotsDirectory+"energy_momentum_animation.gif";
  system(command.c_str());

}
///////////////////////////////////////////////
///////////////////////////////////////////////
void Plotter::accumulate(const Universe::objectContainer & objects, unsigned int timeStep){

  double energy = 0.0, velocity=0.0, velocity2=0.0;

  Vector3D momentum;
  
  for(auto it: objects){
    const Vector3D &speed = it.getSpeed();
    double mass = it.getMass();
    energy += 0.5*mass*speed.mag2();
    momentum = momentum + speed*mass;
    velocity += speed.mag();
    velocity2 += speed.mag2();    
  }

  meanEnergy.push_back(energy/objects.size());
  meanMomentum.push_back(momentum.mag()/objects.size());
  meanVelocity.push_back(velocity/objects.size());
  meanVelocity2.push_back(velocity2/objects.size());
}
///////////////////////////////////////////////
///////////////////////////////////////////////
void Plotter::plotAccumulated() const{

  int nTimeSteps = meanEnergy.size();

  std::vector<double> time;
  std::vector<double> meanV_maxwell;
  double temperature = 0.0;
  double tmp = 0.0;
  double mass = 1.0;//FIXME
  for(int iTimeStep=0;iTimeStep<nTimeSteps;++iTimeStep){
    time.push_back(iTimeStep);
    temperature = getTemperature(meanEnergy.at(iTimeStep));
    tmp = sqrt(8.0*boltzmann_k*temperature/M_PI/mass);
    meanV_maxwell.push_back(tmp);			  
  }
  std::map<std::string, std::string> keywords;
  keywords["label"] = "<E>";
  plt::plot(time, meanEnergy, keywords);

  keywords["label"] = "<p>";
  plt::plot(time, meanMomentum, keywords);

  keywords["label"] = "<v>";
  plt::plot(time, meanVelocity, keywords);

  keywords["label"] = "<v> from Maxwell-Boltzmann for T = 2<E>/(3k)";
  plt::plot(time,  meanV_maxwell, keywords);
  plt::xlim(0.0, (double)nTimeSteps);
  plt::xlabel("time step");
  plt::ylabel("value [arbitrary units]");
  plt::legend();

  std::ostringstream ostr;
  ostr<< "accumulated.png";
  plt::save(plotsDirectory+ostr.str());
  plt::close();
}
///////////////////////////////////////////////
///////////////////////////////////////////////
double Plotter::getTemperature(double energy) const{
  return energy*2.0/3.0/boltzmann_k;  
}
///////////////////////////////////////////////
///////////////////////////////////////////////
