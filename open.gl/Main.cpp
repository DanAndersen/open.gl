#include "Main_SDL.h"
#include "Main_SFML.h"
#include "Main_GLFW.h"

int main(int argc, char *argv[])
{
	return main_GLFW();
	//return main_SDL(argc, argv);    
	//return main_SFML();
}