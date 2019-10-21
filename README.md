# Colour-SOFM
A self-organizing feature map which is trained on a random three-dimensional (RGB) input space.

# Compilation
To compile you will need to first install the [MinGW C++ compiler](https://www.rose-hulman.edu/class/csse/resources/MinGW/installation.htm). Once you have done so, simply run the following command from a Bash command line:

```bash
g++ main.cpp -o SOFM.exe pixel.h  user-input.h -I CImg/ -lgdi32 -Wl,--stack,100000000
```

# Learning Parameters
When executed, the program will prompt the user for:
* The height of the SOFM
* The width of the SOFM
* The number of epochs to train the SOFM over
* The neighbourhood radius for the SOFM update function
* The learning rate

# Input Space
The SOFM is trained on a three dimensional input space of pixels with randomized RGB values. Initially, the SOFM will look similar to the image below.

<p align="center">
  <img src="./SOFM.bmp" />
</p>

# Output
The output of the SOFM is saved to the "SOFM-TRAINED.bmp" file and will look similar to the following:

<p align="center">
  <img src="./SOFM-TRAINED.bmp" />
</p>
