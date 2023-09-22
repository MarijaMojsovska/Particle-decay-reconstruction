#ifndef ParticleLifetime_h
#define ParticleLifetime_h

#include "util/include/ActiveObserver.h"
#include "AnalysisSteering.h"
#include <vector>
#include <string>

class Event;
class LifetimeFit;
class TH1F;

class ParticleLifetime: public AnalysisSteering,
                        public ActiveObserver<Event> {
	
	public:
		ParticleLifetime (const AnalysisInfo* info);
		// deleted copy constructor and assignment to prevent unadvertent copy
		ParticleLifetime ( const ParticleLifetime& x ) = delete;
  		ParticleLifetime& operator=( const ParticleLifetime& x ) = delete;
  		~ParticleLifetime() override;
  		  
 		void beginJob() override;
 		void   endJob() override;
  		void update( const Event& ev ) override;

	
	private:
		struct Particle {
			std::string name;
			LifetimeFit* pMean;
			TH1F* hMean;
		};
		std::vector<Particle*> pList; //vector of pointers to Particle objects
 		void pCreate( const std::string& name, float min, float max, double timeMin, double timeMax );
};

#endif
 
