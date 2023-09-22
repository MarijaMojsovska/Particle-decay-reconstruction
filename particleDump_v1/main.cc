#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std; 

int read ( ifstream& file, float& x, float& y, float& z, int* q, float* p_x, float* p_y, float* p_z );
void dump(int id, int n, float x, float y, float z, int* q, float* p_x, float* p_y, float* p_z);

int main()
{
//Open input file
	string file_name = "particle_events.txt";
	ifstream file(file_name);

//Event variables	
	int id;  //event identifier
	float x, y, z;  //the 3 decay point coordinates
	int n;  //number of particles
	int q[10];  //electric charges of the particles
	float p_x[10];  //the 3 momentum components of the particles
	float p_y[10];
	float p_z[10];	

	string line;
	while (getline(file, line)) 
	{
		stringstream ss(line);
		ss >> id;
		n = read (file, x, y, z, q, p_x, p_y, p_z);
		dump (id, n, x, y, z, q, p_x, p_y, p_z);
	}	
	return 0;
}


