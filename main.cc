#include <iostream>
#include "Landscape.cc"
#include "MonteCarlo.hh"


// struct XY {
//    double x_;
//    double y_;
//};
//


int main(){

    XY test;
    test.x_ = 4.5;
    test.y_ = 2.3;

    std::cout << "Please enter a x: ";
    std::cin >> test.x_;

    std::cout << "Please enter a y: ";
    std::cin >> test.y_;

    std::cout << "Please enter a temp: ";
    float temp;
    std::cin >> temp;

    Landscape landscape;
    MonteCarlo mc = MonteCarlo(test, landscape, temp); 
    
    return 0;
}

