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

/** The texture holding the loaded image. */
static SDL_Texture *Pointer_Viewport_Texture_Original_Image;

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
int ViewportInitialize(SDL_Surface *Pointer_Surface_Image)
{
	// Try to create the viewport window
	Pointer_Viewport_Window = SDL_CreateWindow("Image Viewer", 0, 0, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
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
	
	// Convert the image surface to a texture
	Pointer_Viewport_Texture_Original_Image = SDL_CreateTextureFromSurface(Pointer_Viewport_Window_Renderer, Pointer_Surface_Image);
	if (Pointer_Viewport_Texture_Original_Image == NULL)
	{
		printf("[%s:%d] Error : failed to convert the image surface to a texture (%s).\n", __FUNCTION__, __LINE__, SDL_GetError());
		return -1;
	}
	
	return 0;
}

void ViewportDrawImage(void)
{
	SDL_RenderCopyEx(Pointer_Viewport_Window_Renderer, Pointer_Viewport_Texture_Original_Image, NULL, NULL, 0, NULL, 0);
	SDL_RenderPresent(Pointer_Viewport_Window_Renderer);
}
