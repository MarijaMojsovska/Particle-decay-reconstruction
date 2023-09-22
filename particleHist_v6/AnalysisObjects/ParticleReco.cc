#include "AnalysisObjects/ParticleReco.h"

#include "AnalysisFramework/Event.h"
#include "AnalysisUtilities/Utilities.h"
#include "AnalysisUtilities/Constants.h"

#include <cmath>

using namespace std;


// constructor
ParticleReco::ParticleReco() {
}


// destructor
ParticleReco::~ParticleReco() {
}


// recompute tag informations for new event
void ParticleReco::update( const Event& ev ) {
  // set default quantities
  type   = unknown;
  energy = -1.0;
  mass   = -1.0;

  // code to compute total energy and invariant mass for the two
  // mass hypotheses for the decay products

  // positive / negative track counters
  int positive = 0;
  int negative = 0;

  // variables for momentum sums
  float sum_px = 0.0;
  float sum_py = 0.0;
  float sum_pz = 0.0; 
  
  // variables for energy sums, for K0 and Lambda0
  double Etot_K0 = 0.0;
  double Etot_L0 = 0.0;
  //variables for the invariant masses, for K0 and Lambda0
  double M_K0;
  double M_L0;  

  Utilities u;
  Constants c;

  // loop over particles
  for (int i=0; i<ev.nParticles(); i++) 
  {
  	
  	if ( ev.particle(i)->q > 0 )
  		positive++;
  	else if ( ev.particle(i)->q < 0 )
  		negative++;

	sum_px += ev.particle(i)->p_x;  // update momentum sums
 	sum_py += ev.particle(i)->p_y; 
	sum_pz += ev.particle(i)->p_z; 	   

	//K0 hypotheses
	Etot_K0 += u.Energy(ev.particle(i)->p_x, ev.particle(i)->p_y, ev.particle(i)->p_z, c.mPion() );

	//Lambda0 hypotheses
	if ( ev.particle(i)->q > 0 )
  		Etot_L0 += u.Energy (ev.particle(i)->p_x, ev.particle(i)->p_y, ev.particle(i)->p_z, c.mProton());
  	else if ( ev.particle(i)->q < 0 )
  		Etot_L0 += u.Energy (ev.particle(i)->p_x, ev.particle(i)->p_y, ev.particle(i)->p_z, c.mPion() );  

  }

  if ((positive==1 && negative==1))  // check for exactly one positive and one negative track
  {
  // invariant masses for different decay product mass hypotheses
  	M_K0 = u.InvariantMass (sum_px, sum_py, sum_pz, Etot_K0);
  	M_L0 = u.InvariantMass (sum_px, sum_py, sum_pz, Etot_L0);

  // compare invariant masses with known values and set final values
  // ( type, energy and mass )
  	if ( sqrt( pow(( M_K0-c.mK0() ), 2)) < sqrt( pow(( M_L0-c.mLambda0() ), 2)) )
	{
		type = K0;
		mass = M_K0;
		energy = Etot_K0; 
	}	  
  	else
	{
  		type = Lambda0;
		mass = M_L0;
		energy = Etot_L0; 
	}

  }


  return;

}


// return particle type
int ParticleReco::Type() {
  // check for new event and return result
	check();
	return type;
}


// return particle energy
double ParticleReco::Energy() {
  // check for new event and return result
	check();
	return energy;
}


// return particle mass
double ParticleReco::Mass() {
  // check for new event and return result
  	check();
	return mass;
}

