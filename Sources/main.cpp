// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <chrono>

/*
void GLAPIENTRY MessageCallback( GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam ) {
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}
*/

int main() {

	// Load GLFW and Create a Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

	// Check for Valid Context
	if (mWindow == nullptr) {
		fprintf(stderr, "Failed to Create OpenGL Context");
		return EXIT_FAILURE;
	}

	// Create Context and Load OpenGL Functions
	glfwMakeContextCurrent(mWindow);
	gladLoadGL();
	fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
    
    glEnable(GL_DEBUG_OUTPUT);

	if (MODE == "geometry") {
		GLuint vertexShader = createShader(GL_VERTEX_SHADER, geoVertex);
		GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, geoFrag);
		GLuint geometryShader = createShader(GL_GEOMETRY_SHADER, geoShader);

		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glAttachShader(shaderProgram, geometryShader);
		glLinkProgram(shaderProgram);
		glUseProgram(shaderProgram);

		GLuint vbo;
		glGenBuffers(1, &vbo);

		float points[] = {
			//Coordinates  Color             Sides
			-0.45f,  0.45f, 1.0f, 0.0f, 0.0f,  4.0f,
			0.45f,  0.45f, 0.0f, 1.0f, 0.0f,  8.0f,
			0.45f, -0.45f, 0.0f, 0.0f, 1.0f, 16.0f,
			-0.45f, -0.45f, 1.0f, 1.0f, 0.0f, 32.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		// Create VAO
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Specify layout of point data
		GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
			6 * sizeof(float), 0);

		GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
			6 * sizeof(float), (void*)(2 * sizeof(float)));

		GLint sidesAttrib = glGetAttribLocation(shaderProgram, "sides");
		glEnableVertexAttribArray(sidesAttrib);
		glVertexAttribPointer(sidesAttrib, 1, GL_FLOAT, GL_FALSE,
			6 * sizeof(float), (void*)(5 * sizeof(float)));

		while (glfwWindowShouldClose(mWindow) == false) {
			if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(mWindow, true);
			}

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawArrays(GL_POINTS, 0, 4);

			// Flip Buffers and Draw
			glfwSwapBuffers(mWindow);
			glfwPollEvents();
		}

	} else if(MODE == "tree") {
		GLuint vertexShader = createShader(GL_VERTEX_SHADER, treeVertex);
		GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, treeFrag);
		GLuint geometryShader = createShader(GL_GEOMETRY_SHADER, treeGeo);

		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glAttachShader(shaderProgram, geometryShader);
		glLinkProgram(shaderProgram);
		glUseProgram(shaderProgram);

		GLuint vbo;
		glGenBuffers(1, &vbo);

		float points[] = {
			//Coordinates  Color           num levels| num branches
			0.f,  -0.5f, 1.0f, 0.0f, 0.0f, 10.0f, 2.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		// Create VAO
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Specify layout of point data
		GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
			7 * sizeof(float), 0);

		GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
			7 * sizeof(float), (void*)(2 * sizeof(float)));

		GLint levelNumAttrib = glGetAttribLocation(shaderProgram, "levels");
		glEnableVertexAttribArray(levelNumAttrib);
		glVertexAttribPointer(levelNumAttrib, 1, GL_FLOAT, GL_FALSE,
			7 * sizeof(float), (void*)(5 * sizeof(float)));

		GLint branchNumAttrib = glGetAttribLocation(shaderProgram, "branches");
		glEnableVertexAttribArray(branchNumAttrib);
		glVertexAttribPointer(branchNumAttrib, 1, GL_FLOAT, GL_FALSE,
			7 * sizeof(float), (void*)(6 * sizeof(float)));

		while (glfwWindowShouldClose(mWindow) == false) {
			if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(mWindow, true);
			}

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawArrays(GL_POINTS, 0, 1);

			// Flip Buffers and Draw
			glfwSwapBuffers(mWindow);
			glfwPollEvents();
		}

	} else {

		// Create Vertex Array Object
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Create a Vertex Buffer Object and copy the vertex data to it
		GLuint vbo;
		glGenBuffers(1, &vbo);
		/*
		float vertices[] = {
			-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
			0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right

			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
			-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Bottom-left
			-0.5f,  0.5f, 1.0f, 0.0f, 0.0f  // Top-left
		};
		*/

		float vertices[] = {
			-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
			0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
			-0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
		};

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Element buffer object (uses vertex buffer somehow?)

		GLuint elements[] = {
			0, 1, 2,
			2, 3, 0
		};
		GLuint ebo;
		glGenBuffers(1, &ebo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(elements), elements, GL_STATIC_DRAW);

		//Somehow read an external shader file I guess
		//Or just deal with ugly shader string constants

		// Create and compile the vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);

		// Create and compile the fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);

		// Link the vertex and fragment shader into a shader program
		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glBindFragDataLocation(shaderProgram, 0, "outColor");
		glLinkProgram(shaderProgram);
		glUseProgram(shaderProgram);

		// Specify the layout of the vertex data
		/*
		GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
		*/

		GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");

		auto t_start = std::chrono::high_resolution_clock::now();

		GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
			5 * sizeof(float), 0);

		GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib,
			3,
			GL_FLOAT,
			GL_FALSE,
			5 * sizeof(float),
			(void*)(2 * sizeof(float)));

		// Rendering Loop
		while (glfwWindowShouldClose(mWindow) == false) {
			if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(mWindow, true);
			}

			// Background Fill Color
			glClearColor(0.f, 0.f, 0.f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//For drawing vertex point arrays
			//glDrawArrays(GL_TRIANGLES, 0, 6);

			//For drawing element buffers
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			// Flip Buffers and Draw
			glfwSwapBuffers(mWindow);
			glfwPollEvents();

			auto t_now = std::chrono::high_resolution_clock::now();
			float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

			glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
		}
	}
    
    //glDebugMessageCallback(MessageCallback, 0);

	glfwTerminate();

	return EXIT_SUCCESS;
}

GLuint createShader(GLenum type, const GLchar* src) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);
	return shader;
}
