/** @file Main.c
 * Program initialization and main loop.
 * @author Adrien RICCIARDI
 */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Viewport.h>

//-------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------
/** Display the program help to the terminal.
 * @param String_Program_Name The program name to display.
 */
static void MainDisplayProgramUsage(char *String_Program_Name)
{
	printf("Image Viewer (C) 2017 Adrien RICCIARDI.\n"
		"\n"
		"Usage : %s Image_File | --help\n"
		"Image_File is the file to open.\n"
		"--help displays this message.\n"
		"\n"
		"Control keys :\n"
		"  - Mouse wheel : zoom in/zoom out\n"
		"  - 'f' key : toggle image flipping (first press leads to horizontal flipping, second press vertical flipping, third press both horizontal and vertical flipping, fourth press disables flipping)\n"
		"  - 'q' key : exit program\n", String_Program_Name);
}

/** Automatically called on program exit, gracefully unintialize SDL. */
static void MainExit(void)
{
	SDL_Quit();
}

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	SDL_Event Event;
	
	// Check arguments
	if (argc != 2)
	{
		MainDisplayProgramUsage(argv[0]);
		return EXIT_FAILURE;
	}
	
	// Is help requested ?
	if (strcmp(argv[1], "--help") == 0)
	{
		MainDisplayProgramUsage(argv[0]);
		return EXIT_SUCCESS;
	}
	
	// SDL intialization
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Error : failed to initialize SDL (%s).\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	atexit(MainExit);
	
	// TODO try to load the image before creating the viewport
	
	// TODO when image is loaded, update window title with image name
	
	// Initialize modules (no need to display an error message if a module initialization fails because the module already did)
	if (ViewportInitialize(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480) != 0) return EXIT_FAILURE; // TODO set initial viewport size and window decorations according to parameters saved on previous program exit
	
	// Process incoming SDL events
	while (1)
	{
		while (SDL_PollEvent(&Event))
		{
			switch (Event.type)
			{
				case SDL_QUIT:
					return EXIT_SUCCESS;
				
				// Unhandled event, do nothing
				default:
					break;
			}
		}
	}
}
