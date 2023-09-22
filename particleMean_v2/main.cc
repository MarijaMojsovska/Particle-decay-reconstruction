#include <iostream>
#include <fstream>
#include <string>
#include "MassMean.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"

const Event* read( std::ifstream& file );
void dump( const Event& ev ); 
double mass( const Event& ev );


int main( int argc, char* argv[] ) {

  // open input file
	std::string file_name = "particle_events.txt";
	std::ifstream file(file_name);

  // create MassMean objects
	MassMean K0(0.495, 0.500);
	MassMean L0(1.115, 1.116);	

  // loop over events
  const Event* ev;
  while ( ( ev = read( file ) ) != nullptr ) {

	K0.add(*ev);
	L0.add(*ev);
//	dump( *ev );
//	delete ev;
  }

  // compute results
  K0.compute();
  L0.compute();

  // print number of selected events and results for both particles
  std::cout << "K0:  mean: " << K0.mMean() << " rms: " << K0.mRMS() << std::endl;
  std::cout << "L0:  mean: " << L0.mMean() << " rms: " << L0.mRMS() << std::endl;
  
  return 0;

}

