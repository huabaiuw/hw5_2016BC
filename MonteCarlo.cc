#include <MonteCarlo.hh>
#include <cstdlib>

MonteCarlo::MonteCarlo(
	Coordinates const & xyz, 
    float const temperature
):
    xyz_(xyz),
	temperature_( temperature ),
	last_accepted_z_( 10000 ),
	min_z_( 10000 )
{
}

MonteCarlo::~MonteCarlo() { std::cout << "HHAHHA" << std::endl;}

void
MonteCarlo::set_temperature(float const temp) { temperature_ = temp;}

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

bool
MonteCarlo::boltzmann(Coordinates & xyz) {

	double score_delta( xyz.get_z() - last_accepted_z_ );
	double boltz_factor =  ( -score_delta / temperature_ );
	double probability = std::exp( std::min (40.0, std::max(-40.0,boltz_factor)) );

	if ( probability < 1 ) {
        srand(2016);
		if ((double)rand() / (double)RAND_MAX >= probability ) {
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

