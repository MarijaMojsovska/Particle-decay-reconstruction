#ifndef MassMean_h
#define MassMean_h

class Event;

class MassMean {

 public:

  MassMean( float min, float max ); // mass range
  // deleted copy constructor and assignment to prevent unadvertent copy
  MassMean           ( const MassMean& x ) = delete;
  MassMean& operator=( const MassMean& x ) = delete;
  ~MassMean();

  void add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  int nEvents () const;                    // return number of accepted events
  double mMean() const;                               // return mean mass
  double mRMS () const;                              // return rms  mass

 private:

	double massMin; // min mass
	double massMax; // max mass

	int N; // number of accepted events
	double sum; // sum of masses
	double sqr; // sum of masses square

	double mean; // mean mass
	double rms; // rms  mass

};

#endif

