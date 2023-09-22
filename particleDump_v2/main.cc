#include <iostream>
#include <fstream>
#include <string>
using namespace std; 

struct Event;
struct Particle;

const Event* read( std::ifstream& file );
void dump( const Event& ev );
void clear( const Event* ev );



int main()
{
//Open input file
	string file_name = "particle_events.txt";
	ifstream file(file_name);

// loop over events
	const Event* ev;
	while ( ( ev = read( file ) ) != nullptr )
	{
    	dump( *ev );
    	clear( ev );
	}

	return 0;
}


