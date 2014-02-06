/*
 * SDL_class.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Reuben
 */


#include <windows.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#include "vect.hpp"
#include "framer.hpp"
#include "graphic_string.hpp"

#ifndef SDL_CLASS_H_
#define SDL_CLASS_H_

class SDL
{
public:
       SDL_Surface* scr;
       SDL_Event event;
       HWND hwnd;
       bool quit,windowed;
       SDL(SDL_Surface* screen)
       {
               quit=false;
               windowed=true;
               hwnd=FindWindowA("ConsoleWindowClass",NULL);
               ShowWindow(hwnd,false);
               SDL_Init(SDL_INIT_EVERYTHING);
               SDL_EnableUNICODE(SDL_ENABLE);
               TTF_Init();
               Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
               Mix_Init(MIX_INIT_MP3);
               scr=screen;
       }
       ~SDL()
       {
               Mix_Quit();
               TTF_Quit();
               SDL_Quit();
       }
       void wait()
       {
               bool stop=false;
               while(SDL_PollEvent(&event));
               SDL_Event e;
               while(!quit&&!stop)
               {
                       if(SDL_WaitEvent(&e))
                       {
                               if(e.type==SDL_KEYDOWN)
                                       stop=true;
                               if(e.type==SDL_QUIT)
                                       quit=true;
                       }
               }
       }
       void pause(unsigned int pause_time)
       {
               timer T;
               T.start();
               while(SDL_PollEvent(&event));
               SDL_Event e;
               while(!quit&&T.elapse()<pause_time)
               {
                       if(SDL_PollEvent(&e))
                       {
                               if(e.type==SDL_QUIT)
                                       quit=true;
                       }
                       SDL_Delay(1);
               }
       }
       int poll_event()
       {
               return SDL_PollEvent(&event);
       }
       int wait_event()
       {
               return SDL_WaitEvent(&event);
       }
       void SDL_handle_events()
       {
               if(event.type==SDL_QUIT)
               {
                       quit=true;
               }
       }
       void update()
       {
               if(scr)
                       SDL_Flip(scr);
       }
       bool toggle_fullscreen(vect screen_dimensions)
       {
           if( windowed == true )
           {
               scr = SDL_SetVideoMode( screen_dimensions.x, screen_dimensions.y, screen_dimensions.z, SDL_SWSURFACE | SDL_FULLSCREEN);

               if(scr)
               {
                       return windowed = false;
               }
               else
               {
                       return false;
               }
           }
           else
           {
               scr = SDL_SetVideoMode( screen_dimensions.x, screen_dimensions.y , screen_dimensions.z, SDL_SWSURFACE | SDL_RESIZABLE);
               if(scr)
               {
                       return windowed = true;
               }
               else
               {
                       return false;
               }
           }
           return false;
       }
};

#endif /* SDL_CLASS_H_ */
