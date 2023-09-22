#ifndef LifetimeFit_h
#define LifetimeFit_h

#include <vector>

class Event;

class LifetimeFit {

 public:

	LifetimeFit( float min, float max, double minTime, double maxTime, double minScan, double maxScan, double step ); // mass range
	// deleted copy constructor and assignment to prevent unadvertent copy
	LifetimeFit           ( const LifetimeFit& x ) = delete;
	LifetimeFit& operator=( const LifetimeFit& x ) = delete;
	~LifetimeFit();

	bool add( const Event& ev );      // add data from a new event
	void compute();                   // compute mean and rms

	int nEvents () const;             // return number of accepted events

	double lifeTime () const;	    // return mean life time
	double lifeTimeError () const;    // return error life time


 private:

	double massMin; // min mass
	double massMax; // max mass

	double minTimeRange;
	double maxTimeRange;

	double minScanRange;
	double maxScanRange;

	double scanStep;

	std::vector<double> decayT; //container for all the decay times

	double meanLifeTime;
	double errorLifeTime;

};

#endif

