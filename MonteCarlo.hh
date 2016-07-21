// C++ headers
#include <string>
#include <Landscape.cc>

struct XY {
    double x_;
    double y_;
};

class MonteCarlo {
public:
    MonteCarlo(
		XY const & xy_, 
        Landscape const & landscape,
		float const temperature
	)

	~MonteCarlo();

	void
	set_temperature( float const temp );

    float	
	get_temperature() const; 

	bool
	boltzmann(XY & xy);

// void
//	reset( XY const & xy );

	void
	set_last_accepted_pose(
		Pose const & pose
	);

	void
	set_last_accepted_xy(
		XY const& xy,
		double z 
	);

	void
	set_lowest_score_xy(
		XY const& xy,
        double z
	);

	XY const &
	last_accepted_xy() const
	{
		return *last_accepted_xy_;
	}

	XY const &
	lowest_score_xy() const
	{
		return *lowest_score_pose_;
	}

	void
	recover_low( XY & xy );

	/// @brief Sets the ScoreFunction to  <scorefxn> , re-scores
	/// last accepted pose and lowest score pose

	void
	set_landscape( Landscape const & landscape );

	/// @brief Returns the MonteCarlo ScoreFunction

	Landscape const & get_landscape() const;

	/// @brief Displays the last accepted score and the lowest score
	void show_scores() const;

	void reset_counters();
	void show_counters() const;

	Real last_accepted_z() const;
	Real lowest_z() const;
	void clear_z();// remove last_accepted and lowest_z

private:
    XY xy_;
	XY last_accepted_xy_;
	XY xy_with_lowest_z_;

    double z_;
    double last_accepted_z_;
    double lowest_z_;

	float temperature_;

	Landscape* landscape_function_;
};

