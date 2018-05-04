// Preprocessor Directives
#ifndef GLITTER
#define GLITTER
#pragma once

// System Headers
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <btBulletDynamicsCommon.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
//     #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const std::string MODE = "geometry";

const int mWidth = 1280;
const int mHeight = 720;

//graphics pipeline vertex -> geometry -> fragment

const char* vertexSource = R"glsl(

#version 150 core

in vec2 position;
in vec3 color;

out vec3 Color;

void main() {
	Color = color;
    gl_Position = vec4(position, 0.0, 1.0);
}

)glsl";

const char* fragmentSource = R"glsl(

#version 150 core

in vec3 Color;

uniform vec3 triangleColor;

out vec4 outColor;

void main() {
	outColor = vec4(Color, 1.0);
}

)glsl";

const char* geoVertex = R"glsl(
#version 150 core

in vec2 pos;

void main() {
	gl_Position = vec4(pos, 0.0, 1.0);
}

)glsl";

const char* geoFrag = R"glsl(
#version 150 core

out vec4 outColor;

void main() {
	outColor = vec4(1.0, 0.0, 0.0, 1.0);
}

)glsl";

const char* geoShader = R"glsl(
#version 150 core

layout(points) in;
layout(line_strip, max_vertices = 1) out;

void main() {
	gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();
}

)glsl";

// Vertex shader
const GLchar* vertexShaderSrc = R"glsl(
    #version 150 core

    in vec2 pos;

    void main()
    {
        gl_Position = vec4(pos, 0.0, 1.0);
    }

)glsl";

// Fragment shader
const GLchar* fragmentShaderSrc = R"glsl(
    #version 150 core

    out vec4 outColor;
    void main()
    {
        outColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
)glsl";

//methods
GLuint createShader(GLenum, const GLchar*);

#endif //~ Glitter Header
