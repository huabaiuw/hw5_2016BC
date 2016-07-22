#include <cstdlib>
#include <string>
#include "Coordinates.cc"


///////////////// This part is the declarations of the MonteCarlo Class /////////////////////////////////////
///////////////// In Rosetta code convention, the part normally will be put in the separated .hh header file  
class MonteCarlo {
public:
    MonteCarlo( Coordinates & xyz, float temperature);

	~MonteCarlo();

	void
	set_temperature( float temp );

    float	
	get_temperature() const; 

	bool
	boltzmann(Coordinates & xyz);

	Coordinates const &
	get_last_accepted_coordinates() const
	{
		return last_accepted_xyz_;
	}

	Coordinates const &
	get_coordinates_with_min_z() const
	{
		return xyz_with_min_z_;
	}

	double last_accepted_z() const;
	double min_z() const;

	void clear();

private:
    Coordinates xyz_;
	Coordinates last_accepted_xyz_;
	Coordinates xyz_with_min_z_;

    double last_accepted_z_;
    double min_z_;

	float temperature_;
};



///////////////// The following part is the implementations of the MonteCarlo Class /////////////////////////////////////
///////////////// In Rosetta code convention, the part normally will be put in the .cc file  

MonteCarlo::MonteCarlo(
	Coordinates & xyz, 
    float temperature
):
	temperature_( temperature ),
	last_accepted_z_( xyz.get_z() ),
	last_accepted_xyz_( xyz ),
	min_z_( xyz.get_z() )
{
    xyz_.clone(xyz);
    boltzmann(xyz); 
}

MonteCarlo::~MonteCarlo() { std::cout << "HHAHHA" << std::endl;}

void 
MonteCarlo::clear() {
// 	last_accepted_xyz_ = NULL;
// 	xyz_with_min_z_(NULL); 
}

float
MonteCarlo::get_temperature() const
{
	return temperature_;
}

void
MonteCarlo::set_temperature(float temp) { temperature_ = temp;}

bool
MonteCarlo::boltzmann(Coordinates & new_xyz) {

	double z_delta( new_xyz.get_z() - last_accepted_z_ ); // compare the z of new_xyz and the stored last accepted z;
                                                          // calcualte the difference, and save it in the variable "z_delta"; 

	double boltz_factor =  ( -z_delta / temperature_ );   // 
	double probability = std::exp( std::min (40.0, std::max(-40.0,boltz_factor)) );

	if ( probability < 1 && (double)rand() / (double)RAND_MAX >= probability) {
            new_xyz = last_accepted_xyz_;
			return false; // rejected
    }

	if (new_xyz.get_z() < min_z_) {
		min_z_ = new_xyz.get_z();
	}

	last_accepted_z_ = new_xyz.get_z();
	last_accepted_xyz_ = new_xyz;

	return true; // accept!
}



double
MonteCarlo::last_accepted_z() const { return last_accepted_z_;}

double
MonteCarlo::min_z() const { return min_z_;}

