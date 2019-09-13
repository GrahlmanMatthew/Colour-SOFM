#include <iostream>
#include "user-input.h"
using namespace std;

int main(){

    // Gathering Dimensions of SOFM
    int map_width = get_integer_input("Width of SOFM", 50, 2000);
    int map_height = get_integer_input("Height of SOFM", 50, 2000);

    // Gathering Learning Parameters for the SOFM
    int num_epochs = get_integer_input("Number of Epochs", 1, 100000);
    int neighbourhood_radius = get_integer_input("Neighbourhood Radius", 1, 150);
    float learning_rate = get_float_input("Learning Rate", 0, 1.0);

    bool isCodingFun = false;

    if (!isCodingFun){
        cout << "Suffer bitch...";
    }
    else{
        cout << "Have Fun!";
    }

}



