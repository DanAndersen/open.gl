#include <SDL.h>
#include <SDL_opengl.h>
#include "Common.h"

int main_SDL(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_Window* window = SDL_CreateWindow("OpenGL - SDL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	initOpenGLProgram();

	SDL_Event windowEvent;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				break;
			}

			if (windowEvent.type == SDL_KEYUP &&
				windowEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				break;
			}
		}

		drawTriangle();

		SDL_GL_SwapWindow(window);
	}


	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}