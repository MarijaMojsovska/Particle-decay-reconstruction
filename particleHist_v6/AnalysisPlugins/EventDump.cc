#include "AnalysisPlugins/EventDump.h"

#include "AnalysisFramework/Event.h"
#include "AnalysisFramework/AnalysisFactory.h"

#include <iostream>

using namespace std;

// concrete factory to create an EventDump analyzer
class EventDumpFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "dump" as name for this analyzer and factory
  EventDumpFactory(): AnalysisFactory::AbsFactory( "dump" ) {}
  // create an EventDump when builder is run
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new EventDump( info );
  }
};
// create a global EventDumpFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an EventDumpFactory will be available with name "dump".
static EventDumpFactory ed;

EventDump::EventDump( const AnalysisInfo* info ):
 AnalysisSteering( info ) {
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
void EventDump::update( const Event& ev ) {

	std::cout << ev.eventNumber() << std::endl;
	std::cout << ev.x() << " " << ev.y() << " " << ev.z() << std::endl;
	std::cout << ev.nParticles() << std::endl;
	for(int i=0; i<ev.nParticles(); i++)
	  std::cout << ev.particle(i)->q << " " << ev.particle(i)->p_x << " " << ev.particle(i)->p_y << " " << ev.particle(i)->p_z <<std::endl;
	
	return;
}

