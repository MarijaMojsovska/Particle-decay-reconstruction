#include "Event.h"
#include <vector>
using namespace std;

Event::Event( int ID, float x, float y, float z ):
 // initializations
 id(ID),
 X(x),
 Y(y),
 Z(z)
 {
  // reserve for the vector a number of elements equal to the maximum number of particles
  pp.reserve(10);
}


Event::~Event() {
  for (vector<Particle*>::iterator it = pp.begin(); it != pp.end(); it++)
     delete *it; // delete all the particle pointers  
}


void Event::add( int charge, float px, float py, float pz ) {
	
  // check for the number of particles, if maximum reached do nothing
  // and return
  if(pp.capacity()==0)
  	return;

  // create the new particle and fill with data
  Particle *p = new Particle;
  p->q = charge;
  p->p_x = px;
  p->p_y = py;
  p->p_z = pz;
  // store the new particle pointer
  pp.push_back(p);

  return;
}


// get event id.
int Event::eventNumber() const {
  return id;
}


// get decay point coordinates
float Event::x () const {
	return X;
}
float Event::y () const {
	return Y;
}
float Event::z () const {
	return Z;
} 



// get number of particles
int Event::nParticles () const{
	return pp.size();
}



// get particle
const Event::Particle* Event::particle( unsigned int i ) const {
	if(i<=pp.size())
		return pp[i];
	else return nullptr;	
}

