/** @file Viewport.h
 * Display the image in a window and handle all graphic functions (like zooming or flipping).
 * @author Adrien RICCIARDI
 */
#ifndef H_VIEWPORT_H
#define H_VIEWPORT_H

//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
/** Create the main SDL window and the renderer.
 * @param Window_X X coordinate of the viewport window in pixels.
 * @param Window_Y Y coordinate of the viewport window in pixels.
 * @param Window_Width Viewport window width in pixels.
 * @param Window_Height Viewport window height in pixels.
 * @return 0 if the function succeeded,
 * @return -1 if an error happened.
 */
int ViewportInitialize(int Window_X, int Window_Y, int Window_Width, int Window_Height);

#endif
