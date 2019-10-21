#include <math.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

// Class Purpose: this class allows for the creation of pixels objects for the map to self-organize in the input-space.
class pixel {
 
 // Each pixel in the SOFM will have the red, green, and blue colour channels.
  private:  
    float red;
    float green;
    float blue;
    int x_coord;
    int y_coord;

  public:
    // Constructor: assigns the red, green, and blue channel values a random float between 0 and 1.
    pixel(){
        this->red = ((double) rand() / (RAND_MAX));
        this->green = ((double) rand() / (RAND_MAX));
        this->blue = ((double) rand() / (RAND_MAX));
    }

    //Constructor: creates a pixel object with colour channels set to supplied parameters.
    pixel(int r, int g, int b){
      this->red = r;
      this->green = g;
      this->blue = b;
    }

    /*  getDistance(): returns to Euclidean distance between this pixel's and pixel p's colour channels.
        Parameters:
          @p: a pixel object with initialized R,G,B colour channels.
    */
    float getDistance(pixel p){
        float diff_red = pow(this->get_red() - p.get_red(), 2);
        float diff_green = pow(this->get_green() - p.get_green(), 2);
        float diff_blue = pow(this->get_blue() - p.get_blue(), 2);
        float distance = sqrt(diff_red + diff_green + diff_blue);
        //cout << "distance: " << distance << " dR: " << diff_red << " dG: " << diff_green << " dB: " << diff_blue << endl;
        return distance;
    }

    // setRGB(): sets this pixel's colour channel values to the supplied parameters.
    void set_RGB(float new_red, float new_green, float new_blue){
      this->red = new_red;
      this->green = new_green;
      this->blue = new_blue;
    }

    // set_coordinates(): sets this pixel's coordinates in the SOFM based on the supplied parameters.
    void set_coordinates(int x, int y){
      this->x_coord = x;
      this->y_coord = y;
    }

    // get_red(): return's this pixel's red value.  
    float get_red(){ return this->red; }
    
    // get_green(): return's this pixel's green value.
    float get_green(){ return this->green; }

    // get_blue(): return's this pixel's blue value.
    float get_blue(){ return this->blue; }

    // get_x(): return's the x coord of this pixel
    int get_x_coord(){ return this->x_coord; }

    // get_y(): return's the y coord of this pixel
    int get_y_coord(){ return this->y_coord; }

    //  print_prixel(): output's this red, green, and blue values to the console.
    void print_pixel(){ cout << "R: " << this->red << " G: " << this->green << " B: " << this->blue << endl;};
};