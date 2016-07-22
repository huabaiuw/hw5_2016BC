#include <cstdlib>
#include "Coordinates.cc"
#include "Uniform.cc"

///////////////// This part is the declarations of the MonteCarlo Class /////////////////////////////////////
///////////////// In Rosetta, this part normally will be put in the separated .hh header file  
class MonteCarlo {
public:

  // Constructor
  // Usage: MonteCarlo mc = MonteCarlo(xyz, temp)
  MonteCarlo( Coordinates & xyz, float temperature );

  ~MonteCarlo();

  void set_temperature( float temp );
  float	get_temperature() const; 

  // This is the workhorse for MonteCarlo Class
  // this function compares the z values of the new Coordinates "new_xyz" and the stored Coordinates "last_accepted_xyz_". 
  // If the "new_xyz" has a lower z, the function will update "last_accepted_xyz_" with the new one, and return true.
  // If the "new_xyz" has a higher z, the function will still accept the "new_xyz" with certain probability, 
  // where the variable "temperature_" will affect how easy to accept a Coordinates with higher z value.
  // The higher the temperature, the easier to accept.
  // If the function rejected the new_xyz, it will overwrite the "new_xyz" with the "last_accepted_xyz_".
  // This is why there is pass by reference sign here "&".
  bool boltzmann(Coordinates & new_xyz);
  
  Coordinates const & get_last_accepted_coordinates() const { return last_accepted_xyz_;}

  double last_accepted_z() const;

private:
	Coordinates last_accepted_xyz_;

    double last_accepted_z_;

	float temperature_;
};

///////////////// The following part contains the implementations of the MonteCarlo Class /////////////////////////////////////
///////////////// In Rosetta, this part normally will be put in the .cc file  

MonteCarlo::MonteCarlo(
	Coordinates & xyz, 
    float temperature
):
	temperature_( temperature ),
	last_accepted_xyz_( xyz ),
	last_accepted_z_( xyz.get_z() )
{
}

MonteCarlo::~MonteCarlo() { std::cout << "This MonteCarlo Object is deleted!" << std::endl;}

bool
MonteCarlo::boltzmann(Coordinates & new_xyz) {
  double z_delta( new_xyz.get_z() - last_accepted_z_ ); // compare the z value of new_xyz and the stored last accepted z value;
                                                        // calcualte the difference, and save it in the variable "z_delta"; 

  double boltz_factor =  ( -z_delta / temperature_ );   // Useful Wiki page: https://en.wikipedia.org/wiki/Boltzmann_distribution
                                                        // This is Boltzmann weighting factor:"-E/kT",
                                                        // E stands for the energy gap, here we are using the difference of z value;
                                                        // k is Boltzmann constant; T is absolute temperature;
                                                        // Here, as well as in Rosetta, what we mean temperature is actually kT;
                                                        // The choose of temperature is empirical, "0.6" is a common choice in Rosetta.

  double probability = std::exp( std::min (40.0, std::max(-40.0,boltz_factor)) );
                                                        // Here we transform the boltzmann factor to a probability
                                                        // e^boltz_factor, and we are setting an upper and lower boundaries for boltz_factor;
                                                        // If the new z is lower than stored z, in other words, the z_delta is negative,
                                                        // the boltz_factor will be positive, and the probablity will be larger than 1.

  Uniform uniformRG; // create a Uniform Object, RG stands for "Random number Generator";

  // generate the uniformly distributed random number between 0 and 1. 
  // Then, for probability < 1, the smaller the probability, the higher chance the "new_xyz" get rejected. 
  if ( probability < 1 && uniformRG.getRandom() >= probability) {
    new_xyz = last_accepted_xyz_;
	return false; // rejected
  }

  // otherwise, accept the "new_xyz", and update the stored Coordinates and z value.

  last_accepted_z_ = new_xyz.get_z();
  last_accepted_xyz_ = new_xyz;
  return true; // accept!
}

float MonteCarlo::get_temperature() const { return temperature_; }

void MonteCarlo::set_temperature(float temp) { temperature_ = temp;}

double MonteCarlo::last_accepted_z() const { return last_accepted_z_;}

