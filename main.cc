// In this exercise, you will be working with classes and derived classes.
// Inheritance is an important concept in object-oriented design
// because it allows us to define one class in terms of another class.
// Conceptually, one class ought to derive from another class if it passes
// the "is a" test.  If you can say X is a Y, then X should derive from Y.
// For instance, a "Dog" is a "Mammal".  It would be appropriate to encode
// this relationship by by creating a "Dog" class as a derivative of
// the "Mammal" class.

// Here are a few references to get you started on this concept:

// For this exercise, we can think of a "triangle" and a "rectangle" as
// derivatives of the parent class "shape".

// Your mission, should you choose to accept it, will be to define two classes
// circle and triangle that will calculate the area of a circle and a triangle.
// This area will be stored in a private member variable defined in the
// parent class "shape", which will only be accessible by the base classe's get_area
// and set_area functions. You will test your new derived classes by creating
// instances of each in main() and printing their areas.

// Question (Answer here):
// Why does the whats_area() function in the rectangle class generate an error?

// For Homework 14, You should create a separate cc file that contains your base
// and derived classes. For this exercise, you should add a pure virtual function
// to the base class called "name", which returns a string giving the name for the
// class. You'll use this to make reporting the areas of your objects easier: you
// can construct a std::vector< shape * > and load up the individual instances
// (constructed using "new" and put into pointers) into this vector.  Then you can
// use a for loop to visit each shape and to output its name and its area.  The
// output should remain identical to that in hw13, but it should come from a for loop
// instead of from individual cout statements.

#include <iostream>
#include "MonteCarlo.cc"
#include "Uniform.cc"

int main(){

  // Declare a Coordinates Ojbect: xyz, and initial it with one of the three Landscape functions.
  // Currentchoices: "sum_squares", "ackley", "rastrigin"

  std::cout << "Please enter a function name (choices sum_squares, ackley, and rastrigin): ";
  std::string function_name;
  std::cin >> function_name; 

  Coordinates xyz(function_name); 

  // set up the starting x; 
  double input_x;
  std::cout << "Please enter a x: ";
  std::cin >> input_x; 
  xyz.set_x(input_x);

  // set up the starting y;
  double input_y;
  std::cout << "Please enter a y: ";
  std::cin >> input_y;
  xyz.set_y(input_y);


  std::cout << "Please enter an outer cycle number: ";
  int outer;
  std::cin >> outer;

  std::cout << "Please enter an inner cycle number: ";
  int inner;
  std::cin >> inner;
  
  std::cout << xyz.get_z()<<std::endl;


  // Declare and initial a MonteCarlo Ojbect: mc, 
  // we initial it with the starting Coordinates xyz, and temperature 0;
  // we will set the temperature before we use the Boltmann function.
  MonteCarlo mc(xyz,0); 

  // set up a uniform random number generator.
  Uniform uniform_RG;
  
  float large_step = 1000;
  float small_step = 0.01;
  float step_size;

  float high_temp = 0.1;
  float low_temp = 0.00001;
  float temperature;

  //////// This is the outer cycle for simulated annealing process ///////////
  // useful webpages: https://en.wikipedia.org/wiki/Simulated_annealing
  // https://www.rosettacommons.org/docs/latest/scripting_documentation/RosettaScripts/Movers/movers_pages/GenericSimulatedAnnealerMover
  for (int i=0; i < outer; i++) {
    temperature = (high_temp - low_temp)*std::exp(-i)+low_temp;
    mc.set_temperature(temperature);
    
    step_size = (large_step - small_step)*std::exp(-i)+small_step;

    for (int j=0; j < inner; j++){
      std::cout << "========================== New Circle ================================="<<std::endl;

      double delta1 = uniform_RG.getRandom() - 0.5;
      double delta2 = uniform_RG.getRandom() - 0.5;

      xyz.modify_x(step_size*delta1);
      xyz.modify_y(step_size*delta2);
      std::cout << "Outter: "<<i<<" Inner: "<< j << ": "<<"x_changed: "<< step_size*delta1 << " y_changed: "<< step_size*delta2<<std::endl;
      std::cout << "Outter: "<<i<<" Inner: "<< j << " Current x: "<<xyz.get_x() << " Current y: " << xyz.get_y()<<std::endl;
      std::cout << "Outter: "<<i<<" Inner: "<< j << " before_boltzmann: "<<xyz.get_z()<<std::endl;
      mc.boltzmann(xyz); 
      std::cout << "Outter: "<<i<<" Inner: "<< j << " after_boltzmann: "<<xyz.get_z()<<std::endl;
      std::cout << "Outter: "<<i<<" Inner: "<< j << ": "<<mc.last_accepted_z()<<std::endl;
      std::cout << "Outter: "<<i<<" Inner: "<< j << " Current x: "<<xyz.get_x() << " Current y: " << xyz.get_y()<<std::endl;
    }
  }
  return 0;
}
