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
// an ParticleLifetimeFactory will be available with name "plot".
static ParticleLifetimeFactory pm;

ParticleLifetime::ParticleLifetime (const AnalysisInfo* info) :
 AnalysisSteering( info ){
}

ParticleLifetime::~ParticleLifetime() {
}


void ParticleLifetime::beginJob() {
  ifstream file("particleFitters");
  string name;
  float massMin;
  float massMax;
  double timeMin;
  double timeMax;
  double scanMin;
  double scanMax;
  double Step;

  while ( file >> name >> massMin >> massMax >> timeMin >> timeMax >> scanMin >> scanMax >> Step ) 
	pCreate( name, massMin, massMax, timeMin, timeMax, scanMin, scanMax, Step);

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
    // get mean and rms
    const int N = pMean->nEvents();// unused var
    const double mean = pMean->lifeTime();
    const double rms  = pMean->lifeTimeError ();
    // print results
    cout  << par->name << "\t N=" << N << "\t Tmean: " << mean << "\t Trms: " << rms << endl;
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

//fill the histogram with the invariant mass for the accepted events
    if(pMean->add( ev )==true){ 
	static ProperTime* pt = ProperTime::instance();
	hMean->Fill(pt->decayTime());
    }
  }
  return;
}


void ParticleLifetime::pCreate( string& name, float massMin, float massMax, double timeMin, double timeMax, double scanMin, double scanMax, double Step  ) {

  // create name for TH1F object
  const char* hName = ("time"+name).c_str();

  Particle* p = new Particle;
  p-> name = name;
  p->pMean = new LifetimeFit( massMin, massMax, timeMin, timeMax, scanMin, scanMax, Step );
  p->hMean = new TH1F( hName, hName, 100, timeMin, timeMax );
  pList.push_back( p );

  return;

}


