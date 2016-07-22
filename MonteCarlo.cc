#include <cstdlib>
#include <string>
// #include <Landscape.cc>
#include "Coordinates.cc"

class MonteCarlo {
public:
    MonteCarlo(
		Coordinates & xyz, 
		float temperature
	);

	// ~MonteCarlo();

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

// MonteCarlo::~MonteCarlo() { std::cout << "HHAHHA" << std::endl;}


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
MonteCarlo::boltzmann(Coordinates & xyz) {

	double score_delta( xyz.get_z() - last_accepted_z_ );
	double boltz_factor =  ( -score_delta / temperature_ );
	double probability = std::exp( std::min (40.0, std::max(-40.0,boltz_factor)) );

	if ( probability < 1 ) {
		if ((double)rand() / (double)RAND_MAX >= probability ) {
            xyz = last_accepted_xyz_;
			return false; // rejected
		}
    }

	if (xyz.get_z() < min_z_) {
		min_z_ = xyz.get_z();
	}

	last_accepted_z_ = xyz.get_z();
	last_accepted_xyz_ = xyz;

	return true; // accept!
}

double
MonteCarlo::last_accepted_z() const { return last_accepted_z_;}

double
MonteCarlo::min_z() const
{
	return min_z_;
}

