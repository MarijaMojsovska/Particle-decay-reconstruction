#ifndef Utilites_h
#define Utilites_h

class Utilities
{
	public:
		double Energy( const float &px, const float &py, const float &pz, const double M );
		double InvariantMass( float &px, float &py, float &pz, double E );
};

#endif
