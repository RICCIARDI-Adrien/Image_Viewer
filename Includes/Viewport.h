/** @file Viewport.h
 * Display the image in a window and handle all graphic functions (like zooming or flipping).
 * @author Adrien RICCIARDI
 */
#ifndef H_VIEWPORT_H
#define H_VIEWPORT_H

#include <SDL2/SDL.h>

//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
/** Create the main SDL window and the renderer.
 * @param Pointer_Surface_Image The image to display.
 * @return 0 if the function succeeded,
 * @return -1 if an error occurred.
 */
int ViewportInitialize(SDL_Surface *Pointer_Surface_Image);

/** Display the image by taking into account zoom and other transformations. */
void ViewportDrawImage(void);

/** Add eventual additionnal borders to the original image to make sure its ratio is kept regardless of the viewport dimension.
 * @param New_Viewport_Width The viewport width in pixels.
 * @param New_Viewport_Height The viewport height in pixels.
 * @return 0 if the function succeeded,
 * @return -1 if an error occurred.
 * @note Call this function when the window has been resized.
 */
int ViewportAdaptImage(int New_Viewport_Width, int New_Viewport_Height);

#endif
