// In this exercise, you will gain more knowledge of "Simulated Annealing process" 
// and "Monte Carlo method", which are key tools in protein design using Rosetta.
//
// In the most generic Rosetta protocol, we start with a protein structure, called Pose;
// then, we move the structure in certain way (usually randomly perturbing the structure);
// we check the "score" of the new structure, compare it with the previous one, 
// and decide whether to accept the new structure or reject it. 
// Finally, a structure near the lowest score will be reached.
// 
// In this exercise, we will deal with a much simpler version of this process.
// For a function z = f(x, y), we will use simulated annealing process to find the (x, y), 
// which give the global minimum of z. 
// Start with an arbitrary point (x, y), we calculate z, and then pertube the (x, y) a litte bit,
// calculate and compare the new z with previous z, to decide whether to accept this new (x, y) or not.
// Finally, hopefuly, we can find the (x, y) giving the smallest z.
//
// In order to do this, we will create several Classes. 
// 1) Landscape
//    This is a class containing the function z = f(x, y);
// 2) Coordinates
//    This is the class, used to store the x, y, z coordinates.
// 3) Random
//    Since "Monte Carlo method" heavily relys on randomness, 
//    this is the class to generate uniformly distributed random numbers.
// 4) MonteCarlo
//    This is the class to decide whether to accept or reject pretubed (x, y).
//
// Through this exercise, we will be familiar with putting different pieces of codes together.
// Question: 
// What are the purposes of those identifiers "#ifndef xxx", "#define xxx", and "#endif", 
// such as, in "Uniform.cc", "#ifndef INCLUDED_Uniform_cc", "#define INCLUDED_Uniform_cc"?
// 

#include <iostream>
#include "MonteCarlo.cc"
#include "Uniform.cc"

int main(){

  // Declare a Coordinates Ojbect: xyz, and initial it with one of the three Landscape functions.
  // Current choices: "sum_squares", "ackley", "rastrigin"

  std::cout << "Please choose a landscape function (choices: sum_squares, ackley, and rastrigin): ";
  std::string function_name;
  std::cin >> function_name; 

  Coordinates xyz(function_name); 

  // set up the starting x (such as 30); 
  double input_x = 30;
  std::cout << "Please enter a x: ";
  std::cin >> input_x; 
  xyz.set_x(input_x);

  // set up the starting y (such as 30);
  double input_y = 30;
  std::cout << "Please enter a y: ";
  std::cin >> input_y;
  xyz.set_y(input_y);

  std::cout << "Please enter an outer cycle number: ";
  int outer = 10;
  std::cin >> outer;

  std::cout << "Please enter an inner cycle number: ";
  int inner = 1000;
  std::cin >> inner;
  
  std::cout << "The Starting point: X = "<<xyz.get_x()<<" Y = "<<xyz.get_y()<<std::endl;
  std::cout << "The starting Z value: "<<xyz.get_z()<<std::endl;

  // Declare and initial a MonteCarlo Ojbect: mc, 
  // we initial it with the starting Coordinates xyz, and temperature 0;
  // we will set the temperature before we use the Boltmann function.
  MonteCarlo mc(xyz,0); 

  // set up a uniform random number generator.
  Uniform uniform_RG;

  // You can play with this step scalar. 
  // This will directly related to the estimate distance between the starting point the global minimum
  std::cout << "Please enter an upper_step size: ";
  float large_step = 1000; 
  std::cin >> large_step;
  float small_step = 0.01;
  float step_size;

  std::cout << "Please enter an upper_temperature: ";
  float high_temp = 0.1;
  std::cin >> high_temp;
  float low_temp = 0.00001;
  float temperature;

  //////// This is the outer cycle for simulated annealing process ///////////
  // useful webpages: https://en.wikipedia.org/wiki/Simulated_annealing
  // https://www.rosettacommons.org/docs/latest/scripting_documentation/RosettaScripts/Movers/movers_pages/GenericSimulatedAnnealerMover
  for (int i=0; i < outer; i++) {

    //// What is the purpose   
    temperature = (high_temp - low_temp)*std::exp(-i)+low_temp; 
    mc.set_temperature(temperature);
    
    step_size = (large_step - small_step)*std::exp(-i)+small_step;

    for (int j=0; j < inner; j++){
      std::cout << "=========================="<< "Outer cycle #: "<<i+1<<" Inner cycle #: "<< j+1 <<"====================="<<std::endl;

      double delta1 = uniform_RG.getRandom() - 0.5;
      double delta2 = uniform_RG.getRandom() - 0.5;
      std::cout << "Previous X: "<< xyz.get_x() << " Previous Y: "<< xyz.get_y()<<" Previous Z: "<< xyz.get_z()<<std::endl;

      xyz.modify_x(step_size*delta1);
      xyz.modify_y(step_size*delta2);

      std::cout << "X changed: "<< step_size*delta1 << " Y changed: "<< step_size*delta2<<std::endl;
      std::cout << "New X: "<<xyz.get_x() << " New Y: " << xyz.get_y()<<" New Z: "<<xyz.get_z()<<std::endl;
      bool whether_to_accept = mc.boltzmann(xyz); 
      std::cout << "Accept? " << whether_to_accept << std::endl;
      std::cout << "Saved X: "<<xyz.get_x() << " Saved Y: " << xyz.get_y()<<std::endl;
      std::cout << "After_boltzmann Z: "<<xyz.get_z()<<std::endl;
    }

      std::cout << "Final X: "<<xyz.get_x() << " Final Y: " << xyz.get_y()<<std::endl;
      std::cout << "Final Z: "<<xyz.get_z()<<std::endl;
  }
  return 0;
}
