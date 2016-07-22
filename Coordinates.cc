#include <iostream>
#include <Landscape.cc>

class Coordinates {

public:
    void update_z(); 

    Coordinates():
    x_(1.0),
    y_(1.0){
        update_z();
    } 

    ~Coordinates(){}

////// getter and setter
    double get_x() {return x_;}
    void set_x(double x){x_ = x; update_z();}

    double get_y() {return y_;}
    void set_y(double y){y_ = y; update_z();}

    double get_z() {return z_;}

private:
    double x_;
    double y_;
    double z_;
};

void Coordinates::update_z() {
        Rastrigin ras(x_, y_);
        z_ = ras.get_z();
}

int main() {
    Coordinates test;
    test.set_x(10);
    test.set_y(-3);
    std::cout << test.get_z() << std::endl;
    return 0;
}

