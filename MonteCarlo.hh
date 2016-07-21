// C++ headers
#include <map>
#include <string>
#include <Landscape.cc>

struct XY {
    double x_;
    double y_;
};

class MonteCarlo {
public:
	/// mc = MonteCarlo( coordinateXY , landscapeFunction , temp )
	
    MonteCarlo(
		XY const & xy_, 
        Landscape const & landscapeFunction,
		float const temp 
	);

	~MonteCarlo();

	void
	set_temperature( float const temp );

    float	
	temperature() const {
		return temperature_;
	}

	bool
	boltzmann(
		XY & xy,
		core::Real const proposal_density_ratio = 1,
		core::Real const inner_score_delta_over_temperature = 0
	);

	bool
	boltzmann(
		core::Real score,
		core::Real const proposal_density_ratio = 1,
		core::Real const inner_score_delta_over_temperature = 0,
		bool check_lowest_score = true
	);

	void
	reset( XY const & xy );

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

	/// @brief Compares score of <pose> to the lowest score found.
	/// If lower, sets the current lowest score pose and lowest score.
	/// Use internal pose energies if score_pose is false.
	/// Used to evaluate lowest score without boltzmann. Does not change pose structure.
	/// @note Does not update simulation statistics or last accepts by default.
	///
	/// example(s):
	///  mc.eval_lowest_score_pose( pose )
	/// See also:
	///  MonteCarlo
	///  MonteCarlo.lowest_score
	///  MonteCarlo.lowest_score_pose
	///  MonteCarlo.recover_low
	bool eval_lowest_score_pose(
		Pose & pose,
		bool score_pose = true,
		bool update_stats = false,
		std::string const & move_type = "unk"
	);


	/// @brief attach observer to last accepted conformation
	/// @tparam ConformationObserver any class implementing <tt> void attach_to( Conformation & ) </tt>
	template< typename ConformationObserver >
	void
	attach_observer_to_last_accepted_conformation( ConformationObserver & obs );


	/// @brief attach observer to lowest score conformation
	/// @tparam ConformationObserver any class implementing <tt> void attach_to( Conformation & ) </tt>
	template< typename ConformationObserver >
	void
	attach_observer_to_lowest_score_conformation( ConformationObserver & obs );


	/// @brief attach observer to last accepted pose
	/// @tparam PoseObserver any class implementing <tt> void attach_to( Pose & ) </tt>
	template< typename PoseObserver >
	void
	attach_observer_to_last_accepted_pose( PoseObserver & obs );


	/// @brief attach observer to lowest score pose
	/// @tparam PoseObserver any class implementing <tt> void attach_to( Pose & ) </tt>
	template< typename PoseObserver >
	void
	attach_observer_to_lowest_score_pose( PoseObserver & obs );


	/// @brief Sets the input  <pose>  and last accepted pose to
	/// the lowest score pose
	///
	/// example(s):
	///     mc.recover_low( pose )
	/// See also:
	///     MonteCarlo
	///     MonteCarlo.last_accept
	///     MonteCarlo.last_accepted_pose
	///     MonteCarlo.last_accepted_score
	///     MonteCarlo.lowest_score
	///     MonteCarlo.lowest_score_pose
	void
	recover_low( Pose & pose );


	/// @brief Sets the ScoreFunction to  <scorefxn> , re-scores
	/// last accepted pose and lowest score pose
	///
	/// example(s):
	///     mc.score_function( scorefxn )
	/// See also:
	///     MonteCarlo
	///     MonteCarlo.boltzmann
	///     MonteCarlo.set_temperature
	///     MonteCarlo.temperature
	///     ScoreFunction
	///     create_score_function
	virtual
	void
	score_function( ScoreFunction const & scorefxn ); // ScoreFunctionCOP scorefxn )


	/// @brief Returns the MonteCarlo ScoreFunction
	///
	/// example(s):
	///     mc.score_function()
	///     mc.score_function()( pose )
	/// See also:
	///     MonteCarlo
	///     MonteCarlo.boltzmann
	///     MonteCarlo.set_temperature
	///     MonteCarlo.temperature
	///     ScoreFunction
	///     create_score_function
	ScoreFunction const & score_function() const;


	/// @brief Displays the last accepted score and the lowest score
	///
	/// example(s):
	///     mc.show_scores()
	/// Output as:
	///     protocols.moves.MonteCarlo: MonteCarlo:: last_accepted_score,lowest_score: X Y
	/// See also:
	///     MonteCarlo
	///     MonteCarlo.last_accepted_score
	///     MonteCarlo.lowest_score
	///     MonteCarlo.show_counters
	///     MonteCarlo.show_state
	void show_scores() const;

	void reset_counters();
	void show_counters() const;

	Size total_trials() const;

	Real last_accepted_z() const;
	Real lowest_z() const;
	void clear_z();// remove last_accepted and lowest_z

	void
	evaluate_convergence_checks( core::pose::Pose const& pose, bool reject, bool final );

public:
	Size
	check_frequency() const {
		return check_frequency_;
	}

private:
	/// @brief Latest accepted XY 
	XY last_accepted_xy_;

	/// @brief Lowest score pose encountered
	XY lowest_z_xy_;

	/// @brief Acceptance criterion temperature
	core::Real temperature_;

	/// @brief Internal scoring function
	Landscape landscape_function_;

	int last_accept_;
    
	int counter_;

	Real last_accepted_z_;
	Real lowest_z_;

	int check_frequency_;
};

