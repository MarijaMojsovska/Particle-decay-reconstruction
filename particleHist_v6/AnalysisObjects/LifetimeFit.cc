#include "AnalysisObjects/LifetimeFit.h"
#include "AnalysisFramework/Event.h"
#include "AnalysisObjects/ProperTime.h"
#include "AnalysisUtilities/QuadraticFitter.h"

#include <cmath>
#include <iostream>
using namespace std;

LifetimeFit::LifetimeFit( float min, float max, double minTime, double maxTime, double minScan, double maxScan, double step ):
massMin(min),
massMax(max),
minTimeRange(minTime),
maxTimeRange(maxTime),
minScanRange(minScan),
maxScanRange(maxScan),
scanStep(step)
{
}


LifetimeFit::~LifetimeFit() {
}


// add data from a new event
bool LifetimeFit::add( const Event& ev ) {

	static ProperTime* pt = ProperTime::instance();
	double t = pt->decayTime();

	if ( t<maxTimeRange && t>minTimeRange ) // check for mass being in range
	{
		decayT.push_back(t);
		return true;
	}
	else return false;
	
}


// compute mean and rms
void LifetimeFit::compute() {

	QuadraticFitter fit;
	for(double t_s=minScanRange; t_s<=maxScanRange; t_s+=scanStep )
	{	
		double L = 0.0;
		for(double T: decayT)
			L = L + (T/t_s) + log10(t_s) + log10( exp(-minTimeRange/t_s) - exp(-maxTimeRange/t_s) ); 
		fit.add(t_s, L);
	}
	meanLifeTime = -fit.b()/(2*fit.c());
	errorLifeTime = 1/(sqrt(2*fit.c()));
	fit.clear();
}


double LifetimeFit::lifeTime() const {
	return meanLifeTime;
}

double LifetimeFit::lifeTimeError() const {
	return errorLifeTime;
}

// return number of selected events
int LifetimeFit::nEvents() const {
	return decayT.size();
}



