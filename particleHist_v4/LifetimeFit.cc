#include "LifetimeFit.h"
#include "Event.h"
#include "ParticleReco.h"

#include <cmath>


LifetimeFit::LifetimeFit( float min, float max ):
massMin(min),
massMax(max),
N(0)
{
}


LifetimeFit::~LifetimeFit() {
}


// add data from a new event
bool LifetimeFit::add( const Event& ev ) {

	static ParticleReco* pr = ParticleReco::instance();
	double M = pr->Mass();

	if ( M<massMax && M>massMin ) // check for mass being in range
	{
		N++;
		return true;
	}
	else return false;
	
}


// compute mean and rms
void LifetimeFit::compute() {	
}


// return number of selected events
int LifetimeFit::nEvents() const {
	return N;
}


