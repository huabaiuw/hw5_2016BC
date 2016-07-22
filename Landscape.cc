#include <cmath>

class Landscape {

public:
    float get_z() {return z_;}

protected:
    void set_z(double z){z_ = z;}

private:
    double z_;
};

class Sphere: public Landscape {
public:
    Sphere( double x, double y) {
        x_ = x; 
        y_ = y;
        set_z(calculate_z());
    }

    double calculate_z() {
        return pow(x_,2)+pow(y_,2);
    }

    double slope_x() {
        return (pow(x_+0.0001, 2)-pow(x_-0.0001, 2))/0.0002;
    }

    double slope_y() {
        return (pow(y_+0.0001, 2)-pow(y_-0.0001, 2))/0.0002;
    }

private:
    double x_;
    double y_;
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
        return 20+pow(x_,2)+pow(y_,2)-10*(cos(2*pi*x_)+cos(2*pi*y_));
    }

    double slope_x() {
        double pi = M_PI;
        return ((pow(x_+0.0001, 2)-pow(x_-0.0001, 2))+10*(cos(2*pi*(x_-0.0001))-cos(2*pi*(x_+0.0001))))/0.0002;
    }

    double slope_y() {
        double pi = M_PI;
        return ((pow(y_+0.0001, 2)-pow(y_-0.0001, 2))+10*(cos(2*pi*(y_-0.0001))-cos(2*pi*(y_+0.0001))))/0.0002;
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
    
    double slope_x() {
        double pi = M_PI;
        return ((pow(x_+0.0001, 2)-pow(x_-0.0001, 2))+10*(cos(2*pi*(x_-0.0001))-cos(2*pi*(x_+0.0001))))/0.0002;
    }

    double slope_y() {
        double pi = M_PI;
        return ((pow(y_+0.0001, 2)-pow(y_-0.0001, 2))+10*(cos(2*pi*(y_-0.0001))-cos(2*pi*(y_+0.0001))))/0.0002;
    }
private:
    double x_;
    double y_;
};
