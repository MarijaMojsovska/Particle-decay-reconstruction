#include <iostream>
#include "Event.h"
#include "Particle.h"
using namespace std;


void dump( const Event& ev ) 
{
	cout << ev.id << endl;
	cout << ev.x << " " << ev.y << " " << ev.z << endl;
	cout << ev.n << endl;
	for(int i=0; i<ev.n; i++)
	{
		cout << ev.pp[i]->q << " " << ev.pp[i]->p_x << " " << ev.pp[i]->p_y << " " << ev.pp[i]->p_z << endl;
	}
	return;
}
