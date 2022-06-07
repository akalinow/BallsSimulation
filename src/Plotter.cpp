#include <algorithm>
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
  double maxY = 0.2*objects.size();
  int frameNumberWidth = 4;

  std::string title = "nBalls: "+std::to_string(objects.size()) + " time step: "+std::to_string(timeStep);
  plt::title(title);
  plt::xlim(-xLimHist,  xLimHist);
  plt::ylim(-yLimHist, yLimHist);
  plt::xlabel("x");
  plt::ylabel("y");

  //plt::xkcd();
  
  double radius = objects.front().getRadius()*radiusToPixel;
  double circleArea = 2.0*M_PI*std::pow(radius, 2);
  std::vector<double> x, y;
  std::vector<double> energy, px, py, pz;
  std::vector<double> speedV;
  for(auto it: objects){
    x.push_back(it.getPosition().x());
    y.push_back(it.getPosition().y());
    plt::scatter(x, y, circleArea);
    x.clear();
    y.clear();
    const Vector3D &speed = it.getSpeed();
    double mass = it.getMass();
    energy.push_back(0.5*mass*speed.mag2());
    speedV.push_back(speed.mag());
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

  int nBins = 20;
  std::vector<double> energyProb(nBins);
  std::vector<double> energyValues(nBins);
  double temperature = 2*0.5/3.0;//FIXME
  double e = 0.0;
  double de = *std::max_element(energy.begin(), energy.end())/nBins;
  double norm = objects.size()/(boltzmann_k*temperature);
  for(unsigned int iBin=0;iBin<energyProb.size();++iBin){
    e = (iBin+0.5)*de;
    energyProb.at(iBin) = norm*exp(-e/(boltzmann_k*temperature))*de;
    energyValues.at(iBin) = e;
  }

  double m = 1.0;
  norm = 4.0*M_PI*pow(m/(2.0*M_PI*boltzmann_k*temperature),3/2.0);
  norm *=objects.size();
  double dv = *std::max_element(speedV.begin(), speedV.end())/nBins;
  double v = 0.0;
  double e_kin = 0.0;
  std::vector<double> speedProb(nBins);
  std::vector<double> speedValues(nBins);
  double sum = 0.0;
  for(unsigned int iBin=0;iBin<speedProb.size();++iBin){
    v = (iBin+0.5)*dv;
    e_kin = m*pow(v,2)/2.0;
    speedProb.at(iBin) = norm*pow(v,2)*exp(-e_kin/(boltzmann_k*temperature))*dv;
    sum += speedProb.at(iBin);
    speedValues.at(iBin) = v;
  }
  
  plt::figure(2);
  plt::subplot(2, 2, 1);
  plt::title(title);
  plt::hist(speedV,nBins,"mediumpurple");
  std::map<std::string, std::string> keywords;
  keywords["label"] = "$N(v) = N_{0} \\cdot Maxwell(v)dv$";
  plt::plot(speedValues, speedProb, keywords);
  plt::xlim(0, 3);
  plt::ylim(0.0, maxY);
  plt::xlabel("Speed");
  plt::ylabel("Particle count");
  plt::legend();

  plt::subplot(2, 2, 2);
  plt::hist(energy,nBins,"sienna");
  keywords["label"] = "$N(E) = \\frac{N_{0}}{k_{B}T}e^{-E/k_{B}T}dE$";
  plt::plot(energyValues, energyProb, keywords);
  plt::xlim(0, 3);
  plt::ylim(0.0, 1.5*maxY);
  plt::xlabel("Energy");
  plt::ylabel("Particle count");
  plt::legend();
  
  plt::subplot(2, 2, 3);
  plt::title("");
  plt::hist(px,21,"mediumseagreen");
  plt::xlim(-2, 2);
  plt::ylim(0.0, maxY);
  plt::xlabel("Momentum X componment");
  plt::ylabel("Particle count");

  plt::subplot(2, 2, 4);
  plt::title("");
  plt::hist(py,21,"mediumseagreen");
  plt::xlim(-2, 2);
  plt::ylim(0.0, maxY);
  plt::xlabel("Momentum Y componment");
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
  plt::xlim(0.0, (double)nTimeSteps);
  plt::xlabel("time step");
  plt::ylabel("value [arbitrary units]");

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
