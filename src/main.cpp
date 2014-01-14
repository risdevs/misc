#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <thread>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

void readFile(std::string file, std::string &content)
{
	std::ifstream ifs(file);
	content = std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();
}

GLuint loadShader(std::string file, GLenum type)
{
	std::string content;
	readFile(file, content);


	const char *c_str = content.c_str();
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &c_str, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if(status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);

		printf("Error compiling %s:\n%s\n", file.c_str(), buffer);

		return -1;
	}

	return shader;
}

int main()
{
    glfwInit();

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
	//GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);



	///////////
	//Vertices
	GLuint vbo;
	glGenBuffers(1, &vbo);

	float vertices[] = {
	    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
	     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
	     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
	    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Bottom-left
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	
	//Create an element array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


	///////////
	//Shaders

	//Load and compile vertex and fragment shader
	GLuint vertexShader = loadShader("shader.vert", GL_VERTEX_SHADER);
	GLuint fragmentShader = loadShader("shader.frag", GL_FRAGMENT_SHADER);


	//Create  a program and attach both shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);


	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (2 * sizeof(float)));







	///////////
	//RUN LOOP
	while(!glfwWindowShouldClose(window))
	{
		/*
		float time = (float)clock() / (float)CLOCKS_PER_SEC;
		glUniform3f(uniColor,
			 (sin(time * 100.0f) + 1.0f) / 2.0f,
			 (sin(time * 100.0f + 1.f) + 1.0f) / 2.0f,
			 (sin(time * 100.0f + 2.f) + 1.0f) / 2.0f);
		*/
		
		// Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	    glfwSwapBuffers(window);
	    glfwPollEvents();

	    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		    glfwSetWindowShouldClose(window, GL_TRUE);

	}

	glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &vbo);

    glfwTerminate();
}
