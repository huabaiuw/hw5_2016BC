#ifndef INCLUDED_Uniform_cc
#define INCLUDED_Uniform_cc

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
