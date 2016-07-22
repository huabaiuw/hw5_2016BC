#include <iostream>
#include <ctime>
#include "MonteCarlo.cc"

int main(){

    srand(time(NULL)); 


    Coordinates test;
    double input_x;
    double input_y;

    std::cout << "Please enter a x: ";
    std::cin >> input_x; 

    std::cout << "Please enter a y: ";
    std::cin >> input_y;

    test.set_x(input_x);
    test.set_y(input_y);

    std::cout << "Please enter a inner cycle number: ";
    int inner;
    std::cin >> inner;
    
    std::cout << test.get_z()<<std::endl;

    Landscape landscape;
    
    MonteCarlo mc(test,0); 
    
    std::cout << mc.last_accepted_z()<<std::endl;
    std::cout << rand() << " " << rand()<< " " << rand() <<std::endl;

    float step_size = 1000;
    float temp = 1.0;
   
    for (int i=0; i < 10; i++) {
        // step_size = step_size/4.0;
        step_size = step_size/10;
        temp = temp/4;
        mc.set_temperature(temp);
        inner = inner/10;
    for (int j=0; j < inner; j++){
        std::cout << "========================== New Circle ================================="<<std::endl;
        double delta1 = (double)rand() / (double)RAND_MAX - 0.5;
        double delta2 = (double)rand() / (double)RAND_MAX - 0.5;
        // double x_slope = test.slope_x();
        // double y_slope = test.slope_y();
        double x_slope = 1.0;
        double y_slope = 1.0;

        test.modify_x(-x_slope*step_size*delta1);
        test.modify_y(-y_slope*step_size*delta2);
        std::cout << "Outter: "<<i<<" Inner: "<< j << ": "<<"x_changed: "<< -x_slope*step_size*delta1 << " y_changed: "<<-y_slope*step_size*delta2<<std::endl;
        std::cout << "Outter: "<<i<<" Inner: "<< j << "Current x: "<<test.get_x() << " Current y: " << test.get_y()<<std::endl;
        std::cout << "Outter: "<<i<<" Inner: "<< j << "before_boltzmann: "<<test.get_z()<<std::endl;
        mc.boltzmann(test); 
        std::cout << "Outter: "<<i<<" Inner: "<< j << "after_boltzmann: "<<test.get_z()<<std::endl;
        std::cout << "Outter: "<<i<<" Inner: "<< j << ": "<<mc.last_accepted_z()<<std::endl;
        std::cout << "Outter: "<<i<<" Inner: "<< j << "Current x: "<<test.get_x() << " Current y: " << test.get_y()<<std::endl;
    }
    }

    return 0;
}

