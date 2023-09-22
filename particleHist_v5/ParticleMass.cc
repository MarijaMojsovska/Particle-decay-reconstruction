#include "ParticleMass.h"

#include "Event.h"
#include "MassMean.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"
#include "ParticleReco.h"

#include "TH1F.h"
#include "TFile.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


// concrete factory to create an ParticleMass analyzer
class ParticleMassFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleMassFactory(): AnalysisFactory::AbsFactory( "plot" ) {}
  // create an ParticleMass when builder is run
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new ParticleMass( info );
  }
};
// create a global ParticleMassFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ParticleMassFactory will be available with name "plot".
static ParticleMassFactory pm;

ParticleMass::ParticleMass (const AnalysisInfo* info) :
 AnalysisSteering( info ){
}

ParticleMass::~ParticleMass() {
}


void ParticleMass::beginJob() {
  ifstream file( aInfo->value( "ranges" ).c_str() );
  string name;
  float mMin;
  float mMax;
  while ( file >> name >> mMin >> mMax ) pCreate( name, mMin, mMax );

  return;
}


void ParticleMass::endJob() {
  // save current working area
  TDirectory* currentDir = gDirectory;
  // open histogram file
  TFile* file = new TFile( aInfo->value( "plot" ).c_str(), "RECREATE" );
  
  // loop over objects
  for ( Particle* par: pList ) {
    MassMean* pMean = par->pMean;
    TH1F* hMean = par->hMean;
    pMean->compute();// compute results
    // get mean and rms
    const int N = pMean->nEvents();
    const double mean = pMean->mMean();
    const double rms  = pMean->mRMS ();
    // print results
    cout  << par->name << "\t N=" << N << "\t Mmean: " << mean << "\t Mrms: " << rms << endl;
    hMean->Write();//save histogram
 }

  // close file
  file->Close();
  delete file;
  // restore working area
  currentDir->cd();

  return;
}



void ParticleMass::update( const Event& ev ) {
  // loop over objects
  for ( Particle* par: pList ) {
    MassMean* pMean = par->pMean; 
    TH1F* hMean = par->hMean;

//fill the histogram with the invariant mass for the accepted events
    if(pMean->add( ev )==true){
	static ParticleReco* pr = ParticleReco::instance();
	hMean->Fill(pr->Mass());
    }
  }
  return;
}

void ParticleMass::pCreate( const string& name, float min, float max ) {

  // create name for TH1F object
  const char* hName = ("mass"+name).c_str();
  Particle* p = new Particle;
  p-> name = name;
  p->pMean = new MassMean( min, max );
  p->hMean = new TH1F( hName, hName, 100, min, max );
  pList.push_back( p );

  return;

}



