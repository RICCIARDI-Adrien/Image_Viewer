/** @file Viewport.c
 * @see Viewport.h for description.
 * @author Adrien RICCIARDI
 */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <Viewport.h>

//-------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------
/** The window to display to. */
static SDL_Window *Pointer_Viewport_Window;

/** The renderer able to display to the window. */
static SDL_Renderer *Pointer_Viewport_Window_Renderer;

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
int ViewportInitialize(int Window_X, int Window_Y, int Window_Width, int Window_Height)
{
	// Try to create the viewport window
	Pointer_Viewport_Window = SDL_CreateWindow("Image Viewer", Window_X, Window_Y, Window_Width, Window_Height, 0);
	if (Pointer_Viewport_Window == NULL)
	{
		printf("[%s:%d] Error : failed to create the SDL window (%s).\n", __FUNCTION__, __LINE__, SDL_GetError());
		return -1;
	}
	
	// Try to create an hardware-accelerated renderer to plug to the window
	Pointer_Viewport_Window_Renderer = SDL_CreateRenderer(Pointer_Viewport_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Pointer_Viewport_Window_Renderer == NULL)
	{
		printf("[%s:%d] Error : failed to create the SDL window renderer (%s).\n", __FUNCTION__, __LINE__, SDL_GetError());
		return -1;
	}
	
	return 0;
}
