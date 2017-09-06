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
 * @return -1 if an error happened.
 */
int ViewportInitialize(SDL_Surface *Pointer_Surface_Image);

/** Display the image by taking into account zoom and other transformations. */
void ViewportDrawImage(void);

#endif
