//
//  main.cpp
//  sdl_tutorial
//
//  Created by Howard Tam on 10/22/16.
//  Copyright © 2016 Howard Tam. All rights reserved.
//

#include <SDL2/SDL.h>
#include <stdio.h>
//#include <string>
//
//using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 480;

// Start up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window * gWindow = NULL;

// The surface contained by the window
SDL_Surface * gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Surface * gXOut = NULL;

// Notice that these are pointers to SDL surfaces. The reason is that 1) we'll be dynamically allocating memory to load images and 2) it's better to reference an image by memory location.
// Also, always remember to initialize your pointers. We set them to NULL immediately when declaring them.

bool init() {
    // Initialization flag
    bool success = true;
    
    // Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if ( gWindow == NULL ) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }
    
    return success;
}

bool loadMedia() {
    // Loading success flag
    bool success = true;
    
    // Load splash image
    gXOut = SDL_LoadBMP( "03_event_driven_programming/x.bmp" );
    
    if ( gXOut == NULL ) {
        printf("Unable to load image %s! SDL_Error: %s\n", "03_event_driven_programming/x.bmp", SDL_GetError() );
        success = false;
    }
    
//  An important thing to note is that this piece of code assumes you have a directory called "02_getting_an_image_on_the_screen" that contains an image named "hello_world.bmp" in your working directory. The working directory is where your application thinks it is operating. Typically, your working directory is the directory where your executable is at but some programs like Visual Studio change the working directory to where the vcxproj file is located. So if your application can't find the image, make sure it is in the right place.
    
    return success;
}

void close() {
//  In our clean up code, we destroy the window and quit SDL like before but we also have to take care of the surface we loaded. We do this by freeing it with SDL_FreeSurface. Don't worry about the screen surface, SDL_DestroyWindow will take care of it.
//        
//  Make sure to get into the habit of having your pointers point to NULL when they're not pointing to anything.
    
    // Deallocate surface
    SDL_FreeSurface(gScreenSurface);
    gXOut = NULL;
    
    // Destroy window
    SDL_DestroyWindow(gWindow);
    
    // Quit SDL Subsystem
    SDL_Quit();
}

// This type of main() is required by SDL for cross-browser compatibility
int main (int argc, char* args[]) {
    
    // Start up SDL and create window
    
    if ( !init() ) {
        printf("Failed to initialize!\n");
    } else {
        // Load media
        if ( !loadMedia() ) {
            printf("Failed to load media!\n");
        } else {
            // Main loop flag
            bool quit = false;
            
            // Event handler
            SDL_Event e;
            
            // While application is running
            while (!quit) {
                // Handle events on queue
                while ( SDL_PollEvent( &e ) != 0 ) {
                    // User requests quit
                    if ( e.type == SDL_QUIT ) {
                        quit = true;
                    }
                }
                
//                SDL_PollEvent will keep taking events off the queue until it is empty. When the queue is empty, SDL_PollEvent will return 0. So what this piece of code does is keep polling events off the event queue until it's empty. If an event from the event queue is an SDL_QUIT event (which is the event when the user Xs out the window), we set the quit flag to true so we can exit the application.
            }
            
            // Apply the image
            SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);
            
            //  What blitting does is take a source surface and stamps a copy of it onto the destination surface. The first argument of SDL_BlitSurface is the source image. The third argument is the destination. We'll worry about the 2nd and 4th arguments in future tutorials.
            
            // Update the surface
            SDL_UpdateWindowSurface(gWindow);
            
            //  After drawing everything on the screen that we want to show for this frame we have to update the screen using SDL_UpdateWindowSurface. See when you draw to the screen, you are not typically drawing to the image on the screen you see. By default, most rendering systems out there are double buffered. These two buffers are the front and back buffer.
            //
            //  When you make draw calls like SDL_BlitSurface, you render to the back buffer. What you see on the screen is the front buffer. The reason we do this is because most frames require drawing multiple objects to the screen. If we only had a front buffer, we would be able to see the frame as things are being drawn to it which means we would see unfinished frames. So what we do is draw everything to the back buffer first and once we're done we swap the back and front buffer so now the user can see the finished frame.
            //
            //  This also means that you don't call SDL_UpdateWindowSurface after every blit, only after all the blits for the current frame are done.
        }
    }
    
    // Free resources and close SDL
    close();
    
    return 0;
}
