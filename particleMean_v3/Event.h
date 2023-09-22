#ifndef Event_h
#define Event_h

#include <vector>

class Event {

 public:

  Event( int ID, float x, float y, float z ); // create an event with number "n"
                                             // and coordinates x, y, z
                                             
// deleted copy constructor and assignment to prevent unadvertent copy
  Event           ( const Event& x ) = delete;
  Event& operator=( const Event& x ) = delete;  
                                          
  ~Event();

  // composite object Particle to hold all information for each particle
  // ( electric charge and x,y,z momentum components )
  struct Particle {
    int q;  //electric charges of the particle
  	float p_x;  //the 3 momentum components of the particles
  	float p_y;   
  	float p_z;
  };
  typedef const Particle* part_ptr;

  // add a particle to the event
  void add( int charge, float px, float py, float pz );

  // get event id.
  int eventNumber() const;
  // get decay point coordinates
  float x () const;
  float y () const;
  float z () const;

  // get number of particles
  int nParticles () const;
  // get particle
  part_ptr particle( unsigned int i ) const;



 private:
  // event-specific informations:
  	int id;  //event identifier
	float X, Y, Z;  //the 3 decay point coordinates
	std::vector<Particle*> pp;
};

#endif

