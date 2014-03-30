#include <GL/glew.h>
#include <cstdio>

void initGLEW() 
{
	glewExperimental = GL_TRUE;	// necessary to force GLEW to use mdoern OpenGL method
	glewInit();

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);

	printf("%u\n", vertexBuffer);
}