#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
using namespace std; 

struct Event;
struct Particle;

const Event* read( std::ifstream& file );
void dump( const Event& ev );
void clear( const Event* ev );
bool add (const Event& ev, double mMin, double mMax, double& sum, double& sqr);



int main()
{
	int N = 0; //number of accepted events
	double sum = 0.0; //sum of invariant masses
	double sqr = 0.0; //sum of squares of invariant masses
	double mean; //mean invariant mass
	double rms; //rms invariant mass
	
//Open input file
	string file_name = "particle_events.txt";
	ifstream file(file_name);

// loop over events
	const Event* ev;
	while ( ( ev = read( file ) ) != nullptr )
	{
		if ( add( *ev, 0.490, 0.505, sum, sqr ) )	N++;
    	//dump( *ev );
    	clear( ev );
	}
	
	mean = (sum*1.0 / N) + 0.490; //adding back the min mass
	rms = (sqr*1.0 / N) - pow( ((sum*1.0 / N) + 0.490), 2);	
	
	cout << "mean: " << mean << endl;
	cout << "rms: " << rms << endl;

	return 0;
}


