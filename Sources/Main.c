/** @file Main.c
 * Program initialization and main loop.
 * @author Adrien RICCIARDI
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
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
	
	return EXIT_SUCCESS;
}
