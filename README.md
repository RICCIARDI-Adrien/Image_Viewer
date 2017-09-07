# Image Viewer
Display a large amount of image formats to the screen with simple functions like zooming, flipping...  
Linux, macOS and Windows platforms are supported.  
Program is written in POSIX C and uses SDL2 for rendering.

## Usage
```
image-viewer <image file>
```
`<image file>` is the image file to load.  
  
Use `image-viewer --help` to display program usage and control keys.

## Building
On Debian/Ubuntu systems, you have to install some SDL2 packages.
```
sudo apt install libsdl2-dev libsdl2-image-dev
```
Then simply type `make` in the repository directory to build the program.
