#include "MassMean.h"
#include "Event.h"

#include <cmath>

double mass( const Event& ev );


MassMean::MassMean( float min, float max ):
massMin(min),
massMax(max),
N(0),
sum(0.0),
sqr(0.0)
{
}


MassMean::~MassMean() {
}


// add data from a new event
void MassMean::add( const Event& ev ) {

	double M;
	M = mass(ev);
	if ( M<massMax && M>massMin ) // check for mass being in range
	{
		sum += (M-massMin); //subtract the min mass for better precision
		sqr += M*M;
		N++;
	}
	
}


// compute mean and rms
void MassMean::compute() {
	mean = (sum*1.0 / N) + massMin; //adding back the min mass
	rms = (sqr*1.0 / N) - pow( ((sum*1.0 / N) + massMin), 2);	
}


// return number of selected events
int MassMean::nEvents() const {
	return N;
}

// return mean and rms
double MassMean::mMean() const {
	return mean;
}
double MassMean::mRMS() const {
	return rms;
} 

