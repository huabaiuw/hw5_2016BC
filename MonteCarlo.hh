#include <string>
// #include <Landscape.cc>
#include <Coordinates.cc>

class MonteCarlo {
public:
    MonteCarlo(
		Coordinates const & xyz, 
		float const temperature
	);

	~MonteCarlo();

	void
	set_temperature( float const temp );

    float	
	get_temperature() const; 

	bool
	boltzmann(Coordinates & xyz);

	Coordinates const &
	get_last_accepted_coordinates() const
	{
		return last_accepted_coordinates_;
	}

	Coordinates const &
	get_coordinates_with_min_z() const
	{
		return lowest_z_coordinates_;
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

