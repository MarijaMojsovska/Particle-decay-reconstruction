#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include <vector>
#include <string>

class Event;
class MassMean;
class TH1F;

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
		struct Particle {
			std::string name;
			MassMean* pMean;
			TH1F* hMean;
		};
		std::vector<Particle*> pList; //vector of pointers to Particle objects
 		void pCreate( const std::string& name, float min, float max );
};

#endif
 
