A simple image viewer that reads in the RGB pixels values of .ppm images. Written in C using SDL (Required). Supports resizing of the window

To install SDL: 


sudo apt install libsdl2-dev


To Compile the program:


gcc -Wall -Wextra -g -o iv view.c `sdl2-config --cflags --libs`


After compiling pipe an image into the viewer:


cat img.ppm | ./iv


if you are lacking on ppm images I included some in the Optional_imgs_for testing folder:) if you would like your own ppm images to test gimp allows for the exporting of images as ppm

<img width="1032" height="548" alt="Screenshot 2026-03-10 194443" src="https://github.com/user-attachments/assets/a6f5ab97-045f-4bc4-9f18-65c8529afa16" />


PPM files include format specifiers, a commented line, width, and height values, max color value, then binary for the pixels.
Image Viewer discards the specifier, discards the commented line, and parses width and height using sscanf. The max color value is also discarded as most modern files should have a value of 255.

SDL2 is used for the creation of the window and rendering. The code creates a window with the dimensions of the input image, and is marked as resizable. After the window's drawing surface is created, a second offscreen surface is created
for allowing for the resizing of the window. Sdl typically destroys and recreates a window surface when a window is resized, while the offscreen surface remains unaffected by that issue.

PPM binary pixels are just flat streams of red, blue, green, so a simple loop is enough to read each pixel, and convert them into SDL'S format. 



Image quality depends on the original image so make sure you are satisfied with the quality

<img width="1162" height="614" alt="Screenshot 2026-03-10 194906" src="https://github.com/user-attachments/assets/8a983fbf-12f3-4959-9ab7-e39153729ca3" />



After modifications (and fixing seg faults this image viewer can handle 4k images
<img width="1277" height="605" alt="Screenshot 2026-03-10 195029" src="https://github.com/user-attachments/assets/acc45475-befa-496f-8f77-b552ac737bc4" />




