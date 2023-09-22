#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include <vector>

class Event;
class MassMean;

class ParticleMass: public AnalysisSteering {
	
	public:
		ParticleMass();
		// deleted copy constructor and assignment to prevent unadvertent copy
		ParticleMass ( const ParticleMass& x ) = delete;
  		ParticleMass& operator=( const ParticleMass& x ) = delete;
  		~ParticleMass() override;
  		  
 		void beginJob() override;
 		void   endJob() override;
  		void process( const Event& ev ) override;

	
	private:
		std::vector<MassMean*> pList; //vector of pointers to MassMean objects
 
};

#endif
 
