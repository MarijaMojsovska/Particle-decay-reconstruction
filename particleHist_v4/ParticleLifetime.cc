#include "ParticleLifetime.h"

#include "Event.h"
#include "LifetimeFit.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"
#include "ProperTime.h"

#include "TH1F.h"
#include "TFile.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


// concrete factory to create an ParticleLifetime analyzer
class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleLifetimeFactory(): AnalysisFactory::AbsFactory( "time" ) {}
  // create an ParticleLifetime when builder is run
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new ParticleLifetime( info );
  }
};
// create a global ParticleLifetimeFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ParticleLifetimeFactory will be available with name "time".
static ParticleLifetimeFactory pm;

ParticleLifetime::ParticleLifetime (const AnalysisInfo* info) :
 AnalysisSteering( info ){
}

ParticleLifetime::~ParticleLifetime() {
}


void ParticleLifetime::beginJob() {
  pCreate("K0",0.495, 0.500, 10.0, 500.0);
  pCreate("L0",1.115, 1.116, 10.0, 1000.0);
  return;
}


void ParticleLifetime::endJob() {
  // save current working area
  TDirectory* currentDir = gDirectory;
  // open histogram file
  TFile* file = new TFile( aInfo->value( "plot" ).c_str(), "UPDATE" );
  
  // loop over objects
  for ( Particle* par: pList ) {
    LifetimeFit* pMean = par->pMean;
    TH1F* hMean = par->hMean;
    pMean->compute();// compute results

    hMean->Write();//save histogram
 }

  // close file
  file->Close();
  delete file;
  // restore working area
  currentDir->cd();

  return;
}



void ParticleLifetime::update( const Event& ev ) {
  // loop over objects
  for ( Particle* par: pList ) {
    LifetimeFit* pMean = par->pMean; 
    TH1F* hMean = par->hMean;

//fill the histogram with the decay time for the accepted events
    if(pMean->add( ev )==true){ 
	static ProperTime* pt = ProperTime::instance();
	hMean->Fill(pt->decayTime());
    }
  }
  return;
}


void ParticleLifetime::pCreate( const string& name, float min, float max, double timeMin, double timeMax  ) {

  // create name for TH1F object
  const char* hName = ("time"+name).c_str();

  Particle* p = new Particle;
  p-> name = name;
  p->pMean = new LifetimeFit( min, max );
  p->hMean = new TH1F( hName, hName, 100, timeMin, timeMax );
  pList.push_back( p );

  return;

}



