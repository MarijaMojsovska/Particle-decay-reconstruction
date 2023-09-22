#include <iostream>
#include "Event.h"


void dump( const Event& ev ) 
{
	std::cout << ev.eventNumber() << std::endl;
	std::cout << ev.x() << " " << ev.y() << " " << ev.z() << std::endl;
	std::cout << ev.nParticles() << std::endl;
	for(int i=0; i<ev.nParticles(); i++)
	{
		std::cout << ev.particle(i)->q << " " << ev.particle(i)->p_x << " " << ev.particle(i)->p_y << " " << ev.particle(i)->p_z << std::endl;
	}
	return;
}
