#ifndef LifetimeFit_h
#define LifetimeFit_h

class Event;

class LifetimeFit {

 public:

  LifetimeFit( float min, float max ); // mass range
  // deleted copy constructor and assignment to prevent unadvertent copy
  LifetimeFit           ( const LifetimeFit& x ) = delete;
  LifetimeFit& operator=( const LifetimeFit& x ) = delete;
  ~LifetimeFit();

  bool add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  int nEvents () const;             // return number of accepted events

 private:

	double massMin; // min mass
	double massMax; // max mass

	int N; // number of accepted events

};

#endif

