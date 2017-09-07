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

/** Viewport width in pixels. */
static int Viewport_Width;
/** Viewport height in pixels. */
static int Viewport_Height;

/** Adjusted image width in pixels. */
static int Viewport_Adjusted_Image_Width;
/** Adjusted image height in pixels. */
static int Viewport_Adjusted_Image_Height;

/** The texture holding the loaded image. */
static SDL_Texture *Pointer_Viewport_Texture_Original_Image;
/** The texture holding the image adapted to the current viewport dimensions. */
static SDL_Texture *Pointer_Viewport_Texture_Adapted_Image = NULL;

/** The rectangle defining the area of the adjusted image to display to the viewport. */
static SDL_Rect Viewport_Rectangle_View;

//-------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------
/** Compute the adjusted image area to display according to the zoom factor.
 * @param Viewport_X The viewport horizontal coordinate to start viewing from.
 * @param Viewport_Y The viewport vertical coordinate to start viewing from.
 * @param Zoom_Factor The new zoom factor.
 */
static void ViewportComputeViewingArea(int Viewport_X, int Viewport_Y, int Zoom_Factor)
{
	int Rectangle_X = 0, Rectangle_Y = 0;
	static int Previous_Zoom_Level_Rectangle_X = 0, Previous_Zoom_Level_Rectangle_Y = 0, Previous_Zoom_Factor = 1;
	
	// Force the view rectangle to start from the viewport origin when there is no zooming
	if (Zoom_Factor == 1)
	{
		Rectangle_X = 0;
		Rectangle_Y = 0;
	}
	// Handle zooming in by adding to the preceding view rectangle origin the new mouse moves (scaled according to the new zoom factor)
	else if (Previous_Zoom_Factor < Zoom_Factor)
	{
		Rectangle_X = Previous_Zoom_Level_Rectangle_X + (((Viewport_X / Zoom_Factor) * Viewport_Adjusted_Image_Width) / Viewport_Width);
		Rectangle_Y = Previous_Zoom_Level_Rectangle_Y + (((Viewport_Y / Zoom_Factor) * Viewport_Adjusted_Image_Height) / Viewport_Height);
	}
	// Handle zooming out by subtracting to the preceding view rectangle origin the new mouse moves (scaled according to the previous zoom factor, which was greater than the current one and was the factor used to compute the zooming in)
	else if (Previous_Zoom_Factor > Zoom_Factor)
	{
		Rectangle_X = Previous_Zoom_Level_Rectangle_X - (((Viewport_X / Previous_Zoom_Factor) * Viewport_Adjusted_Image_Width) / Viewport_Width);
		Rectangle_Y = Previous_Zoom_Level_Rectangle_Y - (((Viewport_Y / Previous_Zoom_Factor) * Viewport_Adjusted_Image_Height) / Viewport_Height);
	}
	
	// Make sure no negative coordinates are generated
	if (Rectangle_X < 0) Rectangle_X = 0;
	if (Rectangle_Y < 0) Rectangle_Y = 0;
	
	// There is nothing to do when zooming to 1x because the for loop will immediately exit and x and y coordinates will be set to 0
	Viewport_Rectangle_View.x = Rectangle_X;
	Viewport_Rectangle_View.y = Rectangle_Y;
	
	// The smaller the rectangle is, the more the image will be zoomed
	Viewport_Rectangle_View.w = (Viewport_Adjusted_Image_Width / Zoom_Factor) - 1;
	Viewport_Rectangle_View.h = (Viewport_Adjusted_Image_Height / Zoom_Factor) - 1;
	
	Previous_Zoom_Level_Rectangle_X = Rectangle_X;
	Previous_Zoom_Level_Rectangle_Y = Rectangle_Y;
	Previous_Zoom_Factor = Zoom_Factor;
}

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
	SDL_RenderCopyEx(Pointer_Viewport_Window_Renderer, Pointer_Viewport_Texture_Adapted_Image, &Viewport_Rectangle_View, NULL, 0, NULL, 0);
	SDL_RenderPresent(Pointer_Viewport_Window_Renderer);
}

int ViewportAdaptImage(int New_Viewport_Width, int New_Viewport_Height)
{
	unsigned int Pixel_Format;
	int Original_Image_Width, Original_Image_Height, Scaling_Percentage;
	SDL_Rect Rectangle_Original_Image_Dimension;
	
	// Get new viewport dimension
	Viewport_Width = New_Viewport_Width;
	Viewport_Height = New_Viewport_Height;
	
	// Get original image dimension (these values could be kept as global, but SDL_QueryTexture() is really fast)
	if (SDL_QueryTexture(Pointer_Viewport_Texture_Original_Image, &Pixel_Format, NULL, &Original_Image_Width, &Original_Image_Height) != 0)
	{
		printf("[%s:%d] Error : failed to query original image texture parameters (%s).\n", __FUNCTION__, __LINE__, SDL_GetError());
		return -1;
	}
		
	// Adjust image size to viewport ratio to make sure the image will keep its ratio
	// Image is smaller than the viewport, keep viewport size
	if ((Original_Image_Width < Viewport_Width) && (Original_Image_Height < Viewport_Height))
	{
		Viewport_Adjusted_Image_Width = Viewport_Width;
		Viewport_Adjusted_Image_Height = Viewport_Height;
	}
	// Image is bigger than the viewport, make the adapted image use the biggest original dimension and fill the other one to keep ratio
	else
	{
		// Fill the bottom part of the image if the image is larger than higher
		if (Original_Image_Width > Original_Image_Height)
		{
			Viewport_Adjusted_Image_Width = Original_Image_Width; // Keep the width
			
			// Compute an adjusted image height that is proportional to the viewport height (all computations are made with percentages to be easier to understand, and also because multiplying by 100 allows simple and fast fixed calculations with accurate enough results)
			Scaling_Percentage = (100 * Original_Image_Width) / Viewport_Width; // This is the percentage the viewport must be scaled to be as large as the original image, it will be used to determine the adjusted image height
			// Adjusted image height is the viewport height scaled by the percentage the viewport width was scaled, this way the image is proportionally adjusted to the viewport
			Viewport_Adjusted_Image_Height = (Viewport_Height * Scaling_Percentage) / 100;
		}
		// Original image height is greater or equal to image width
		else
		{
			Viewport_Adjusted_Image_Height = Original_Image_Height; // Keep the height
			
			// Compute an adjusted image width that is proportional to the viewport width (all computations are made with percentages to be easier to understand, and also because multiplying by 100 allows simple and fast fixed calculations with accurate enough results)
			Scaling_Percentage = (100 * Original_Image_Height) / Viewport_Height; // This is the percentage the viewport must be scaled to be as high as the original image, it will be used to determine the adjusted image width
			// Adjusted image width is the viewport width scaled by the percentage the viewport height was scaled, this way the image is proportionally adjusted to the viewport
			Viewport_Adjusted_Image_Width = (Viewport_Width * Scaling_Percentage) / 100;
		}
	}
	
	// Remove the previously existing texture
	if (Pointer_Viewport_Texture_Adapted_Image != NULL) SDL_DestroyTexture(Pointer_Viewport_Texture_Adapted_Image);
	
	// Create a texture with the right dimension to keep the image ratio
	Pointer_Viewport_Texture_Adapted_Image = SDL_CreateTexture(Pointer_Viewport_Window_Renderer, Pixel_Format, SDL_TEXTUREACCESS_TARGET, Viewport_Adjusted_Image_Width, Viewport_Adjusted_Image_Height);
	if (Pointer_Viewport_Texture_Adapted_Image == NULL)
	{
		printf("[%s:%d] Error : failed to create the adjusted image texture (%s).\n", __FUNCTION__, __LINE__, SDL_GetError());
		return -1;
	}
	
	// Fill the texture with a visible background color, so the original image dimension are easily visible
	if (SDL_SetRenderTarget(Pointer_Viewport_Window_Renderer, Pointer_Viewport_Texture_Adapted_Image) != 0)
	{
		printf("[%s:%d] Error : failed to target the renderer to the adjusted image texture (%s).\n", __FUNCTION__, __LINE__, SDL_GetError());
		return -1;
	}
	// Set a green background color
	if (SDL_SetRenderDrawColor(Pointer_Viewport_Window_Renderer, 0, 192, 0, 0) != 0)
	{
		printf("[%s:%d] Error : failed to set renderer drawing color (%s).\n", __FUNCTION__, __LINE__, SDL_GetError());
		return -1;
	}
	// Do the fill operation
	if (SDL_RenderClear(Pointer_Viewport_Window_Renderer) != 0)
	{
		printf("[%s:%d] Error : failed to fill the adjusted image texture with the background color (%s).\n", __FUNCTION__, __LINE__, SDL_GetError());
		return -1;
	}
	
	// Copy the original image on the adjusted image
	Rectangle_Original_Image_Dimension.x = 0;
	Rectangle_Original_Image_Dimension.y = 0;
	Rectangle_Original_Image_Dimension.w = Original_Image_Width - 1;
	Rectangle_Original_Image_Dimension.h = Original_Image_Height - 1;
	if (SDL_RenderCopy(Pointer_Viewport_Window_Renderer, Pointer_Viewport_Texture_Original_Image, NULL, &Rectangle_Original_Image_Dimension) != 0)
	{
		printf("[%s:%d] Error : failed to render the original image texture on the adapted image texture (%s).\n", __FUNCTION__, __LINE__, SDL_GetError());
		return -1;
	}
	
	// Restore the renderer (it can write to the display again)
	if (SDL_SetRenderTarget(Pointer_Viewport_Window_Renderer, NULL) != 0)
	{
		printf("[%s:%d] Error : failed to target the renderer to the display (%s).\n", __FUNCTION__, __LINE__, SDL_GetError());
		return -1;
	}
	
	// Reset zoom when resizing the window to avoid aiming to whatever but the right place
	ViewportComputeViewingArea(0, 0, 1);
	
	return 0;
}

void ViewportSetZoomFactor(int Zoom_Factor)
{
	int Mouse_X, Mouse_Y;
	
	// Start the rectangle at on-screen the mouse coordinates (zoom factor must be taken into account)
	SDL_GetMouseState(&Mouse_X, &Mouse_Y); // TODO put the mouse at the center of the zooming rectangle to make zooming more natural
	ViewportComputeViewingArea(Mouse_X, Mouse_Y, Zoom_Factor);
}
