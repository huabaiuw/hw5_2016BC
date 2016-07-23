#ifndef INCLUDED_Landscape_cc
#define INCLUDED_Landscape_cc

/// The class Landscape is the parent class for a set of 3-D landscape functions.
/// useful sites: http://www.sfu.ca/~ssurjano/ackley.html
//                http://www.sfu.ca/~ssurjano/rastr.html
//                http://www.sfu.ca/~ssurjano/sumsqu.html
//                https://en.wikipedia.org/wiki/Test_functions_for_optimization
#include <cmath>

class Landscape {
public:
    float get_z() {return z_;}

protected:
    void set_z(double z){z_ = z;}

private:
    double z_;
};

//////////  A derived class: SumSquares function
//////////  function: z = x^2 + y^2
//////////  the global minimum will be x = 0, y = 0, z = 0;
class SumSquares: public Landscape {
public:
    SumSquares( double x, double y) {
        x_ = x; 
        y_ = y;
        set_z(calculate_z());
    }
    double calculate_z() {
        return pow(x_,2)+pow(y_,2);
    }

private:
    double x_;
    double y_;
};

//////////  A derived class: Rastrigin function
//////////  function: z = 20 + (x-4)^2 + (y-5)^2 - 10( cos(2pi(x-4))+cos(2pi(y-5)) );
//////////  the global minimum will be x = 4, y = 5, z = 0;
class Rastrigin: public Landscape {
public:
    Rastrigin( double x, double y) {
        x_ = x; 
        y_ = y;
        set_z(calculate_z());
    }

    double calculate_z() {
        double pi = M_PI;
        return 20+pow((x_-4),2)+pow((y_-5),2)-10*(cos(2*pi*(x_-4))+cos(2*pi*(y_-5)));
    }

private:
    double x_;
    double y_;
};

//////////  A derived class: Ackley function
//////////  function: z =  -20*exp(-0.2*sqrt(0.5*(x^2+y^2)))-exp(0.5*(cos(2*pi*x)+cos(2*pi*y))) + e + 20;
//////////  the global minimum will be x = 0, y = 0, z = 0;
class Ackley: public Landscape {
public:
    Ackley( double x, double y) {
        x_= x;
        y_= y;
        set_z(calculate_z());
    }

    double calculate_z() {
        double pi = M_PI;
        double e = exp(1.0);
        return -20*exp(-0.2*sqrt(0.5*(pow(x_,2)+pow(y_,2))))-exp(0.5*(cos(2*pi*x_)+cos(2*pi*y_))) + e + 20;
    }
    
private:
    double x_;
    double y_;
};

class Booth: public Landscape {
public:
    Booth( double x, double y) {
        x_= x;
        y_= y;
        set_z(calculate_z());
    }

    double calculate_z() {
        return pow(x_ + 2*y_-7, 2) + pow(2*x_+y_-5, 2);
    }
    
private:
    double x_;
    double y_;
};
#endif
