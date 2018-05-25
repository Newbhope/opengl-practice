
#version 150 core

layout(points) in;
layout(line_strip, max_vertices = 420) out;

in vec3 vColor[]; //Output from vertex shader for each vertex
in float vSides[];

out vec3 fColor; //Output to fragment shader

void main() {
	fColor = vColor[0];
    for (int i = 0; i < vSides[0]; i++) {
        //Angle between each side in radians

        //Offset from center of point (0.3 to accomodate for aspect rratio)
        vec4 offset = vec4(cos(ang) * 0.3, -sin(ang) * 0.4, 0.0, 0.0);
        gl_Position = gl_in[0].gl_Position + offset;

        EmitVertex();
    }
    EndPrimitive();
}
