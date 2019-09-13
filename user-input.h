#include <iostream>
#include <limits>
#include <string>
using namespace std;

/*  Purpose: returns the value inputted by the user as an integer only if the value is between the lower and upper bounds (inclusive).
    Parameters:
        @input_name: a string which represents the name of the input value to be collected.
        @lower_bound: an integer which represents the lower bound of the input value.
        @upper_bound: an integer which represents the upper bound of the input value.   
*/
int get_integer_input(string input_name, int lower_bound, int upper_bound){
    const int INT_MAX = numeric_limits<int>::max();
    int value = INT_MAX;
    while(value == INT_MAX){
        cout << "Enter " << input_name << " (as an integer between " << lower_bound << "-" << upper_bound << "): ";
        cin >> value;
        value = ((value >= lower_bound && value <= upper_bound) ? value : INT_MAX);
    }
    return value;
}

/*  Purpose: returns the value inputted by the user as an float only if the value is between the lower and upper bounds (inclusive).
    Parameters:
        @input_name: a string which represents the name of the input value to be collected.
        @lower_bound: an float which represents the lower bound of the input value.
        @upper_bound: an float which represents the upper bound of the input value.   
*/
float get_float_input(string input_name, float lower_bound, float upper_bound){
    const float FLOAT_MAX = numeric_limits<float>::max();
    float value = FLOAT_MAX;
    while(value == FLOAT_MAX){
        cout << "Enter " << input_name << " (as an float between " << lower_bound << "-" << upper_bound << "): ";
        cin >> value;
        value = ((value >= lower_bound && value <= upper_bound) ? value : FLOAT_MAX);
    }
    return value;
}