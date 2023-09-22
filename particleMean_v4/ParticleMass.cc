#include "ParticleMass.h"

#include "Event.h"
#include "MassMean.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


ParticleMass::ParticleMass() {
}
ParticleMass::~ParticleMass() {
}

// function to be called at execution start
void ParticleMass::beginJob() {

  pList.push_back( new MassMean( 0.495, 0.500 ) ); //K0
  pList.push_back( new MassMean( 1.115, 1.116 ) ); //L0

  return;
}


void ParticleMass::endJob() {

  // loop over objects
  for ( MassMean* mMean: pList ) {
    mMean->compute();// compute results
    // get mean and rms energies
    const double mean = mMean->mMean();
    const double rms  = mMean->mRMS ();
    // print results
    cout  << "mean: " << mean << "\t rms: " << rms << endl;
 }
 
  return;
}



void ParticleMass::process( const Event& ev ) {
  // loop over objects
  for ( MassMean* mMean: pList ) 
  	mMean->add( ev );
  return;
}



