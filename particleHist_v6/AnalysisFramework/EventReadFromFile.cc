#include "AnalysisFramework/EventReadFromFile.h"

#include "AnalysisFramework/Event.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// read data from file "name"
EventReadFromFile::EventReadFromFile( const string& name ) {
  file = new ifstream( name.c_str() );
}


EventReadFromFile::~EventReadFromFile() {
  delete file;
}


// get an event
const Event* EventReadFromFile::get() {
  return readFile();
}


// read an event
const Event* EventReadFromFile::readFile() {
	Event* ev;
	string line;
	stringstream ss;
	int id,n;
	float x,y,z;

	if ( getline(*file, line) ) 
	{
		ss << line;
		ss >> id;
		ss.clear();
		
		getline(*file, line);
		ss << line;
		ss >> x >> y >> z;
		ss.clear();	
		
		ev = new Event(id, x, y, z);
	}			 
	else return nullptr;

	getline(*file, line);
	ss << line;
	ss >> n;
	ss.clear();
		
	int q;
	float p_x, p_y, p_z;
	for(int i=0; i<n; i++)
	{	
		getline(*file, line);
		ss << line;
		ss >> q >> p_x >> p_y >> p_z;
		ev->add(q, p_x, p_y, p_z);
		ss.clear();	
	}
	return ev;
}

