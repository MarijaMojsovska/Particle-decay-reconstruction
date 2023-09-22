#include <math.h>
#include "Event.h"
#include "Particle.h"


// compute energy from momentum x,y,z components and invariant mass
double Energy( const float &px, const float &py, const float &pz, const double M )
{
	return sqrt( pow(M,2) + (pow(px,2) + pow(py,2) + pow(pz,2)) );
}

	

// compute invariant mass from momentum x,y,z components and energy
double InvariantMass( float &px, float &py, float &pz, double E )
{
	return sqrt( pow(E,2) - (pow(px,2) + pow(py,2) + pow(pz,2)) ); 
}


const double massPion    = 0.1395706;   // GeV/c^2
const double massProton  = 0.938272;    // GeV/c^2
const double massK0      = 0.497611;    // GeV/c^2
const double massLambda0 = 1.115683;    // GeV/c^2


double mass( const Event& ev ) {

  // retrieve particles in the event
  typedef const Particle* part_ptr;
  const part_ptr* particles = ev.pp;

  // positive / negative track counters
  int positive = 0;
  int negative = 0;

  // variables for momentum sums
  float sum_px = 0.0;
  float sum_py = 0.0;
  float sum_pz = 0.0; 
  
  // variables for energy sums, for K0 and Lambda0
  float Etot_K0 = 0.0;
  float Etot_L0 = 0.0;
  //variables for the invariant masses, for K0 and Lambda0
  float M_K0;
  float M_L0;  

  // loop over particles
  for (int i=0; i<ev.n; i++) 
  {
  	
  	if ( particles[i]->q > 0 )
  		positive++;
  	else if ( particles[i]->q < 0 )
  		negative++;

	sum_px += particles[i]->p_x;  // update momentum sums
 	sum_py += particles[i]->p_y; 
	sum_pz += particles[i]->p_z; 	   
    
	//K0 hypotheses
	Etot_K0 += Energy(particles[i]->p_x, particles[i]->p_y, particles[i]->p_z, massPion );
	//Lambda0 hypotheses
	if ( particles[i]->q > 0 )
  		Etot_L0 += Energy (particles[i]->p_x, particles[i]->p_y, particles[i]->p_z, massProton);
  	else if ( particles[i]->q < 0 )
  		Etot_L0 += Energy (particles[i]->p_x, particles[i]->p_y, particles[i]->p_z, massPion );  
  }

  if ((positive==1 && negative==1))  // check for exactly one positive and one negative track
  {
  // invariant masses for different decay product mass hypotheses
  	M_K0 = InvariantMass (sum_px, sum_py, sum_pz, Etot_K0);
  	M_L0 = InvariantMass (sum_px, sum_py, sum_pz, Etot_L0);

  	if ( sqrt( pow((M_K0-massK0),2)) < sqrt( pow((M_L0-massLambda0),2)) ) // compare invariant masses with known values and return the nearest one
		  return M_K0;
  	else
  		return M_L0;
  }
  else // otherwise return negative (unphysical) invariant mass
  	return -1;
  
}

