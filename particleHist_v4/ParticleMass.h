#ifndef ParticleMass_h
#define ParticleMass_h

#include "util/include/ActiveObserver.h"
#include "AnalysisSteering.h"
#include <vector>
#include <string>

class Event;
class MassMean;
class TH1F;

class ParticleMass: public AnalysisSteering,
                    public ActiveObserver<Event> {
	
	public:
		ParticleMass (const AnalysisInfo* info);
		// deleted copy constructor and assignment to prevent unadvertent copy
		ParticleMass ( const ParticleMass& x ) = delete;
  		ParticleMass& operator=( const ParticleMass& x ) = delete;
  		~ParticleMass() override;
  		  
 		void beginJob() override;
 		void   endJob() override;
  		void update( const Event& ev ) override;

	
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
 
