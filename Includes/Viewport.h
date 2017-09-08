/** @file Viewport.h
 * Display the image in a window and handle all graphic functions (like zooming or flipping).
 * @author Adrien RICCIARDI
 */
#ifndef H_VIEWPORT_H
#define H_VIEWPORT_H

#include <SDL2/SDL.h>

//-------------------------------------------------------------------------------------------------
// Types
//-------------------------------------------------------------------------------------------------
/** All available flipping modes. */
typedef enum
{
	VIEWPORT_FLIPPING_MODE_ID_NORMAL, //!< Flipping is disabled.
	VIEWPORT_FLIPPING_MODE_ID_HORIZONTAL, //!< Horizontal flipping.
	VIEWPORT_FLIPPING_MODE_ID_VERTICAL, //!< Vertical flipping.
	VIEWPORT_FLIPPING_MODE_ID_HORIZONTAL_AND_VERTICAL, //!< Both horizontal and vertical flipping.
	VIEWPORT_FLIPPING_MODE_IDS_COUNT //!< How many flipping modes are available.
} TViewportFlippingModeID;

//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
/** Create the main SDL window and the renderer.
 * @param String_Window_Title The window title to display.
 * @param Pointer_Surface_Image The image to display.
 * @return 0 if the function succeeded,
 * @return -1 if an error occurred.
 */
int ViewportInitialize(char *String_Window_Title, SDL_Surface *Pointer_Surface_Image);

/** Display the image by taking into account zoom and other transformations. */
void ViewportDrawImage(void);

/** Add eventual additionnal borders to the original image to make sure its ratio is kept regardless of the viewport dimensions.
 * @param New_Viewport_Width The viewport width in pixels.
 * @param New_Viewport_Height The viewport height in pixels.
 */
void ViewportSetDimensions(int New_Viewport_Width, int New_Viewport_Height);

/** Zoom a specific area of the image.
 * @param Viewport_X The viewport horizontal coordinate to start viewing from.
 * @param Viewport_Y The viewport vertical coordinate to start viewing from.
 * @param Zoom_Factor The zoom level (1 stands for no zoom (the image is fully displayed)).
 */
void ViewportSetZoomedArea(int Viewport_X, int Y, int Zoom_Factor);

/** Set a specific flipping mode for the currently loaded image.
 * @param Flipping_Mode_ID The flipping mode to set.
 * @note Function does nothing if a non-existing flipping mode ID is provided.
 */
void ViewportSetFlippingMode(TViewportFlippingModeID Flipping_Mode_ID);

#endif
