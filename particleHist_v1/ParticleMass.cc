#include "ParticleMass.h"

#include "Event.h"
#include "MassMean.h"

#include "TH1F.h"
#include "TFile.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;
double mass( const Event& ev );

ParticleMass::ParticleMass() {
}
ParticleMass::~ParticleMass() {
}


void ParticleMass::beginJob() {
  pCreate("K0",0.495, 0.500);
  pCreate("L0",1.115, 1.116);
  return;
}


void ParticleMass::endJob() {
  // save current working area
  TDirectory* currentDir = gDirectory;
  // open histogram file
  TFile* file = new TFile( "hist.root", "RECREATE" );
  
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
    cout  << "N=" << N << "\t mean: " << mean << "\t rms: " << rms << endl;
    hMean->Write();//save histogram
 }

  // close file
  file->Close();
  delete file;
  // restore working area
  currentDir->cd();

  return;
}



void ParticleMass::process( const Event& ev ) {
  // loop over objects
  for ( Particle* par: pList ) {
    MassMean* pMean = par->pMean; 
    TH1F* hMean = par->hMean;

//fill the histogram with the invariant mass for the accepted events
    if(pMean->add( ev )==true)
	hMean->Fill(mass(ev));
 
  }
  return;
}


void ParticleMass::pCreate( const string& name, float min, float max ) {

  // create name for TH1F object
  const char* hName = name.c_str();

  Particle* p = new Particle;
  p-> name = name;
  p->pMean = new MassMean( min, max );
  p->hMean = new TH1F( hName, hName, 100, min, max );
  pList.push_back( p );

  return;

}



