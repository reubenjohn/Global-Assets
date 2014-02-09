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

class SDL_2D
{
public:
       SDL_Surface* scr;
       SDL_Event event;
       HWND hwnd;
       bool quit,windowed;
       SDL_2D(SDL_Surface* screen)
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
       ~SDL_2D()
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
       /**
        * changes the color of the pixel at (x,y) of the SDL_Surface that is passed using the color that is passed
        */
       void put_pixel(int x, int y, SDL_Color color)
       {
           //Convert the pixels to 32 bit
           Uint32 *pixels = (Uint32 *)scr->pixels;
           Uint32 pixel=SDL_MapRGB(scr->format,255, 0, 0);
           //Set the pixel
           pixels[ ( y * scr->w ) + x ] = pixel;
       }
       /**
        * draws a line to the SDL_Surface that is passed from coordinates (x1,y1) to (x2,y2)
        * using the color that is passed int the SDL_Color variable
        * (by simply calls the put_pixel() many times)
        */
       void draw_line(float x1, float y1, float x2, float y2, const SDL_Color& color )
       {
       	if( SDL_MUSTLOCK( scr ) )
       	{
       		//Lock the surface
       		SDL_LockSurface( scr );
       	}
	   // Bresenham's line algorithm
	   const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	   if(steep)
	   {
		   std::swap(x1, y1);
		   std::swap(x2, y2);
	   }

	   if(x1 > x2)
	   {
		   std::swap(x1, x2);
		   std::swap(y1, y2);
	   }

	   const float dx = x2 - x1;
	   const float dy = fabs(y2 - y1);

	   float error = dx / 2.0f;
	   const int ystep = (y1 < y2) ? 1 : -1;
	   int y = (int)y1;

	   const int maxX = (int)x2;
	   for(int x=(int)x1; x<maxX; x++)
	   {
		   if(steep)
		   {
			put_pixel(y,x, color);
		   }
		   else
		   {
			put_pixel(x,y, color);
		   }

		   error -= dy;
		   if(error < 0)
		   {
			   y += ystep;
			   error += dx;
		   }
	   }
	   if( SDL_MUSTLOCK( scr ) )
	   {
		   SDL_UnlockSurface( scr );
	   }
   }
};

class SDL_3D:public SDL_2D
{
public:
	vect world_dim,camera_pos;
	float aov;
	SDL_3D(SDL_Surface* screen):SDL_2D(screen)
	{
		change_AngleOfView();
		change_world_dimensions((vect){100,100,100});
		vect change_cameraPosition(world_dim/2);
	}
	vect change_world_dimensions(vect world_dimensions)
	{
		return world_dim=world_dimensions;
	}
	vect change_cameraPosition(vect camera_position)
	{
		return camera_pos=camera_position;
	}
	float change_AngleOfView(float AOV=M_PI/4)
	{
		return aov=AOV;
	}
	vect apparent_pos_of(vect pos)
	{
		vect relPos=(pos-camera_pos);
		return world_dim/2+(world_dim/2)*relPos/(relPos.z*tan(aov));
	}
	/**
	 * Similar to the Drawline() exept it accepts vect variables as coordinates instead of (float,float)
	 */
	void Draw_vect_Line(vect a,vect b,SDL_Color color)
	{
		vect appPos_a=apparent_pos_of(a),appPos_b=apparent_pos_of(b);
		if(
			appPos_a.x>scr->clip_rect.x+50
			&&appPos_b.x<scr->clip_rect.x+scr->clip_rect.w-50
			&&appPos_a.y>scr->clip_rect.y+50
			&&appPos_b.y<scr->clip_rect.y+scr->clip_rect.h-50
			)
			draw_line(appPos_a.x,appPos_a.y,appPos_b.x,appPos_b.y,color);
	}
};


#endif /* SDL_CLASS_H_ */
