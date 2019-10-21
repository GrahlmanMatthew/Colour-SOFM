#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include "user-input.h"
#include "pixel.h"
#include "CImg/CImg.h"
using namespace std;
using namespace cimg_library;

// Compile: g++ main.cpp -o SOFM.exe pixel.h  user-input.h -I CImg/ -lgdi32 -Wl,--stack,100000000  

int main(){

    // Frequency to save a new image of the map 
    int imgOutputFreq = 100;
    int numImages = 2;

    //Gathering Dimensions of SOFM
    int map_width = get_integer_input("Width of SOFM", 50, 2000);
    int map_height = get_integer_input("Height of SOFM", 50, 2000);

    // Gathering Learning Parameters for the SOFM
    int num_epochs = get_integer_input("Number of Epochs", 1, 100000);
    float neighbourhood_radius = get_float_input("Neighbourhood Radius", 1, 150);
    float learning_rate = get_float_input("Learning Rate", 0, 1.0);

    // For timing execution
    clock_t start = clock();


    // rand init
    // Creates an array of size map_width by map_height with randomly initialized pixels whose RGB colour is respresented as a value between 0 and 1.    
    pixel map_arr[map_width][map_height];
    CImg<unsigned char> map_image(map_width, map_height, 1, 3, 0);  // For image representation of map_arr
    for (int i = 0; i < map_width; i++){
        for (int j = 0; j < map_height; j++){
            pixel new_pixel;
            map_arr[i][j] = new_pixel;
            map_arr[i][j].set_coordinates(i, j);  
            float rand_colour[] = {(int)(new_pixel.get_red() * 255), (int)(new_pixel.get_green() * 255), (int)(new_pixel.get_blue() * 255)};
            map_image.draw_point(i, j, rand_colour);
        }
    }

 /*   // Displays an image representation of the map_arr on a GUI.
    CImgDisplay displayer (map_image, "SOFM", 1);
    while (!displayer.is_closed()){
        displayer.wait();
    }
*/
    // Saves the training data for the SOFM.
    map_image.save_bmp("images/1.bmp");

    // Begins "Training" on the SOFM over num_epochs
    for(int this_epoch = 1; this_epoch <= num_epochs; this_epoch++){

        if(this_epoch % imgOutputFreq == 0){
            std::stringstream ss;
            ss << "images/" << numImages << ".bmp";
            std::string filename;
            ss >> filename;
            const char * c = filename.c_str();
            map_image.save_bmp(c);
            numImages++;
        }

        pixel rand_pixel;    // Generates randomly initialized pixel to train the SOFM on. 


        // find BMU
        // Finds the pixel in the map_arr that best matches the rand_pixel
        const float FLOAT_MAX = numeric_limits<float>::max();
        pixel BMU(0, 0, 0);
        float best_distance = FLOAT_MAX;
        for(int i = 0; i < map_width; i++){
            for (int j = 0; j < map_height; j++){
               if(rand_pixel.getDistance(map_arr[i][j]) < best_distance){
                   BMU = map_arr[i][j];
                   best_distance = rand_pixel.getDistance(map_arr[i][j]);
                   BMU.set_coordinates(i, j);
               }
            }
        }

        float a = pow(exp(1.0), (-1 * (((this_epoch-1)/(num_epochs)))));
        // Calculates the Learning Rate for this Epoch
        float epoch_lr = learning_rate * a;

        // Calculates the Neighbourhood Radius for this Epoch
        int epoch_nradius = ceil(neighbourhood_radius * a);
        if (epoch_nradius < 1){
            epoch_nradius = 1;
        }

        // Updates the BMU's RGB Values
        float epoch_red = (BMU.get_red() + epoch_lr * (rand_pixel.get_red() - BMU.get_red()));
        float epoch_green = (BMU.get_green() + epoch_lr * (rand_pixel.get_green() - BMU.get_green()));
        float epoch_blue = (BMU.get_blue() + epoch_lr * (rand_pixel.get_blue() - BMU.get_blue()));
        map_arr[BMU.get_x_coord()][BMU.get_y_coord()].set_RGB(epoch_red, epoch_green, epoch_blue);

        // Updates BMU's' Colour in Image
        float new_colour[] = {(epoch_red * 255), (epoch_green * 255), (epoch_blue * 255)};
        map_image.draw_point(BMU.get_x_coord(), BMU.get_y_coord(), new_colour);

        // Updates the BMU's Neighbour's
        for (int y = BMU.get_y_coord() - neighbourhood_radius; y < BMU.get_y_coord() + neighbourhood_radius; y++){
            for (int x = BMU.get_x_coord(); (x - BMU.get_x_coord()) * (x - BMU.get_x_coord()) + (y - BMU.get_y_coord()) * (y - BMU.get_y_coord()) <= neighbourhood_radius * neighbourhood_radius; x--){
                if(!((y == BMU.get_y_coord()) && (x == BMU.get_x_coord())) && (y < map_height) && (y >= 0) && (x < map_width) && (x >= 0)){
                    float neighbourhood_multiplier = pow(exp(1), -1 * (map_arr[x][y].getDistance(BMU) * map_arr[x][y].getDistance(BMU)) / (2 * epoch_nradius * epoch_nradius));
                    float updated_red = (map_arr[x][y].get_red() + neighbourhood_multiplier * epoch_lr * (BMU.get_red() - map_arr[x][y].get_red()));
                    float updated_green = (map_arr[x][y].get_green() + neighbourhood_multiplier * epoch_lr * (BMU.get_green() - map_arr[x][y].get_green()));
                    float updated_blue = (map_arr[x][y].get_blue() + neighbourhood_multiplier * epoch_lr * (BMU.get_blue() - map_arr[x][y].get_blue()));
                    map_arr[x][y].set_RGB(updated_red, updated_green, updated_blue);

                    // Updates BMU's' Colour in Image
                    float updated_colour[] = {(updated_red * 255), (updated_green * 255), (updated_blue * 255)};
                    map_image.draw_point(x, y, updated_colour);
                }            
            }
            for (int x = BMU.get_x_coord() + 1; (x - BMU.get_x_coord()) * (x - BMU.get_x_coord()) + (y - BMU.get_y_coord()) * (y - BMU.get_y_coord()) <= neighbourhood_radius * neighbourhood_radius; x++){    
                if(!((y == BMU.get_y_coord()) && (x == BMU.get_x_coord())) && (y < map_height) && (y >= 0) && (x < map_width) && (x >= 0)){
                    float neighbourhood_multiplier = pow(exp(1), -1 * ((map_arr[x][y].getDistance(BMU) * map_arr[x][y].getDistance(BMU)) / (2 * epoch_nradius * epoch_nradius)));
                    float updated_red = (map_arr[x][y].get_red() + neighbourhood_multiplier * epoch_lr * (BMU.get_red() - map_arr[x][y].get_red()));
                    float updated_green = (map_arr[x][y].get_green() + neighbourhood_multiplier * epoch_lr * (BMU.get_green() - map_arr[x][y].get_green()));
                    float updated_blue = (map_arr[x][y].get_blue() + neighbourhood_multiplier * epoch_lr * (BMU.get_blue() - map_arr[x][y].get_blue()));
                    map_arr[x][y].set_RGB(updated_red, updated_green, updated_blue);

                    // Updates BMU's' Colour in Image
                    float updated_colour[] = {(updated_red * 255), (updated_green * 255), (updated_blue * 255)};
                    map_image.draw_point(x, y, updated_colour);
                }
            }
        }

    }

    // Saves the training data for the SOFM.
    std::stringstream ss;
    ss << "images/" << numImages << ".bmp";
    std::string filename;
    ss >> filename;
    const char * c = filename.c_str();
    map_image.save_bmp(c);
    cout << "Output Saved!" << endl;
    double duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    std::cout<<"Execution time: "<< duration <<'\n';
    std::system("ffmpeg -f image2 -framerate 10 -i images/%d.bmp out.gif");
    return 0;
}