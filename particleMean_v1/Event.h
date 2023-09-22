#ifndef Event_h
#define Event_h

#include "Particle.h"

struct Event {
	int id;  //event identifier
	float x, y, z;  //the 3 decay point coordinates
	int n;  //number of particles
	Particle **pp;  //array of pointers to Particle structs
};

#endif

