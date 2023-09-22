#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int read ( ifstream& file, float& x, float& y, float& z, int* q, float* p_x, float* p_y, float* p_z ) 
{
	int n;
	string line;
	stringstream ss;
	
	getline(file, line);
	ss << line;
	ss >> x >> y >> z;
	ss.clear();

	getline(file, line);
	ss << line;
	ss >> n;
	ss.clear();
	
	for(int i=0; i<n; i++)
	{
		getline(file, line);
		ss << line;
		ss >> q[i] >> p_x[i] >> p_y[i] >> p_z[i];
		ss.clear();	
	}
	return n;
}
