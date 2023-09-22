#include "MassMean.h"
#include "Event.h"
#include "ParticleReco.h"

#include <cmath>

using namespace std;


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
bool MassMean::add( const Event& ev ) {

	static ParticleReco* pr = ParticleReco::instance();
	double M = pr->Mass();

	if ( M<massMax && M>massMin ) // check for mass being in range
	{
		sum += (M-massMin); //subtract the min mass for better precision
		sqr += M*M;
		N++;
		return true;
	}
	else return false;
	
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

