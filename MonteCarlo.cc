#include <MonteCarlo.hh>

MonteCarlo::MonteCarlo(
	XY const & xy, 
	Landscape const & landscape, 
    float const temperature
):
    xy_(xy);
	temperature_( temperature ),
	last_accept_z_( 10000 ),
	lowest_z_( 10000 )
{
	last_accepted_pose_ = PoseOP( new Pose() );
	lowest_score_pose_ = PoseOP( new Pose() );
    landscape_function_ = new Landscape(landscape);
}

MonteCarlo::~MonteCarlo()
{
}


void MonteCarlo::clear_poses() {
	last_accepted_pose_ = PoseOP( new Pose() );
	lowest_score_pose_ = PoseOP( new Pose() );
}

void
MonteCarlo::reset_scorefxn(
	Pose const & init_pose,
	ScoreFunction const & scorefxn
){
	// score_function_ = new ScoreFunction(scorefxn);
	score_function_ = scorefxn.clone();
	reset(init_pose);
}

void
MonteCarlo::set_temperature( float const temp )
{
	temperature_ = temp;
}

float
MonteCarlo::get_temperature() const
{
	return temperature_;
}

/// return the simulation state to the lowest energy structure we've seen
void
MonteCarlo::recover_low( XY & xy )
{
	( pose ) = ( *lowest_score_pose_ );
	*last_accepted_pose_ = *lowest_score_pose_ ;
	last_accepted_score_ = last_accepted_xy_->;
}

/////////////////////////////////////////////////////////////////////////////

void
MonteCarlo::show_current_lowest_z() const
{
	    std:cout << "MonteCarlo:: current_lowest_z: " << lowest_z() << std::endl;
}

bool
MonteCarlo::boltzmann(
	XY & xy,
	std::string const & move_type, // = unk
	core::Real const proposal_density_ratio, // = 1
	core::Real const inner_score_delta_over_temperature // = 0
)
{
	// score the pose:
	Real const score( (*score_function_)( xy ) );
	//now delegate decision making...
	bool const accept( boltzmann( score, move_type, proposal_density_ratio, inner_score_delta_over_temperature ) );

	//rejected ?
	if ( !accept ) {
		evaluate_convergence_checks( pose, true /*reject*/, false /* not final*/ );
		xy = ( last_accepted_xy_ );
		return false; // rejected
	}

	//accepted !
	PROF_START( basic::MC_ACCEPT );
	*last_accepted_pose_ = pose;

	// print out the scores for each decoy to cmd out, if you pass a flag
	// nice for testing
	if ( basic::options::option[ basic::options::OptionKeys::mc::log_scores_in_MC ].user() && basic::options::option[ basic::options::OptionKeys::mc::log_scores_in_MC ]() == true ) {
		score_function_->show( pose );
	}

#ifdef BOINC_GRAPHICS
	if ( update_boinc_ ) {
		boinc::Boinc::update_graphics_last_accepted( pose, last_accepted_score() );
	}
#endif

	if ( mc_accepted_ == MCA_accepted_score_beat_low ) {
		*lowest_score_pose_ = pose;
		evaluate_convergence_checks( pose, false /*not reject*/, false /*not final*/ );

#ifdef BOINC_GRAPHICS
		if ( update_boinc_ ) {
			boinc::Boinc::update_graphics_low_energy( pose, lowest_score() );
		}
#endif

	} //MCA_accepted_score_beat_low

	PROF_STOP( basic::MC_ACCEPT );
	return true; // accept!
}

//////////////////////////////////////////////////////////
// See notes above on boltzmann()
//////////////////////////////////////////////////////////
bool
MonteCarlo::boltzmann(
	core::Real score,
	std::string const & move_type, // = "unk"
	core::Real const proposal_density_ratio, // = 1
	core::Real const inner_score_delta_over_temperature, // = 0
	bool check_lowest_score //=true
)
{
	// figure out the actual score
	total_score_of_last_considered_pose_ = score; // save this for the TrialMover so that it may keep statistics.
	counter_->count_trial( move_type );

#ifdef BOINC_GRAPHICS
	if ( update_boinc_ ) {
		boinc::Boinc::update_mc_trial_info( counter_->trial( move_type ), move_type );
	}
#endif

	Real const score_delta( score - last_accepted_score_ );
	Real const boltz_factor =  ( -score_delta / temperature_ ) + inner_score_delta_over_temperature;
	Real const probability = std::exp( std::min (40.0, std::max(-40.0,boltz_factor)) ) * proposal_density_ratio;
	if ( probability < 1 ) {
		if ( numeric::random::rg().uniform() >= probability ) {
			mc_accepted_ = MCA_rejected; // rejected
			autotemp_reject();
			return false; // rejected
		}
		mc_accepted_ = MCA_accepted_thermally; // accepted thermally
	} else {
		mc_accepted_ = MCA_accepted_score_beat_last; // energy is lower than last_accepted
	}

	counter_->count_accepted( move_type );
	counter_->count_energy_drop( move_type, score_delta );
	last_accepted_score_ = score;

	autotemp_accept();

	if ( check_lowest_score && score < lowest_score() ) {
		lowest_score_ = score;
		mc_accepted_ = MCA_accepted_score_beat_low; //3;
	}
	return true; // accept!
}


void
MonteCarlo::reset( Pose const & pose )
{
	PROF_START( basic::MC_ACCEPT );
	*last_accepted_pose_ = pose;
	PROF_STOP( basic::MC_ACCEPT );

	Real const score( (*score_function_)( *last_accepted_pose_ ) );
	/// Now handled automatically.  score_function_->accumulate_residue_total_energies( *last_accepted_pose_ );

	PROF_START( basic::MC_ACCEPT );
	*lowest_score_pose_ = *last_accepted_pose_;
	PROF_STOP( basic::MC_ACCEPT );

	last_accepted_score_ = score;
	lowest_score_ = score;
}

/////////////////////////////////////////////////////////////////////////////
void
MonteCarlo::set_autotemp(
	bool const setting,
	Real const quench_temp
)
{
	autotemp_ = setting;
	quench_temp_ = quench_temp;
	last_accept_ = 0;
}

void
MonteCarlo::set_last_accepted_pose( Pose const & pose )
{
	*last_accepted_pose_ = pose;
	last_accepted_score_ = last_accepted_pose_->energies().total_energy();
}

void MonteCarlo::set_last_accepted_pose( core::pose::Pose const& pose, core::Real score ) {
	*last_accepted_pose_ = pose;
	last_accepted_score_ = score;
}

void MonteCarlo::set_lowest_score_pose( core::pose::Pose const& pose ) {
	*lowest_score_pose_ = pose;
	lowest_score_ = pose.energies().total_energy();
}

void MonteCarlo::set_lowest_score_pose( core::pose::Pose const& pose, core::Real score ) {
	*lowest_score_pose_ = pose;
	lowest_score_ = score;
}

bool
MonteCarlo::eval_lowest_score_pose(
	Pose & pose,
	bool score_pose, // true
	bool update_stats, //false
	std::string const & move_type //unk
)
{
	//Get or calculate energy
	Real score;
	if ( score_pose ) {
		score = (*score_function_)(pose);
	} else {
		score =  pose.energies().total_energy();
	}

	//Evaluate
	total_score_of_last_considered_pose_ = score; // save this for the TrialMover so that it may keep statistics.
	if ( score < lowest_score() ) {
		*lowest_score_pose_ = pose;
		lowest_score_ = score;
		if ( update_stats ) {
			counter_->count_accepted( move_type );
			counter_->count_energy_drop( move_type, score - last_accepted_score() );
			last_accepted_score_ = score;
			mc_accepted_ = MCA_accepted_score_beat_low;
			*last_accepted_pose_ = pose;
			evaluate_convergence_checks( pose, false /*not reject*/, false /*not final*/ );
		}

		return true;
	} else {
		if ( update_stats ) {
			mc_accepted_ = MCA_rejected; // rejected
		}
		return false;
	}
}

core::scoring::ScoreFunction const &
MonteCarlo::score_function() const
{
	return *score_function_;
}

Real
MonteCarlo::last_accepted_score() const
{
	//if (last_accepted_pose_->energies().total_energy() != last_accepted_score_) {
	// TR << "Last: " << last_accepted_pose_->energies().total_energy() << " != " << last_accepted_score_ << " diff " << last_accepted_pose_->energies().total_energy() - last_accepted_score_ << std::endl;
	//}
	//return last_accepted_pose_->energies().total_energy();
	return last_accepted_score_;
}


Real
MonteCarlo::lowest_score() const
{
	//if (lowest_score_pose_->energies().total_energy() != lowest_score_) {
	// TR << "Low: " << lowest_score_pose_->energies().total_energy() << " != " << lowest_score_ << " diff " << lowest_score_pose_->energies().total_energy() - lowest_score_ << std::endl;
	//}
	//return lowest_score_pose_->energies().total_energy();
	return lowest_score_;
}


MCA
MonteCarlo::mc_accepted() const
{
	return mc_accepted_;
}

std::string
MonteCarlo::mc_accepted_string() const
{
	return to_string( mc_accepted_ );
}


/////////////////////////////////////////////////////////////////////////////
// replicate logic from monte_carlo.cc
//
// should probably make these parameters ( 150, 1.0 )
void
MonteCarlo::autotemp_reject()
{
	// int const heat_after_cycles( 150 );
	Real const heat_delta( quench_temp_ * 0.5 );
	Real const max_temperature( quench_temp_ * 10.0 );

	if ( !autotemp_ ) return;
	if ( last_accept_ >= (int) heat_after_cycles_ ) {
		//if ( temperature_ > max_temperature * 0.25 )
		TR << "autotemp_reject -- heat: " << last_accept_<< ' ' << temperature_  << std::endl;
		last_accept_ = -1;
		set_temperature( std::min( temperature_ + heat_delta, max_temperature ) );
	}
	++last_accept_;
}

/////////////////////////////////////////////////////////////////////////////
// replicate logic from monte_carlo.cc
void
MonteCarlo::autotemp_accept()
{
	if ( !autotemp_ ) return;
	if ( temperature_ != quench_temp_ ) {
		set_temperature( quench_temp_ );
		TR << "autotemp_accept: reset temperature_ = " << temperature_ << std::endl;
	}

	last_accept_ = 0;
}

void
MonteCarlo::evaluate_convergence_checks( core::pose::Pose const& pose, bool reject, bool /*final*/ ) {
	if ( !reject || numeric::mod( last_check_++, check_frequency_ ) == 0 ) {
		for ( utility::vector1< moves::MonteCarloExceptionConvergeOP >::iterator it = convergence_checks_.begin(); it != convergence_checks_.end(); ++it ) {
			(**it)( pose, *this, reject );
		}
	}
}

void
MonteCarlo::push_back( moves::MonteCarloExceptionConvergeOP check ) {
	convergence_checks_.push_back( check );
}

// for Python bindings
std::ostream & operator << ( std::ostream & os, MonteCarlo const & mc)
{
	os << "protocols.moves.MonteCarlo:\n";
	os << "\"Temperature\" (kT): " << mc.temperature() << "\n";
	os << "Total Trials: " << mc.total_trials() << "\n";
	os << "Lowest Score: " << mc.lowest_score() << "\n";
	os << "Last Accepted Score: " << mc.last_accepted_score() << "\n";
	os << "last_accept = " << mc.lowest_score() << std::endl;
	return os;
}

} // namespace moves
} // namespace core
