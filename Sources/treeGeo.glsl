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
