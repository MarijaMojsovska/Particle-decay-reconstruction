#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Event.h"


const Event* read( std::ifstream& file )
{
	Event* ev;
	std::string line;
	std::stringstream ss;
	int id,n;
	float x,y,z;

	if ( getline(file, line) ) 
	{
		ss << line;
		ss >> id;
		ss.clear();
		
		getline(file, line);
		ss << line;
		ss >> x >> y >> z;
		ss.clear();	
		
		ev = new Event(id, x, y, z);
	}
				 
	else return nullptr;

	getline(file, line);
	ss << line;
	ss >> n;
	ss.clear();
		
	int q;
	float p_x, p_y, p_z;
	for(int i=0; i<n; i++)
	{	
		getline(file, line);
		ss << line;
		ss >> q >> p_x >> p_y >> p_z;
		ev->add(q, p_x, p_y, p_z);
		ss.clear();	
	}
	return ev;
}
