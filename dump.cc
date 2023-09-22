#include <iostream>
using namespace std;

void dump (int id, int n, float x, float y, float z, int* q, float* p_x, float* p_y, float* p_z)
{
	cout << id << endl;
	cout << x << " " << y << " " << z << endl;
	cout << n << endl;
	for(int i=0; i<n; i++)
	{
		cout << q[i] << " " << p_x[i] << " " << p_y[i] << " " << p_z[i] << endl;
	}
	return;
}
