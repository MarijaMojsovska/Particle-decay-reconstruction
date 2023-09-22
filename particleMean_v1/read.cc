#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Event.h"
#include "Particle.h"
using namespace std;


const Event* read( std::ifstream& file )
{
	Event* ev;
	string line;
	stringstream ss;

	if ( getline(file, line) ) 
		ev = new Event;
 	else return nullptr;

	ss << line;
	ss >> ev->id;
	ss.clear();
		
	getline(file, line);
	ss << line;
	ss >> ev->x >> ev->y >> ev->z;
	ss.clear();

	getline(file, line);
	ss << line;
	ss >> ev->n;
	ss.clear();
	
	ev->pp = new Particle*[ev->n];
	for(int i=0; i<ev->n; i++)
	{	
		Particle *p = new Particle;
		getline(file, line);
		ss << line;
		ss >> p->q >> p->p_x >> p->p_y >> p->p_z;
		ev->pp[i]=p;
		ss.clear();	
	}
	return ev;
}
