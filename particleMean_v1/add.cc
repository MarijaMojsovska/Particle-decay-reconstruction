#include "Event.h"

double mass( const Event& ev );

bool add (const Event& ev, double mMin, double mMax, double& sum, double& sqr)
{
	double M;
	M = mass(ev);
	
	if ( M<mMax && M>mMin )
	{
		sum += (M-mMin); //subtract the min mass for better precision
		sqr += M*M;
		return true;
	}
	
	else return false;	
}
