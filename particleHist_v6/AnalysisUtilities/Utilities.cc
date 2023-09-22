#include "AnalysisUtilities/Utilities.h"
#include <math.h>


// compute energy from momentum x,y,z components and invariant mass
double Utilities::Energy( const float &px, const float &py, const float &pz, const double M )
{
	return sqrt( pow(M,2) + (pow(px,2) + pow(py,2) + pow(pz,2)) );
}


// compute invariant mass from momentum x,y,z components and energy
double Utilities::InvariantMass( float &px, float &py, float &pz, double E )
{
	return sqrt( pow(E,2) - (pow(px,2) + pow(py,2) + pow(pz,2)) ); 
}
