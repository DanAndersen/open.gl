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

const char *vertexShaderSource = 
	"#version 150\n"
	"in vec2 position;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(position, 0.0, 1.0);\n"
	"}"
;

const char *fragmentShaderSource = 
	"#version 150\n"
	"out vec4 outColor;\n"
	"void main()\n"
	"{\n"
	"	outColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
	"}\n"
;

float vertices[] = {
	 0.0f,  0.5f, // Vertex 1 (X, Y)
     0.5f, -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f  // Vertex 3 (X, Y)
};

void compileShader(GLuint shaderProgram, GLuint shaderType, const char *shaderSource)
{
	printf("compiling shader...");
	// compiling shaders
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	GLint shaderCompileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompileStatus);

	if (shaderCompileStatus == GL_TRUE) {
		printf("shader compiled.\n");
	} else {
		printf("shader failed to compile.\n");
	}

	const unsigned int shaderInfoLogNumBytes = 512;

	char shaderInfoLogBuffer[shaderInfoLogNumBytes];
	glGetShaderInfoLog(shader, shaderInfoLogNumBytes, NULL, shaderInfoLogBuffer);
	printf("shader info log: %s\n", shaderInfoLogBuffer);

	printf("attaching shader to program...\n");
	glAttachShader(shaderProgram, shader);
}

void initTriangle()
{
	// setting up Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);	// every time we call glVertexAttribPointer, that info is stored in the VAO



	GLuint vbo;	// creating a vertex buffer object
	glGenBuffers(1, &vbo);	// generate 1 buffer

	glBindBuffer(GL_ARRAY_BUFFER, vbo);	// make vbo the active object
	
	// copy the vert data to the graphics card
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	printf("creating program...\n");
	GLuint shaderProgram = glCreateProgram();

	printf("compiling vertex shader...\n");
	compileShader(shaderProgram, GL_VERTEX_SHADER, vertexShaderSource);

	printf("compiling fragment shader...\n");
	compileShader(shaderProgram, GL_FRAGMENT_SHADER, fragmentShaderSource);

	printf("specifying which output is writing to which buffer...\n");
	glBindFragDataLocation(shaderProgram, 0, "outColor");

	printf("linking program...\n");
	glLinkProgram(shaderProgram);

	printf("using program...\n");
	glUseProgram(shaderProgram);

	// get reference to "position" input in vertex shader
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");

	// specify how data for this input is retrieved from array
	int numValuesPerInput = 2;
	glVertexAttribPointer(posAttrib, numValuesPerInput, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(posAttrib);

	
}

void drawTriangle()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void initOpenGLProgram()
{
	initGLEW();
	initTriangle();
}