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

const std::string MODE = "tree";

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
in vec3 color;
in float sides;

out vec3 vColor; //Output to geometry or fragment shader
out float vSides;

void main() {
	gl_Position = vec4(pos, 0.0, 1.0);
	vColor = color;
	vSides = sides;
}

)glsl";

const char* geoShader = R"glsl(
#version 150 core

layout(points) in;
layout(line_strip, max_vertices = 69) out;

in vec3 vColor[]; //Output from vertex shader for each vertex
in float vSides[];

out vec3 fColor; //Output to fragment shader

const float PI = 3.1415926;

void main() {
	fColor = vColor[0];
    for (int i = 0; i <= vSides[0]; i++) {
        //Angle between each side in radians
        float ang = PI * 2.0 / vSides[0] * i;

        //Offset from center of point (magic number to adjust for aspect ratio)
        vec4 offset = vec4(cos(ang) * 0.225, -sin(ang) * 0.4, 0.0, 0.0);
        gl_Position = gl_in[0].gl_Position + offset;

        EmitVertex();
    }
    EndPrimitive();
}

)glsl";

const char* geoFrag = R"glsl(
#version 150 core

in vec3 fColor;

out vec4 outColor;

void main() {
	outColor = vec4(fColor, 1.0);
}

)glsl";

const char* treeVertex = R"glsl(
    #version 150 core

    in vec2 pos;
    in vec3 color;
    in float branches;

    out vec3 vColor; //Output to geometry or fragment shader
    out float vBranches;

    void main() {
    	gl_Position = vec4(pos, 0.0, 1.0);
    	vColor = color;
    	vBranches = branches;
    }

)glsl";

const char* treeGeo = R"glsl(
#version 150 core

layout(points) in;
layout(line_strip, max_vertices = 69) out;

in vec3 vColor[]; //Output from vertex shader for each vertex
in float vBranches[];

out vec3 fColor; //Output to fragment shader

void main() {
    fColor = vColor[0];
    for (int i = 1; i <= vBranches[0] + 1; i++) {

        //left branch
        vec4 leftOffset = vec4(-0.1 * i, 0.1 * i, 0.0, 0.0);
        gl_Position = gl_in[0].gl_Position + leftOffset;
        EmitVertex();

        //right branch
        vec4 rightOffset = vec4(0.1 * i, 0.1 * i, 0.0, 0.0);
        gl_Position = gl_in[0].gl_Position + rightOffset;
        EmitVertex();

    }
    EndPrimitive();
}

)glsl";

const char* treeFrag = R"glsl(
    #version 150 core

    in vec3 fColor;

    out vec4 outColor;

    void main() {
    	outColor = vec4(fColor, 1.0);
    }

)glsl";



//methods
GLuint createShader(GLenum, const GLchar*);

#endif //~ Glitter Header
