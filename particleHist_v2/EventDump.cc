#include "EventDump.h"
#include "Event.h"
#include <iostream>

using namespace std;

EventDump::EventDump() {
}


EventDump::~EventDump() {
}


// function to be called at execution start
void EventDump::beginJob() {
  return;
}


// function to be called at execution end
void EventDump::endJob() {
  return;
}


// function to be called for each event
void EventDump::process( const Event& ev ) {
	
	std::cout << ev.eventNumber() << std::endl;
	std::cout << ev.x() << " " << ev.y() << " " << ev.z() << std::endl;
	std::cout << ev.nParticles() << std::endl;
	for(int i=0; i<ev.nParticles(); i++)
	{
		std::cout << ev.particle(i)->q << " " << ev.particle(i)->p_x << " " << ev.particle(i)->p_y << " " << ev.particle(i)->p_z << std::endl;
	}
	return;

}

