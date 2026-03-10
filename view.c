#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

int main()
{
    //assumes a ppm image...so some hardcoding like ignoring the second line which should be a comment

    FILE *in = stdin;
    char *ptemp = calloc(1000, sizeof(char));
    
    //read the first line (should be a ppm specifier like p3 or p6)
    fgets(ptemp, 1000, in);
    
    //read second line (comment)
    fgets(ptemp, 1000, in);

    //read third line(dimensions: width x height)
    char *pdimensions = calloc(1000, sizeof(char));
    fgets(pdimensions, 1000, in);

    //int *pwidth; //1821;
    //int *pheight; // 2034;

    //read fourth line(max color value - 255 on modern files - but ignore it)
    fgets(ptemp, 1000, in);
    free(ptemp);
  
    int width = -1;
    int height = -1;

    sscanf(pdimensions, "%d %d", &width, &height);
    free(pdimensions);

    printf("width = %d \nheight = %d\n", width, height);

    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
    //for future ref sdl destroys contents of a window when it is resized
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    //for resizing
    SDL_Surface *imageSurface = SDL_CreateRGBSurface(0, width, height, 32, 0,0,0,0);

//    Uint8 r, g, b;
//    r = 0xFF;
//    g = 0x00;
//    b = 0x00;
   
    //small optimization for initializing pixels at coordinate 0
    //avoids allocations every loop
    SDL_Rect pixel = (SDL_Rect){0, 0, 1, 1};
    Uint32 color = 0;

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            //loop over individual pixels and for each pixel read 3 characters from stdin
            //r,g,b make up each pixel
            Uint8 r, g, b;
            r = (char) getchar();
            g = (char) getchar();
            b = (char) getchar();
            color = SDL_MapRGB(psurface->format, r, g, b);

            //faster than making a new rectangle over and over
            pixel.y = y;
            pixel.x = x;
            
            //psurface was deleted each time the window was being resized
            SDL_FillRect(imageSurface, &pixel, color);
        }
    }

    SDL_UpdateWindowSurface(pwindow);

    int app_running = 1;
    while(app_running)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                app_running = 0;
            }
        }
        SDL_Surface *screen = SDL_GetWindowSurface(pwindow);
        SDL_BlitScaled(imageSurface, NULL, screen, NULL);
        SDL_UpdateWindowSurface(pwindow);

        SDL_Delay(100);
    }

    return 0;
}

// compile: gcc -Wall -Wextra -g -o iv view.c `sdl2-config --cflags --libs`
// `sdl2-config --cflags --libs`

//requires the data being piped into image viewer with: cat adven.ppm | ./iv