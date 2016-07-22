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

////////// 
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

/////////////
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

////////////////////
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
