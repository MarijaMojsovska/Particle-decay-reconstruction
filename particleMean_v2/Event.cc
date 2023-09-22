#include "Event.h"

Event::Event( int ID, float x, float y, float z ):
 // initializations
 id(ID),
 X(x),
 Y(y),
 Z(z),
 n(0)
 {
  // allocate a buffer for particle pointers
  pp = new Particle*[nMax];
}


Event::~Event() {
  // delete all the particle pointers
  for(int i=0; i<nMax; i++)
	delete pp[i];  
  // delete the pointers array
  delete[] pp;
}


void Event::add( int charge, float px, float py, float pz ) {
	
  // check for the number of particles, if maximum reached do nothing
  // and return
  if(n>=nMax)
  	return;

  // create the new particle and fill with data
  Particle *p = new Particle;
  p->q = charge;
  p->p_x = px;
  p->p_y = py;
  p->p_z = pz;
  // store the new particle pointer in the array and increase counter
  pp[n]=p;
  n++;

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
	return n;
}



// get particle
const Event::Particle* Event::particle( int i ) const {
	if(i<=nMax)
		return pp[i];
	else return nullptr;	
}

