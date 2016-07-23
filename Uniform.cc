#ifndef INCLUDED_Uniform_cc
#define INCLUDED_Uniform_cc

// This is the class, we are using to generate uniform random numbers.
// please see the source codes in Rosetta/main/source/src/numeric/random/
// Bonus: Can you write a new random generator, which can generate gaussian random number 
// (normally distributed deviate with zero mean and unit variance) ?

#include <cstdlib>

class Uniform {
public:
  Uniform():
  seed_(0) // Clear, for consistent starting state
  {}
    
  ~Uniform() {}

  void setSeed(int const seed) { seed_ = seed; srand( seed_ ); }
  int getSeed() { return seed_; }


  double getRandom() { return (double)rand() / (double)RAND_MAX; }

private:
    int seed_;
}; 

#endif
