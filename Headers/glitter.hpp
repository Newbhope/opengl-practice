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

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
//     #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Define Some Constants
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

#endif //~ Glitter Header
