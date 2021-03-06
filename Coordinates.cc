/// This Coordinates class contains three double numbers, x_, y_, z_,
/// which are used to describe the coordinates of a point in 3-D dimension. 
/// Users can set and modify x_ and y_, and calculate z_, according certain Function.
/// In this exercise, we are only dealing with three functions

#include <iostream>
#include <stdexcept>
#include "Landscape.cc"

class Coordinates {

public:
    void update_z(); // Because we need to use this function before the constructor, 
                     // we put declare it here.
                     //
    // constructor for Coordinates
    Coordinates():
    x_(1.0),
    y_(1.0),
    landscape_function_(NULL)
    {
        update_z();
    } 

    // constructor with input Landscape function name,
    // currently, only there choices: "sum_squares", "ackley", and "rastrigin"
    Coordinates(std::string fxn):
    x_(1.0),
    y_(1.0),
    landscape_function_(fxn)
    {
        update_z();
    } 

    // copy constructor
    Coordinates(Coordinates & src)
    {
        x_ = src.x_;
        y_ = src.y_;
        z_ = src.z_;
        landscape_function_ = src.landscape_function_;
    } 

    ~Coordinates(){}


    // getters and setters
    // the modify functions are important
    double get_x() {return x_;}
    void modify_x(double delta){x_ += delta; update_z();}
    void set_x(double x){x_ = x; update_z();}

    double get_y() {return y_;}
    void modify_y(double delta){y_ += delta; update_z();}
    void set_y(double y){y_ = y; update_z();}

    // get the z value
    // we are not providing setter z, because z value is calculated by using update_z() function;
    double get_z() {return z_;}

    // we are also store the information of the landscape function, which we are using to calculate z.
    std::string get_landscape_function() {return landscape_function_; }
    void set_landscape_function(std::string new_function) {landscape_function_= new_function; update_z(); }

private:
    double x_;
    double y_;
    double z_;
    std::string landscape_function_;
};

void Coordinates::update_z() {
   
         // create a pointer of the parent class Landscape

         Landscape * landscape = NULL; 
         if (landscape_function_ == "sum_squares") { landscape = new SumSquares(x_, y_);}
         else if (landscape_function_ == "rastrigin") { landscape = new Rastrigin(x_, y_);}
         else if (landscape_function_ == "ackley") { landscape = new Ackley(x_, y_);}
         else if (landscape_function_ == "booth") { landscape = new Booth(x_, y_);}
         else{ 
           delete landscape; 
           throw std::invalid_argument( "This function hasn't been defined!" );
         }


         /// please find the correct function in Landscape.cc, and update the z value 
         /// z_=landscape->get_z();
         z_=landscape->get_z();

         // Question: what is the purpose of "delete"? Is this necessary? Once we got the z value, we release the memory.
         delete landscape;
}

