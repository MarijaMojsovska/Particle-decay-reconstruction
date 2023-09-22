#include "Event.h"
#include "Particle.h"

void clear( const Event* ev )
{
	for(int i=0; i<ev->n; i++)
		delete ev->pp[i]; //delete all the Particle structs
	
	delete[] ev->pp; //delete the array
	delete ev; //delete the event

	return;
}

