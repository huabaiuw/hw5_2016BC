#include <iostream>
#include "Landscape.cc"
#include "MonteCarlo.hh"


// struct XY {
//    double x_;
//    double y_;
//};
//


int main(){

    Coordinates test;
    double input_x;
    double input_y;

    std::cout << "Please enter a x: ";
    std::cin >> input_x; 

    std::cout << "Please enter a y: ";
    std::cin >> input_y;

    test.set_x(input_x);
    test.set_y(input_y);

    std::cout << "Please enter a temp: ";
    float temp;
    std::cin >> temp;

    Landscape landscape;
    MonteCarlo mc = MonteCarlo(test, temp); 
    
    return 0;
}

