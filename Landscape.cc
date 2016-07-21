#include <cmath>

class Landscape {

public:
    float get_z() {return z_;}

protected:
    void set_z(float z){z_ = z;}

private:
    float z_;
};


class Rastrigin: public Landscape {
public:
    Rastrigin( double x, double y) {
        x_ = x; 
        y_ = y;
        set_z(calculate_z());
    }

    double calculate_z() {
        double pi = M_PI;
        return 20+2*x_+2*y_-10*(cos(2*pi*x_)+cos(2*pi*y_));
    }
private:
    double x_;
    double y_;
};


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
