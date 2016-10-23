//
//  main.cpp
//  sdl_tutorial
//
//  Created by Howard Tam on 10/22/16.
//  Copyright © 2016 Howard Tam. All rights reserved.
//

#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 480;

// This type of main() is required by SDL for cross-browser compatibility
int main (int argc, char* args[]) {
    
    // The window we'll be rendering to
    SDL_Window *window = NULL;
    
    // The surface contained by the window
    SDL_Surface *screenSurface = NULL;
    
    // Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf("SDL could not initialize! SDL_Error: %s \n", SDL_GetError());
    } else {
        // Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if ( window == NULL ) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            // Get window surface
            screenSurface = SDL_GetWindowSurface( window );
            
            // Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF));
            
            // Update the surface
            SDL_UpdateWindowSurface( window );
            
            // Wait 2 seconds
            SDL_Delay( 5000 );
        }
    }
    
    // Destroy window
    SDL_DestroyWindow( window );
    
    // Quit SDL subsystems
    SDL_Quit();
    
    return 0;
}
