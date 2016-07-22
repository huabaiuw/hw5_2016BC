#include <iostream>
#include "Landscape.cc"

class Coordinates {

public:
    void update_z(); 

    Coordinates():
    x_(1.0),
    y_(1.0){
        update_z();
    } 

    void clone(Coordinates & src)
    {
        x_ = src.x_;
        y_ = src.y_;
        z_ = src.z_;
    } 

    ~Coordinates(){}

////// getter and setter

    double get_x() {return x_;}
    void modify_x(double delta){x_ += delta; update_z();}
    void set_x(double x){x_ = x; update_z();}

    double get_y() {return y_;}
    void modify_y(double delta){y_ += delta; update_z();}
    void set_y(double y){y_ = y; update_z();}

    double get_z() {return z_;}

    double slope_x()
    {
        return x_slope;
    }

    double slope_y(){
        return y_slope;
    }

private:
    double x_;
    double y_;
    double z_;
    double x_slope;
    double y_slope;
};

void Coordinates::update_z() {
        // Rastrigin ras(x_, y_);
        // z_ = ras.get_z();
        // x_slope=ras.slope_x();
        // y_slope=sphere.slope_y();
        Ackley ackley(x_, y_);
        z_ = ackley.get_z();
        x_slope=ackley.slope_x();
        y_slope=ackley.slope_y();

        // Sphere sphere(x_, y_);
        // z_=sphere.get_z();
        // x_slope=sphere.slope_x();
        // y_slope=sphere.slope_y();
}

