/** @file Configuration.h
 * Gather all program configurable parameters.
 * @author Adrien RICCIARDI
 */
#ifndef H_CONFIGURATION_H
#define H_CONFIGURATION_H

//-------------------------------------------------------------------------------------------------
// Constants
//-------------------------------------------------------------------------------------------------
/** The display refresh rate period in milliseconds (1 / 60Hz ~= 16ms). 60 frames per second are fine for a video game, so they are more than enough for an image viewer. */
#define CONFIGURATION_DISPLAY_REFRESH_RATE_PERIOD 16

/** The maximum allowed zoom factor value. */
#define CONFIGURATION_VIEWPORT_MAXIMUM_ZOOM_FACTOR 256

/** Window minimum width in pixels. */
#define CONFIGURATION_VIEWPORT_MINIMUM_WINDOW_WIDTH 100
/** Window minimum height in pixels. */
#define CONFIGURATION_VIEWPORT_MINIMUM_WINDOW_HEIGHT 100

#endif
