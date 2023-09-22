#include "ProperTime.h"

#include "Event.h"
#include "ParticleReco.h"
#include "Constants.h"

#include <cmath>

using namespace std;


// constructor
ProperTime::ProperTime() {
}


// destructor
ProperTime::~ProperTime() {
}


// recompute tag informations for new event
void ProperTime::update( const Event& ev ) {

  static ParticleReco* pr = ParticleReco::instance();
  Constants c;

  //caluculate decay time 
  double d = sqrt( pow(ev.x(),2) + pow(ev.y(),2) + pow(ev.z(),2) ); //distance of the decay point from the origin
  time = (d * pr->Mass()) / ( sqrt( pow(pr->Energy(),2)-pow(pr->Mass(),2) ) * c.LightVelocity() );

  return;

}


// return decay time
double ProperTime::decayTime() {
  // check for new event and return result
  	check();
	return time;
}

